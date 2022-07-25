#include "fg.h"
void fg(int job_no)
{

    struct Node *temp = findbyno(job_no);
    char name[1024];
    strcpy(name,temp->name);
    pid_t pid = temp->pid;
    pid_t pgid = getpgid(pid);

    if (pid == -1)
    {
        printf("Job with the job.no %d doesn't exist", job_no);
        return;
    }

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, pgid);

    if(kill(pid, SIGCONT)<0){

        perror("Error");
    }

    int status;

    waitpid(pid, &status, WUNTRACED);

    tcsetpgrp(STDIN_FILENO, home_pgid);

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    

   delete(pid);

    if (WIFSTOPPED(status) == 1)
    {

        struct Node *temp = head;
        int jno = 1;
        while (temp != NULL)
        {
            jno = temp->job_no + 1;
            temp = temp->next;
        }
        insertNode(pid,name,jno);
       printf("%s with PID %d suspended\n", name, pid);
    }

    return;
}
