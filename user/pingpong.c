#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
    int p[2];
    pipe(p);

    if(fork() == 0) { //child 
        //read byte from parent
        char buf[1];
        read(p[0], buf, 1);
        if(buf[0] == '1')
            printf("%d: received ping\n", getpid());
        
        //send byte to parent
        write(p[1], "1", 1);
    } else { //parent 
        //send byte to child
        write(p[1], "1", 1);

        //read byte from child
        char buf[1];
        read(p[0], buf, 1);
        if(buf[0] == '1')
            printf("%d: received pong\n", getpid());
    }
    return 0;
}
