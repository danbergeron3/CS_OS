#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("ERROR: sleep requires two arguments, but %d were given.\n", argc);
        return -1;
    }
    int time = atoi(argv[1]);
    pause(time);
    exit(0);
}
