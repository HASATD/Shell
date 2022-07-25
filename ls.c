#include "ls.h"
int checkIfFileExists(const char *filename)
{
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if (exist == 0)
        return 1;
    else
        return 0;
}
void print_details(char *path_name, char *dir_name)
{
    //type
    //struct stat stat_buf;

    if (lstat(path_name, &stat_buf) < 0)
    {
        perror("failed");
    };

    /*if(stat_buf.st_nlink==0){
        printf("No such file or directory");
        return;
    }*/
    if ((stat_buf.st_mode & S_IFMT) == S_IFBLK)
        printf("b");
    else if ((stat_buf.st_mode & S_IFMT) == S_IFLNK)
        printf("l");
    else if ((stat_buf.st_mode & S_IFMT) == S_IFCHR)
        printf("c");
    else if ((stat_buf.st_mode & S_IFMT) == S_IFDIR)
        printf("d");
    else if ((stat_buf.st_mode & S_IFMT) == S_IFIFO)
        printf("f");
    else if ((stat_buf.st_mode & S_IFMT) == S_IFREG)
        printf("-");
    else if ((stat_buf.st_mode & S_IFMT) == S_IFSOCK)
        printf("s");
    //stat_bufmissions
    printf("%c", (stat_buf.st_mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (stat_buf.st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (stat_buf.st_mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (stat_buf.st_mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (stat_buf.st_mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (stat_buf.st_mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (stat_buf.st_mode & S_IROTH) ? 'r' : '-');
    printf("%c", (stat_buf.st_mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (stat_buf.st_mode & S_IXOTH) ? 'x' : '-');
    printf(" %4ld ", stat_buf.st_nlink);
    // username,grp
    printf("%10s ", getpwuid(stat_buf.st_uid)->pw_name);
    printf("%10s ", getgrgid(stat_buf.st_gid)->gr_name);
    // total size
    printf("%10ld ", stat_buf.st_size);
    // recent access time
    char Time[1000];
    t = localtime(&stat_buf.st_mtime);
    strftime(Time, sizeof(Time), "%b %e %Y %H:%M", t);
    printf("%s ", Time);
    char buf[1000];
    // read symlink
    if ((stat_buf.st_mode & S_IFMT) == S_IFLNK)
    {
        int i;
        if ((i = readlink(path_name, buf, sizeof(buf))) != -1)
        {
            buf[i] = '\0';
            printf("%s -> %s\n", dir_name, buf);
        }
    }
    else
        printf("%s\n", dir_name);
}
void impl_ls(char **args)
{
    struct dirent **d;
    int is_l = 0, is_a = 0;
    char *current_dir[1024] = {NULL};
    int j = 0;
    for (int i = 1; args[i] != NULL; ++i)
    {
        if (is_l == 0 && is_a == 0 && (strcmp(args[i], "-la") == 0 || strcmp(args[i], "-al") == 0))
        {
            is_l = 1;
            is_a = 1;
        }
        else if (is_l == 0 && strcmp(args[i], "-l") == 0)
            is_l = 1;
        else if (is_a == 0 && strcmp(args[i], "-a") == 0)
            is_a = 1;
        else if(strcmp(args[i],"~")==0){
            current_dir[j]=home_dir;
            j++;
        }
        else if (current_dir[j] == NULL && strcmp(args[i], "&") != 0 &&  strcmp(args[i], "-l") != 0 && strcmp(args[i], "-a") != 0 && strcmp(args[i], "-la") != 0 && strcmp(args[i], "-al") != 0)
        {    
            if (j > 1024)
            {
                printf("argument limit exceeded");
                return;
            }
            current_dir[j] = args[i];
            j++;
        }
        /*else if (strcmp(args[i], "&") != 0)
        {
            printf("Invalid no.of arguments :)\n");
            return;
        }*/
    }
    
    for (int i = 0;i <=j; i++)
    {   if(j>0 && i==j)break;
        if (current_dir[i] == NULL){current_dir[i] = ".";}
    }
    for (int i = 0; i <= j; i++)
    {     
         if(j>0 && i==j)break;
        int n = scandir(current_dir[i], &d, NULL, alphasort);
        
        if (n < 0)
        {
            //if(access(current_dir[i],R_OK)<0){printf("%s: No such file or directory\n",current_dir[i]);continue;}
                
            if (!checkIfFileExists(current_dir[i]))
            {
                printf("%s: No such file or directory\n",current_dir[i]);
                continue;
            }

            if (is_l == 0)
                printf("%s\n", current_dir[i]);
            else
                print_details(current_dir[i], current_dir[i]);
        }
        else
        {

            while (n--)
            {     
                if ((is_a == 1) || (d[n]->d_name[0] != '.' && is_a == 0))
                {
                    if (is_l == 0)
                    {
                        printf("%s\n", d[n]->d_name);
                    }
                    else
                    {
                        char *file_path = (char *)malloc(sizeof(char) * 1000);
                        file_path[0] = '\0';
                        file_path = strcat(file_path, current_dir[i]);
                        file_path = strcat(file_path, "/");
                        file_path = strcat(file_path, d[n]->d_name);
                        print_details(file_path, d[n]->d_name);
                    }
                }
                free(d[n]);
            }
            free(d);
        }
    }
}
