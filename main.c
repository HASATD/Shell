#include "prompt.h"
#include "cd.h"
#include "impl.h"
#include "bgrndtest.h"
#include "pipes.h"
#include "signals.h"
int main()
{
    gethostname(host_name, sizeof(host_name));
    getcwd(home_dir, sizeof(home_dir));
    getlogin_r(u_name, sizeof(u_name));
    head = NULL;
    signal(SIGCHLD, bgrndt);
    signal(SIGINT, control_c);
    signal(SIGTSTP, control_z);

    prev_dir[0] = '\0';
    curr_dir[0] = '\0';
    strcpy(curr_dir, home_dir);
    home_pid = getpid();
    home_pgid = getpgid(home_pid);

    stdin_ori = dup(STDIN_FILENO);
    stdout_ori = dup(STDOUT_FILENO);
    while (1)
    {
        prompt();
        fflush(stdout);
        char l[1024];

        int command_size = 0;
        size_t n = 100;
        char *line_ptr = (char *)malloc(n);
        command_size = getline(&line_ptr, &n, stdin);

        if (command_size < 0){printf("\n");exit(0);}
            
        line_ptr[command_size - 1] = '\0';
        if (line_ptr[0] == '\0')
            continue;

        char *token = strtok(line_ptr, ";");
        if (token != NULL)
        {
            allcmds[0] = token;
        }
        int k = 1;
        while (token != NULL)
        {
            token = strtok(NULL, ";");
            if (token != NULL)
            {
                allcmds[k] = token;

                k = k + 1;
            }
        }

        for (int i = 0; i < k; i++)
        {
            if (strstr(allcmds[i], "|"))
            {
                pipe_impl(allcmds[i]);
            }

            else
                execute(allcmds[i]);
        }
    }
}