#ifndef __HEADERS_H
#define __HEADERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>


char curr_dir[1000];
char host_name[1000];
char u_name[1000];
char home_dir[1000];
char *allcmds[100];
char prev_dir[1000];
int shellInFile, shellOutFile;
pid_t home_pid;
pid_t home_pgid;
struct stat stat_buf;
struct tm *t;
struct Node
{
    pid_t pid;
    char name[1024];
    int job_no;
    char stat[15];
    struct Node *next;
};
struct Node *head;
char cwd[1024];
int err;
int stdin_ori;
int stdout_ori;
#endif