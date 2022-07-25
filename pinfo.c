#include "pinfo.h"

void pinfo(char **args,int no_args){

pid_t pid;

if(no_args==1)pid = getpid();
else pid = atoi(args[1]);

printf("pid -- %d\n",pid);

char path[1024];
sprintf(path, "/proc/%d/stat", pid);
FILE *file = fopen(path,"r");
int is_frgrnd=0;
if (file==NULL){
        printf("Error opening %s file\n", path);
        return;
        
    }
    else
    {
        char pgrp[1024],tpgit[1024],str[1024];
        int i = 1;
        while (fscanf(file, "%s", str) == 1)
        {
            if (i == 5)
                     strcpy(pgrp,str);
            if (i == 8)
            {
                strcpy(tpgit,str);
                break;
            }
            i++;
        }
        if(strcmp(pgrp,tpgit)==0)is_frgrnd=1;
       
    }

    fseek(file,0,SEEK_SET);
char str[1024];int i=1;
   while(fscanf(file,"%s",str)==1){
             if(i==3){
           if(is_frgrnd==1){
               strcat(str,"+");
           }
           printf("Process State -- %s\n",str);
       }
       if(i==23){
           printf("memory -- %s bytes\n",str);
           break;
       }
       i++;
   }

fclose(file);
char new_path[1024], buffer[1024];
    sprintf(new_path, "/proc/%d/exe", pid);
    size_t file_size= readlink(new_path, buffer, 1024);
    if (file_size> 0)
    {
        buffer[file_size] = 0;
        if (strstr(buffer, home_dir))
        {
            char *rel_path = strstr(buffer, home_dir);
            rel_path += strlen(home_dir);
            printf("Executable Path -- ~%s\n", rel_path);
        }
        else
            printf("Executable Path -- %s\n", buffer);
    }
    else{
       
         printf("Error opening %s file\n",new_path);
    }





}