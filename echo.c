#include "echo.h"

void echo_m(char **args)
{
    for (int i = 1; args[i]!=NULL ; i++)
        printf("%s ", args[i]);
    printf("\n");
}