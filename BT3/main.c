/* 
BT3. Tín hiệu Process
Mô tả: Viết một chương trình tạo hai process cha - con. Tiến trình cha sẽ gửi tín hiệu SIGUSR1 tới tiến trình con sau một khoảng thời gian.
Yêu cầu:
Sử dụng signal() để định nghĩa hành vi của tiến trình con khi nhận tín hiệu SIGUSR1.
In ra một thông báo khi tiến trình con nhận được tín hiệu.

*/
/* 
Result: 
returned value of fork(): 14728
Parent process: 14727, created child with PID: 14728
returned value of fork(): 0
Child process PID: 14728
Tiến trình con (PID: 14728) đang chạy, chờ nhận tín hiệu...
waiting for 3 seconds...
waiting for 2 seconds...
waiting for 1 seconds...
tiến trình con đã nhận được signal_kill: 10
Tiến trình con kết thúc.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define Sleeptime 3

void sig_handler(int num) {
    printf("tiến trình con đã nhận được signal_kill: %d\n", num);
    printf("Tiến trình con kết thúc.\n");
}

int main() {

    pid_t pid = fork();
    
    printf("returned value of fork(): %d\n", pid);
    signal(SIGUSR1, sig_handler);

    if (pid < 0) {
        // Fork failed
        printf("failed\n");

    } else if (pid == 0) {
        // Child process
        printf("Child process PID: %d\n", getpid());
        
        printf("Tiến trình con (PID: %d) đang chạy, chờ nhận tín hiệu...\n", getpid());
        while (1);
        
    } else {
        // Parent process
        printf("Parent process: %d, created child with PID: %d\n", getpid(), pid);
        for (int i = 0; i < Sleeptime; i++)
        {   
            sleep(1);
            printf("waiting for %d seconds...\n", Sleeptime - i);
        }
        
        kill(pid, SIGUSR1);
    }
    
    return 0;
}