#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int n = 10;
    schedtickets(n);
    const int loop=5000;
    for(int i = 0; i < loop; i++) {
        asm("nop");
        for(int k=0;k<loop;k++){
            asm("nop");
        }
    }
    schedstatistics();
    exit(0);
}