#include "sig.h"

void sig(int p,int q){
struct Node *temp= findbyno(p);
pid_t pid=temp->pid;
        if (pid!=0)
        {
            if (kill(pid, q) < 0)
            {
                err = 1;
                perror("Errors");
            }
        }
        else
        {
            printf("Invalid job with job number %d\n",p);
            err = 1;
        }



}