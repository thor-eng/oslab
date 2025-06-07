// pipe_example.c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char buffer[50];

    pipe(fd); // create pipe
    pid = fork(); // create child process

    if (pid == 0) {
        // Child process
        close(fd[1]); // close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);
    } else {
        // Parent process
        close(fd[0]); // close read end
        char *msg = "Hello from parent!";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    }
    return 0;
}




// fifo_writer.c (Writer process)
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *fifo = "/tmp/myfifo";
    mkfifo(fifo, 0666);

    int fd = open(fifo, O_WRONLY);
    char *msg = "Hello from FIFO writer!";
    write(fd, msg, sizeof(char) * 50);
    close(fd);
    return 0;
}



// fifo_reader.c (Reader process)
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *fifo = "/tmp/myfifo";
    char buffer[50];

    int fd = open(fifo, O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    printf("FIFO Reader got: %s\n", buffer);
    close(fd);
    return 0;
}



// msgqueue_example.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("progfile", 65); 
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msg_buffer message;

    // Send
    message.msg_type = 1;
    strcpy(message.msg_text, "Hello via Message Queue!");
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Sent: %s\n", message.msg_text);

    // Receive
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Received: %s\n", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL); // destroy message queue
    return 0;
}



// shared_memory.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);

    if (fork() == 0) {
        // Child process reads from shared memory
        sleep(1); // ensure parent writes first
        printf("Child read from memory: %s\n", str);
        shmdt(str);
    } else {
        // Parent process writes to shared memory
        strcpy(str, "Hello from shared memory!");
        shmdt(str);
        wait(NULL);
        shmctl(shmid, IPC_RMID, NULL); // destroy memory
    }

    return 0;
}




