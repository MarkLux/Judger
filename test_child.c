#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // malloc a little memeory

    // int * a = (int *)malloc(4 * sizeof(int));
    // memset(a,1,sizeof(a));

    // 这里记得检查下是否有参数，不然会报段异常
    if (argc > 1)
    {
        char *shmid_str = argv[1];
        int shmid = atoi(shmid_str);

        printf("get shmid: %d\n", shmid);
    }

    pid_t child_pid = fork();
    struct rusage child_usage;
    int child_status;

    if (child_pid > 0)
    {
        wait4(child_pid, &child_status, WSTOPPED, &child_usage);
        printf("child process exited with %ld k memory used\n", child_usage.ru_maxrss);
    }
    else if (child_pid == 0)
    {
        // child process
        int size = 1 * 1024 * 1024;
        int *a = NULL;
        a = (int *)malloc(size);
        memset(a, 1, size);
    }

    return 0;
}