#include "pwd.h"

void pwd_m()
{
    if (getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
    }
    else
    {
        
        perror("Error");
    }
}