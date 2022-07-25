#include "bgrndtest.h"
#include "prompt.h"

void bgrndt(int signal)
{   
    
   
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    
    if (pid > 0)
    {
        if (find(pid))
        {   
            if (status==0)
                fprintf(stderr, "\n%s with pid %d exited normally\n", find(pid)->name , pid);
            else
                fprintf(stderr, "\n%s with pid %d exited abnormally\n", find(pid)->name, pid);
            
            delete(pid);
            prompt();
            fflush(stdout);
        }
    }
}