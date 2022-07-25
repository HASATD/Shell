#include "pipes.h"

void pipe_impl(char arr[])
{

    int no_pipes = 0;
    for (int i = 0; i < strlen(arr); i++)
    {
        if (arr[i] == '|')
            no_pipes++;
    }

    char *all_pipe_cmds[1024];
    char *token = strtok(arr, "|");

    if (token != NULL)
    {
        all_pipe_cmds[0] = token;
    }
    int k = 1;
    while (token != NULL)
    {
        token = strtok(NULL, "|");
        if (token != NULL)
        {
            all_pipe_cmds[k] = token;

            k = k + 1;
        }
    }

    if (k != no_pipes + 1)
    {
        err = 1;
        printf("Invalid no.of arguments");
        return;
    }
    int fd[no_pipes][2];
    for (int i = 0; i < no_pipes; i++)
    {
        int p = pipe(fd[i]);
        if (p < 0)
        {
            err = 1;
            perror("Error");
        }

        if (!i)
        {
            int stot = dup(STDOUT_FILENO);
           // printf("%s\n",all_pipe_cmds[i]);
            dup2(fd[i][1], STDOUT_FILENO);
            close(fd[i][1]);
            execute(all_pipe_cmds[i]);
            dup2(stot, STDOUT_FILENO);
            close(stot);
        }
        else
        {
            int stin = dup(STDIN_FILENO);
            int stot = dup(STDOUT_FILENO);
            dup2(fd[i][1], STDOUT_FILENO);
            close(fd[i][1]);
            dup2(fd[i - 1][0], STDIN_FILENO);
            close(fd[i - 1][0]);
            execute(all_pipe_cmds[i]);
            dup2(stin, STDIN_FILENO);
            close(stin);
            dup2(stot, STDOUT_FILENO);
            close(stot);
        }
    }
    int stin = dup(STDIN_FILENO);
   // printf("%s\n",all_pipe_cmds[no_pipes]);
    dup2(fd[no_pipes - 1][0], STDIN_FILENO);
    close(fd[no_pipes - 1][0]);
    execute(all_pipe_cmds[no_pipes]);
    dup2(stin, STDIN_FILENO);
    close(stin);
}