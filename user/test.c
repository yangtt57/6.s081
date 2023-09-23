#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc,char* argv[]) {
    // int i;
    int p[2];
    pipe(p);
    int i;
    for(i=0;i<35;i++) {
        write(p[1],&i,4);
    }
    close(p[1]);
    if(fork()==0) {
        int num=0;
        int n;
        while((n=read(p[0],&num,4))!=0)
            printf("%d ",num);  // 2 3 4 5 .. 34
    }
    exit(0);
}
