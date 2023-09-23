#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"



void find(char* path,char* pattern, int type) {
    char buf[512],* p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd=open(path,0))<0) {
        fprintf(2,"find: cannot open %s\n",path);
        return;
    }   

    if(fstat(fd,&st)<0) {
        fprintf(2,"find: cannot stat %s\n",path);
        close(fd);
        return;
    }

    if(strlen(path)+1+DIRSIZ > sizeof(buf)) {
        printf("find: path too long\n");
        close(fd);
        return;
    }
    strcpy(buf,path);
    p=buf+strlen(buf);
    *p++='/';
    // printf("%s\n\n",pattern);
    switch (type)
    {
    case 0: {
        while(read(fd,&de,sizeof(de))==sizeof(de)) {
            if(de.inum==0) 
                continue;
            memmove(p,de.name,DIRSIZ);
            p[DIRSIZ]=0;
            if(strstr(de.name,pattern)==1) {
                printf("%s\n",buf);
            }
        }
        break;
    }    
    case 1: {
        
        while(read(fd,&de,sizeof(de))==sizeof(de)) {
            if(de.inum==0) 
                continue;
            memmove(p,de.name,DIRSIZ);
            p[DIRSIZ]=0;
            if(stat(buf,&st)<0) {
                printf("ls: cannot stat %s\n",buf);
                continue;
            }
            if(strstr(de.name,pattern)==1) {
                printf("%s\n",buf);
            }
            if(st.type==T_DIR && strcmp(de.name,".") && strcmp(de.name,"..")) find(buf,pattern,1);
        }
        break;
    }
    }
}

int main(int argc,char* argv[]) {
    // 参数小于两个，直接退出
    if(argc<2) {
        printf("Usage: find [dir] name ......\n");
        exit(1);
    } else if(argc == 2) {
        find(".",argv[1],0);  // 不进入子目录查找
    } else {
        find(argv[1],argv[2],1);
    }
    exit(0);
}