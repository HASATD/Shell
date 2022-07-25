#include "headers.h"

#ifndef __LS_H
#define __LS_H

void print_details(char *file_path,char *dir_name);
void impl_ls(char **args);
int checkIfFileExists(const char* filename);
#endif