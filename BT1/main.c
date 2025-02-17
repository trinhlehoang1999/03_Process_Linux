/* Mô tả: Viết một chương trình C tạo một process con bằng cách sử dụng fork().
Sau khi tạo process, tiến trình con sẽ in ra PID của nó và tiến trình cha
 in ra PID của tiến trình con.
 */
/* ----------------------------- */
// Result:
// Parent process: 12408, created child with PID: 12409
// returned value of fork(): 0
// Child process PID: 12409
/* ----------------------------- */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    // tiến trình con sẽ chạy lại từ đây sau khi tiến trình cha (main) hoàn thành
    
    printf("returned value of fork(): %d\n", pid);

    if (pid < 0) {
        // Fork failed
        printf("failed\n");

    } else if (pid == 0) {
        // Child process
        printf("Child process PID: %d\n", getpid());
    } else {
        // Parent process
        printf("Parent process: %d, created child with PID: %d\n", getpid(), pid);
    }
    
    return 0;
}