#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char* argv[]) {
    // int i;
    if(argc < 2) {
        fprintf(2,"Usage: sleep times .....\n");
        exit(1);
    } else {
        sleep(atoi(argv[1]));
    }
    exit(0);
}