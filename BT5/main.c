#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void sig_handler(int num) {
    printf("tiến trình con đã nhận được signal_kill: %d\n", num);
}

int main(int argc, char *argv[]) {
    // Kiểm tra số lượng đối số dòng lệnh
    if (argc == 2) 
    {
        printf("Đối số truyền vào: %s\n", argv[1]);
    }else
    {
        printf("Hãy dùng 1 đối số\n");
        return -1;
    }
    signal(SIGUSR1, sig_handler);
    pid_t pid = fork();
    
    printf("returned value of fork(): %d\n", pid);

    if (pid < 0) {
        // Fork failed
        printf("failed\n");

    } else if (pid == 0) {
        // Child process
        printf("Child process PID: %d\n", getpid());
        while(1);

    } else {
        // Parent process
        printf("Parent process: %d, created child with PID: %d\n", getpid(), pid);
        while(1);
        kill(getpid(), SIGUSR1);
    }
    
    return 0;
}