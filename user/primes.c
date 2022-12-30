#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"




void redirect(int k, int pd[2]) {
    close(k);
    dup(pd[k]);
    close(pd[0]);
    close(pd[1]);
}

void
cull(int p) {
    int n;
    while(read(0, &n, sizeof(n))) {
        if(n % p != 0) {
            write(1, &n, sizeof(n));
        }
    }
}

void
primes() {
    int pd[2], p;

    if(read(0, &p, sizeof(p))) {
        printf("prime %d\n", p);
        pipe(pd);

        if(fork()) {
            redirect(0, pd);
            primes();
        } else {
            redirect(1, pd);
            cull(p);
        }
    }

}

int
main() {
    int pd[2];
    pipe(pd);

    if(fork()) {
        redirect(0, pd);
        primes();
    } else {
        redirect(1, pd);
        for(int i = 2; i <= 35; i++) {
            write(1, &i, sizeof(i));
        }
    }
    exit(0);
}
