#include "kernel/types.h"
#include "user/user.h"

void clearStr(char* s) {
    int i;
    for(i=0;i<10;i++) 
        s[i]='\0';
}

int main(int argc,char* argv[]) {
    char pbuf[100];
    char* buf[10];
    int n;
    int i,k;

    for(i=1;i<argc;i++) {
        buf[i-1]=malloc(100);
        for(k=0;k<strlen(argv[i]);k++)
            buf[i-1][k]=argv[i][k];
    }
    i--;
    while((n=read(0,pbuf,100))!=0) {
        if(i==0) printf("%s\n",pbuf);
        else {
            // printf("%s\n",pbuf);
            buf[i]=malloc(100);
            int j,k;
            for(j=0;j<n;j++) {
                for(k=j+1;k<n;k++) {
                    if(pbuf[k]=='\n' && pbuf[j]!='\n') {
                        getstr(buf[i],pbuf,j,k);
                        // int t;
                        // for(t=0;t<=i;t++) {
                        //     printf("%s ",buf[t]);
                        // }
                        // exec接受的是char**类型，不能传入char[][]
                        if(fork()==0) exec(buf[0],buf);
                        clearStr(buf[i]);
                        j=k+1;
                    }
                }
            }
        }
        // printf("________________");
    }
    wait(0);
    exit(0);
}