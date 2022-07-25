#include "foreback.h"

void f_grnd(char **args, int and)
{

    pid_t pid;
    pid = fork();

    if (pid < 0)
        perror("Error: \n");
    else if (pid == 0)
    {
        setpgid(0, 0);
        if (execvp(args[0], args) < 0)
        {
            perror("Error");
        }
    }
    else
    {
        dup2(stdout_ori, STDOUT_FILENO);
        dup2(stdin_ori, STDIN_FILENO);
        if (and)
        {
            char name[1024];
            strcpy(name, args[0]);
            for (int i = 1; args[i] != NULL; i++)
            {
                strcat(name, " ");
                strcat(name, args[i]);
            }
            int job_num = 1;
            struct Node *temp = head;

            while (temp != NULL)
            {
                job_num = temp->job_no + 1;
                temp = temp->next;
            }

            insertNode(pid, name, job_num);

            printf("%d\n", pid);
        }
        else
        {
            int stat;
            signal(SIGTTOU, SIG_IGN);
            signal(SIGTTIN, SIG_IGN);
            tcsetpgrp(0, pid);
            waitpid(pid, &stat, WUNTRACED);
            tcsetpgrp(0, home_pid);
            signal(SIGTTOU, SIG_DFL);
            signal(SIGTTIN, SIG_DFL);
           if (WIFSTOPPED(stat))
            {
                char name[1024];
                strcpy(name, args[0]);
                for (int i = 1; args[i] != NULL; i++)
                {
                    strcat(name, " ");
                    strcat(name, args[i]);
                }
                int job_num = 1;
                struct Node *temp = head;

                while (temp != NULL)
                {
                    job_num = temp->job_no + 1;
                    temp = temp->next;
                }

                insertNode(pid, name, job_num);
                printf("%s with PID %d is suspended\n", name, pid);
            }
        }
    }
}