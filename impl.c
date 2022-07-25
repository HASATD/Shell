#include "impl.h"
void execute(char arr[])
{
    char *args[1000] = {NULL};
    err = 0;
    int r = 0, s = 0;
    char arr1[1024];
    strcpy(arr1, arr);
    char *token = strtok(arr, " ");
    if (token != NULL)
    {
        args[0] = token;
    }
    int k = 1;
    while (token != NULL)
    {
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            args[k] = token;
            k = k + 1;
        }
    }

    int and = 0;
    int no_args = 0;
    for (int i = 0; args[i] != NULL; i++)
    {
        no_args += 1;
    }
    if (strcmp(args[no_args - 1], "&") == 0)
    {

        and = 1;
        args[no_args - 1] = NULL;
    }

    if (strstr(arr1, "<") || strstr(arr1, ">") || strstr(arr1, ">>"))
    {

        redirect(arr1, args);
        
        if (err == 1)
        {
            return;
        }
      
            for (int i = 0; args[i] != NULL; i++)
                if (!strcmp(args[i], ">") || !strcmp(args[i], ">>") || !strcmp(args[i], "<"))
                {
                    printf("multiple redirections of the same kind not allowed");
                    err = 1;
                    return;
                }
                no_args = no_args - 2;
    }

    if (!strcmp(args[0], "cd"))
    {

        cd_impl(args);
    }
    else if (!strcmp(args[0], "echo"))
    {
        echo_m(args);
    }
    else if (!strcmp(args[0], "pwd"))
    {
        pwd_m();
    }

    else if (!strcmp(args[0], "ls"))
    {

        impl_ls(args);
    }
    else if (!strcmp(args[0], "pinfo"))
    {

        pinfo(args, no_args);
    }
    else if (!strcmp(args[0], "bg"))
    {
        if (no_args != 2)
            printf("invalid no.of arguments");
        int job_no = atoi(args[1]);
        bg(job_no);
    }
    else if(!strcmp(args[0],"fg")){
       if(no_args!=2)
       printf("invalid no. of arguments");
       int job_no = atoi(args[1]);
       fg(job_no);

    }
    else if (!strcmp(args[0], "jobs"))
    {   if(args[1]){ 
        if (!strcmp(args[1], "-r"))
            r = 1;
        else if (!strcmp(args[1], "-s"))
            s = 1;
            
            }
        jobs(r, s);
    }
    else if (!strcmp(args[0], "sig"))
    {
        if (no_args != 3)
        {
            err = 1;
            printf("Invalid no.of arguments\n");
        }
        else
        {
            int p = atoi(args[1]);
            int q = atoi(args[2]);
            sig(p, q);
        }
    }
    else if (!strcmp(args[0], "repeat"))
    {

        for (int i = 0; i < atoi(args[1]); i++)
        {

            if (!strcmp(args[2], "cd"))
            {

                cd_impl(args + 2);
            }
            else if (!strcmp(args[2], "ls"))
            {

                impl_ls(args + 2);
            }
            else if (!strcmp(args[2], "pinfo"))
            {

                pinfo(args + 2, no_args);
            }
            else if (!strcmp(args[2], "jobs"))
            {

                if (!strcmp(args[3], "-r"))
                    r = 1;
                if (!strcmp(args[3], "-s"))
                    s = 1;
                jobs(r, s);
            }
            else if (!strcmp(args[2], "sig"))
            {
                if (no_args != 5)
                {
                    err = 1;
                    printf("Invalid no.of arguments\n");
                }
                else
                {
                    int p = atoi(args[3]);
                    int q = atoi(args[4]);
                    sig(p, q);
                }
            }
            else if (!strcmp(args[2], "bg"))
            {
                if (no_args != 4)
                    printf("invalid no.of arguments\n");
                int job_no = atoi(args[3]);
                bg(job_no);
            }
            else if (!strcmp(args[2],"fg")){
                if (no_args != 4)
                    printf("invalid no.of arguments\n");
                int job_no = atoi(args[3]);
                fg(job_no);
            }
            else if (!strcmp(args[2], "echo"))
            {
                echo_m(args + 2);
            }
            else if (!strcmp(args[2], "pwd"))
            {
                pwd_m();
            }
            else
                f_grnd(args + 2, and);
        }
    }
    else
        f_grnd(args, and);

    dup2(stdin_ori, STDIN_FILENO);
    dup2(stdout_ori, STDOUT_FILENO);
}
