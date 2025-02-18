#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int create_zombie(void) {
    pid_t pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
    }
    if (pid == 0) {
        // Tiến trình con: kết thúc ngay để trở thành zombie.
        printf("Tiến trình con với PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(2);
        printf("Tiến trình con kết thúc.\n");
    } else {
        // Tiến trình cha: ngủ để giữ tiến trình zombie trong bảng tiến trình.
        printf("tiến trình cha có PID = %d. Tiến trình con có PID = %d).\n", getpid(), pid);
        sleep(5);
        printf("tiến trình cha sau khi kết thúc có PID = %d. Tiến trình con có PID = %d).\n", getpid(), pid);    }
}


int create_orphan(void) {
    pid_t pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
        return -1;
    }
    if (pid == 0) {
        // Tiến trình con: ngủ lâu để sau khi tiến trình cha kết thúc,
        printf("Tiến trình con PID = %d, PPID ban đầu = %d\n", getpid(), getppid());
        sleep(5);
        printf("\nTiến trình con sau khi cha kết thúc: PID = %d, PPID mới = %d\n", getpid(), getppid());
    } else {
        // Tiến trình cha: kết thúc trước tiến trình con
        printf("Tiến trình Parent với PID = %d. Tiến trình con PID = %d sẽ trở thành orphan.\n", getpid(), pid);
        sleep(2);
        printf("Tiến trình cha kết thúc.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("chỉ được nhập 1 đối số zombie or orphan\n");
        return -1;
    }
    
    if (strcmp(argv[1], "zombie") == 0) {
        create_zombie();
    } else if (strcmp(argv[1], "orphan") == 0) {
        create_orphan();
    } else {
        printf("Đối số không hợp lệ. Sử dụng 'zombie' hoặc 'orphan'\n");
    }
    
    return 0;
}