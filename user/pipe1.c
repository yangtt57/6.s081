#include "kernel/types.h"
#include "user/user.h"

int main() {
    int p[2];
    // char* argv[2];
    // argv[0]="wc";
    // argv[1]=0;
    pipe(p);

    if(fork()==0) {
        close(0);
        dup(p[0]);
        close(p[0]);
        close(p[1]);
        char buf[4];
        read(0,buf,13);
        printf("%d\n",atoi(buf));
        // exec("wc",argv);
    } else {
        close(p[0]);
        write(p[1],"13",13);
        // wait(0);
        close(p[1]);
        wait(0);
    }
    exit(0);
}