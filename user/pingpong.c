#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
    int p[2];
    pipe(p);
    
    int n;

    if(fork() == 0) { //child 
        //read byte from parent
        char buf[1];

        n = read(p[0], buf, 1);
        if(n < 0) {
            fprintf(2, "read error\n");
            exit(1);
        }

        if(buf[0] == '1')
            printf("%d: received ping\n", getpid());
        
        //send byte to parent
        if(write(p[1], "1", 1) != 1) {
            fprintf(2, "write error\n");
            exit(1);
        }
        exit(0);
    } else { //parent 
        //send byte to child
        if(write(p[1], "1", 1) != 1) {
            fprintf(2, "write error\n");
            exit(1);
        }

        //read byte from child
        char buf[1];

        n = read(p[0], buf, 1);
        if(n < 0) {
            fprintf(2, "read error\n");
            exit(1);
        }

        if(buf[0] == '1')
            printf("%d: received pong\n", getpid());
        exit(0);
    }
}
