#include "kernel/types.h"
#include "user/user.h"

int main() {
    int n,n_,pid;
    int fds[2],fds_[2];
    char buf[9];

    // crate a pipe
    pipe(fds);
    pipe(fds_);
    pid=fork();
    if(pid==0) {
        close(fds[1]);
        n=read(fds[0],buf,8);
        if(n>0)
            // printf("\n%d\n",n);
            printf("%d: received ping\n",getpid()); 
        close(fds_[0]);
        write(fds_[1],buf,8);
        // exit(0);
    } else {
        close(fds[0]);
        write(fds[1],buf,8);
        close(fds_[1]);
        n_=read(fds_[0],buf,8);
        if(n_>0) 
            printf("%d: received pong\n",getpid());
    }
    exit(0);
}
