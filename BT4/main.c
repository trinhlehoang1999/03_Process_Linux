/* 
Result:
Đối số truyền vào: 5
returned value of fork(): 15187
Parent process: 15186, created child with PID: 15187
returned value of fork(): 0
Child process PID: 15187
15187
Tiến trình con kết thúc bình thường.
Mã thoát của tiến trình con: 5 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    int status = 0, code = 0;
    int flag_parent = 0;
    // Kiểm tra số lượng đối số dòng lệnh
    if (argc == 2) 
    {
        printf("Đối số truyền vào: %s\n", argv[1]);
    }else
    {
        printf("Hãy dùng 1 đối số\n");
        return -1;
    }

    int child_exit_code = atoi(argv[1]);

    pid_t pid = fork();
    
    printf("returned value of fork(): %d\n", pid);

    if (pid < 0) {
        // Fork failed
        printf("failed\n");

    } else if (pid == 0) {
        // Child process
        printf("Child process PID: %d\n", getpid());
        exit(child_exit_code);
    } else {
        // Parent process
        printf("Parent process: %d, created child with PID: %d\n", getpid(), pid);
        flag_parent = wait(&status); // status chứa PID của tiến trình con
        if (flag_parent < 0) 
        {
            printf("wait() unsuccessful\n");
        }
        else 
        {
            if (WIFEXITED(status) != 0) {
                int exit_status = WEXITSTATUS(status);
                printf("Tiến trình con kết thúc bình thường.\n");
                printf("Mã thoát của tiến trình con: %d\n", exit_status);
            } else 
            {
                printf("Tiến trình con kết thúc không bình thường.\n");
            }
        }
    
    }
    
    return 0;
}