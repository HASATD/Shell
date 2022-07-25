#include "prompt.h"

void prompt(){
    if(getcwd(curr_dir,sizeof(curr_dir))){
       
    if(strstr(curr_dir,home_dir)){
        char *rel_path = strstr(curr_dir,home_dir)+strlen(home_dir);
        printf("<%s@%s:~%s>",u_name,host_name,rel_path);
    }
    else {
        printf("<%s@%s:%s>",u_name,host_name,curr_dir);
    }
}}