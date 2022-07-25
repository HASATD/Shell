#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAX 10


int cmp ( const void *pa, const void *pb ) {
   const char **ia = pa;
    const char **ib = pb;
    return strcmp(*ia+1, *ib+1);
}

int main ( ) {
    char *a[4][2]={{"satya","aytas"},{"haasa","asaah"},{"dev","ved"},{"apple","elppa"}};
    int r,c;
    
    
    qsort( a, 4,sizeof(char *), cmp );
    
    for(int i=0;i<4;i++){
        
      printf("%s %s\n",a[i][0],a[i][1]);
    }
    return 0;
}