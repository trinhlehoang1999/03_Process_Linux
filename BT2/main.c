/* 
BT2. Sử dụng exec và Biến Môi Trường
Mô tả: Viết một chương trình trong đó tiến trình con sẽ thay thế chương trình đang chạy bằng một chương trình khác, ví dụ ls hoặc date, sử dụng hàm execlp() hoặc execvp().
Yêu cầu:
Truyền các biến môi trường vào chương trình và thực hiện các công việc khác nhau (ví dụ biến môi trường được truyền vào là 1 thì thực hiện lệnh ls, nếu là 2 thì thực hiện lệnh date).
*/
/* 
Giải thích điều gì xảy ra với tiến trình ban đầu sau khi exec được gọi.
Answer: chương trình mới đã được tạo bới lệnh exec ==> dòng lệnh mới sẽ đè lên dòng lệnh phía dưới ==> dòng lệnh phía dưới sẽ không được thực hiện
*/
/* 
Đối số truyền vào: 1
returned value of fork(): 13696
Tiến trình cha với PID: 13695
returned value of fork(): 0
Thực hiện lệnh ls -l
BT2_exe  main.c  Makefile
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

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
    // Tạo tiến trình con
    pid_t pid = fork();
    printf("returned value of fork(): %d\n", pid);
    if (pid < 0)
    {
        // Xử lý lỗi fork
        printf("fork() failed\n");
    } else if (pid == 0) {
        // Tiến trình con
        char *choice = argv[1];

        if (strcmp(choice, "1") == 0) 
        {
            // Thực hiện lệnh ls -l
            printf("Thực hiện lệnh ls -l\n");
            execlp("/usr/bin/ls", "l", NULL);
            // chương trình mới đã được tạo bới lệnh exec ==> dòng lệnh dưới sẽ không được thực hiện
            while (1); 
        }
        else if (strcmp(choice, "2") == 0)
        {
            // Thực hiện lệnh date
            printf("Thực hiện lệnh date\n");
            execlp("/usr/bin/date", "date", NULL);
            // chương trình mới đã được tạo bới lệnh exec ==> dòng lệnh dưới sẽ không được thực hiện
            while (1);
        } else {
            printf("Chọn đối số không hợp lệ\n");
            return -1;
        }

    } else {
        // Tiến trình cha: đợi tiến trình con hoàn thành
        printf("Tiến trình cha với PID: %d\n", getpid());
        // wait(NULL);
        // printf("Tiến trình cha: Tiến trình con đã hoàn thành.\n");
    }
    return 0;
}
