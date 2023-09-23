
#include "kernel/types.h"
#include "user/user.h"

void prime(int listenfd)
{
    int readnum = 0;
    int n = 0;
    int baseprime = 0;
    int forked = 0; // 标志是否创建了子进程，并且保证每个该进程只能创建一个子进程
    int p[2];
    n = read(listenfd, &readnum, 4);
    if (n <= 0)
    {
        close(listenfd);
        if (forked == 1)
        {
            close(p[1]);
            int child_pid;
            wait(&child_pid);
        }

        exit(0);
    }
    baseprime = readnum;
    printf("prime %d\n", baseprime);
    // printf("pid: %d num: %d\n", getpid(), baseprime);
    while ((n = read(listenfd, &readnum, 4)) != 0)
    {
        //! 傻逼代码
        // if (n <= 0)
        // {
        //     close(listenfd);
        //     if (forked == 1)
        //     {
        //         close(p[1]);
        //         int child_pid;
        //         wait(&child_pid);
        //     }
        //     exit(0);
        // }

        if (readnum % baseprime != 0)
        {
            // int p[2];
            if (forked == 0)
            {
                pipe(p);
                forked = 1;
                if (fork() == 0)
                {
                    // 可以理解为进程的创建需要较长的时间，因此需要将 forked=1 放在外面，避免竞争。
                    // forked = 1;
                    close(p[1]);
                    close(listenfd); // important
                    // sleep(10);
                    prime(p[0]);
                }
                else
                {
                    close(p[0]);
                }
            }
            write(p[1], &readnum, 4);
        }
    }
    if (n <= 0)
    {
        close(listenfd);
        if (forked == 1)
        {
            close(p[1]);
            int child_pid;
            wait(&child_pid);
        }
        exit(0);
    }
}

int main()
{
    int p[2];
    pipe(p);
    // 向第一个进程写入2-35
    int i;
    for (i = 2; i < 35; i++)
    {
        // 直接以int的地址写入
        write(p[1], &i, 4);
    }
    close(p[1]); // 在这里关闭管道的写入端，子进程中的写入端口也会关闭
    prime(p[0]);
    // printf("\n");
    exit(0);
}
