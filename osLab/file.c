#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    char buffer[100];

    // Open the file (O_RDONLY - read only)
    fd = open("sample.txt", O_RDONLY);
    if (fd < 0) {
        perror("Open failed");
        return 1;
    }

    // Read from file
    ssize_t bytes = read(fd, buffer, sizeof(buffer)-1);
    if (bytes < 0) {
        perror("Read failed");
        close(fd);
        return 1;
    }

    buffer[bytes] = '\0'; // Null terminate
    printf("Read from file:\n%s\n", buffer);

    close(fd);
    return 0;
}



#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("Open failed");
        return 1;
    }

    const char *msg = "Hello from write syscall!\n";
    write(fd, msg, strlen(msg));

    close(fd);
    return 0;
}



#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("sample.txt", O_RDONLY);
    if (fd < 0) {
        perror("Open failed");
        return 1;
    }

    int flags = fcntl(fd, F_GETFL);
    if (flags < 0) {
        perror("fcntl F_GETFL failed");
        close(fd);
        return 1;
    }

    printf("File descriptor flags: %d\n", flags);

    close(fd);
    return 0;
}



#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("sample.txt", O_RDONLY);
    if (fd < 0) {
        perror("Open failed");
        return 1;
    }

    lseek(fd, 5, SEEK_SET); // Move to 5th byte from beginning

    char buffer[50];
    int bytes = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytes] = '\0';
    printf("After seeking, read: %s\n", buffer);

    close(fd);
    return 0;
}



#include <sys/stat.h>
#include <stdio.h>

int main() {
    struct stat fileStat;

    if (stat("sample.txt", &fileStat) < 0) {
        perror("stat failed");
        return 1;
    }

    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("File Permissions: %o\n", fileStat.st_mode & 0777);
    printf("Last Access Time: %ld\n", fileStat.st_atime);

    return 0;
}



#include <dirent.h>
#include <stdio.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir failed");
        return 1;
    }

    struct dirent *entry;
    printf("Directory contents:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("  %s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
