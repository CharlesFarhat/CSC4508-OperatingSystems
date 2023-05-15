#include "types.h"
#include "user.h"

#pragma GCC push_options
#pragma GCC optimize ("O0")

int main(int argc, char *argv[])
{
    int pid;

    // on ne veut que 3 fils !
    for(int i=0; i<3; i++) {
        pid = fork();
        if (pid == 0) {
            printf(1, "%d STARTS\n", getpid());
            for(int i=0; i < 2<<28; i++) {}
            printf(1, "%d ENDS\n", getpid());
            exit();
        }
    }

    for(int i=0; i < 2<<28; i++) {}

    // on attend tous les fils qu'on a pu générer précédement
    while(wait() >= 0)
        printf(1, "Killing!\n");

    exit();
}


#pragma GCC pop_options
