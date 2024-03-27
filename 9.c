#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key = 5678;

    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    sprintf(shared_memory, "Hello, shared memory!");

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        char *child_shared_memory = (char *)shmat(shmid, NULL, 0);
        if (child_shared_memory == (char *)(-1)) {
            perror("shmat in child process");
            exit(1);
        }

        printf("Child Process: %s\n", child_shared_memory);
        shmdt(child_shared_memory);
    } else {
        wait(NULL);
        printf("Parent Process: %s\n", shared_memory);
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
