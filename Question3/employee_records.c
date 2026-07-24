#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    char buffer[100];

    fd = open("employees.txt", O_CREAT | O_RDWR, 0644);

    if (fd < 0) {
        printf("Error opening file\n");
        return 1;
    }

    write(fd, "101 Alice\n", 10);
    write(fd, "102 Bob\n", 8);

    lseek(fd, 0, SEEK_SET);

    read(fd, buffer, sizeof(buffer) - 1);
    buffer[18] = '\0';

    printf("Employee Records:\n%s", buffer);

    lseek(fd, 10, SEEK_SET);

    write(fd, "103 Carol\n", 10);

    close(fd);

    return 0;
}
