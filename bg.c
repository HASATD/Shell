#include "bg.h"

void bg(int jobnum)
{
    struct Node *temp = findbyno(jobnum);
    pid_t pid = temp->pid;
    if (pid == -1)
    {
        printf("Error: job with the %d number doesn't exist", jobnum);

        return;
    }

    if (kill(pid, SIGCONT) < 0)
    {
        err = 1;
        perror("");
    }
}