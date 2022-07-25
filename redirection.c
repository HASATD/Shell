#include "redirection.h"

void redirect(char *arr, char **args)
{
    int fd;
    if (strstr(arr, ">"))
    {

        for (int i = 0; args[i + 1] != NULL; i++)
        {
            if (!strcmp(args[i], ">") || !strcmp(args[i], ">>"))
            {
                if (!strcmp(args[i], ">"))
                {

                    fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }
                else if (!strcmp(args[i], ">>"))
                {
                    fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                }
                if (fd < 0)
                {
                    perror("Error");
                    err = 1;
                    return;
                }

                else
                {
                    dup2(fd, STDOUT_FILENO);

                    close(fd);
                }

                int j = i;

                // printf("hello\n");
                for (i; args[i + 2] != NULL; i++)
                {
                    args[j] = args[i + 2];
                    j++;
                }

                args[j] = 0;

                break;
            }
        }
    }

    if (strstr(arr, "<"))
    {
       
        for (int i = 0; args[i + 1] != NULL; i++)
        {
            if (!strcmp(args[i], "<"))
            {
                fd = open(args[i + 1], O_RDONLY);

                if (fd < 0)
                {

                    perror("Error");
                    err = 1;
                    return;
                }
                else
                {
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                }
                int j = i;
                for (i; args[i + 2] != NULL; i++)
                {
                    args[j] = args[i + 2];
                    j++;
                }
                args[j] = 0;
                break;
            }
        }
    }
    
}