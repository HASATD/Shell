#include "cd.h"

void cd_impl(char *args[])
{
    char path[1024];
    
     if (args[1]==NULL) {
         getcwd(curr_dir,sizeof(curr_dir));
              chdir(home_dir);
              strcpy(prev_dir,curr_dir);
         }
    else if (args[2]) 
       printf("cd: invalid usage\nUsage: cd path");
    else if (strcmp(args[1], "~") == 0){
        getcwd(curr_dir,sizeof(curr_dir));
         
         chdir(home_dir);
         strcpy(prev_dir,curr_dir);
         }
    else if (strcmp(args[1], ".") == 0){
        getcwd(curr_dir,sizeof(curr_dir));
         strcpy(prev_dir,curr_dir);

       return;}
     
    else if (args[1][0] == '~')
     {   
         getcwd(curr_dir,sizeof(curr_dir));
         
          strcpy(path,home_dir);
           //printf("%s\n",home_dir);
          strcat(path, args[1]+1);
        // printf("%s\n",path);
         if (chdir(path) < 0){
             perror("Error");return;}
                    strcpy(prev_dir,curr_dir);
     }
     else if(strcmp(args[1],"..")==0){
         getcwd(curr_dir,sizeof(curr_dir));
         chdir(args[1]);
         strcpy(prev_dir,curr_dir);
     }
     else if(args[1][0]=='-'){
         if(prev_dir[0]=='\0'){
             printf("cd: OLDPWD not set\n");
             return;
         }
        getcwd(curr_dir,sizeof(curr_dir));
                printf("%s\n",prev_dir);
        if(chdir(prev_dir)<0)perror("Error");
        strcpy(prev_dir,curr_dir);

     }        
      else if (args[1][0] == '/'){
          getcwd(curr_dir,sizeof(curr_dir));
          
          if(chdir(args[1]) < 0)
          {        perror("Error");return;}
           strcpy(prev_dir,curr_dir);
                          
      }
      else if (getcwd(curr_dir,sizeof(curr_dir))){
          
          if(chdir(args[1]) < 0){
                   perror("Error");return;}
                   strcpy(prev_dir,curr_dir);
                
         }
}