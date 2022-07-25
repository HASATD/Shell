#include "jobs.h"
struct job
{
    char name[1024];
    char stat[15];
    int job_no;
    pid_t pid;
};
int struct_cmp_by_product(const void *a, const void *b)
{
    struct job *ia = (struct job *)a;
    struct job *ib = (struct job *)b;
    return strcmp(ia->name, ib->name);
}

void jobs(int r, int s)
{

    struct Node *temp = head;
    
    int jbcnt = 0;
    struct job alljobs[1024];
    
    while (temp != NULL)
    {
        pid_t pid = temp->pid;
        char path[1024];
        char stat[15];
        sprintf(path, "/proc/%d/stat", pid);
        FILE *file = fopen(path, "r");
        if (file == NULL)
        {
            printf("Error opening %s file\n", path);
        }
        else
        {
            char str[1024];
            int i = 1;
            while (fscanf(file, "%s", str) == 1)
            {
                if (i == 3)
                {
                    if (!strcmp(str, "T"))
                        strcpy(stat, "Stopped");
                    else
                        strcpy(stat, "Running");

                    break;
                }

                i++;
            }
            fclose(file);
             
            strcpy(temp->stat, stat);

            strcpy(alljobs[jbcnt].name, temp->name);
            strcpy(alljobs[jbcnt].stat, temp->stat);
            alljobs[jbcnt].job_no = temp->job_no;
            alljobs[jbcnt].pid = temp->pid;
            jbcnt++;
        }

        temp = temp->next;
    }
   
       
    qsort(alljobs, jbcnt, sizeof(struct job), struct_cmp_by_product);

    
    
        for (int k = 0; k < jbcnt; k++)
        {
           if(r==0 && s==0){
            printf("[%d] %s %s [%d]\n", alljobs[k].job_no, alljobs[k].stat, alljobs[k].name, alljobs[k].pid);
            
           }
           else if(r==0 && s==1){
           if(!strcmp(alljobs[k].stat,"Stopped")){
               printf("[%d] %s %s [%d]\n", alljobs[k].job_no, alljobs[k].stat, alljobs[k].name, alljobs[k].pid);
           }

           }
           else if(r==1 && s==0){
               if(!strcmp(alljobs[k].stat,"Running")){
               printf("[%d] %s %s [%d]\n", alljobs[k].job_no, alljobs[k].stat, alljobs[k].name, alljobs[k].pid);
           }
        }}
    
    
}