
#include "signals.h"

void control_c(int sig)
{
    err = 1;
    printf("\n");
    prompt();
    fflush(stdout);
}

void control_z(int sig)
{
    printf("\n");
    prompt();
    fflush(stdout);
}