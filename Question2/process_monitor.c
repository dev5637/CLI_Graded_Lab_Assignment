#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0) {
        printf("Child Process: PID = %d\n", getpid());
        sleep(10);
        printf("Child finished.\n");
        exit(0);
    } else {
        printf("Parent Process: PID = %d\n", getpid());

        sleep(3);

        printf("Child is taking too long. Sending SIGTERM...\n");
        kill(pid, SIGTERM);

        wait(NULL);

        printf("Zombie process prevented.\n");
    }

    return 0;
}
