#include "headers.h"
#ifndef __LL_H
#define __LL_H

struct Node *insertNode(pid_t pid, char name[],int job_no);
struct Node* delete(pid_t pid);
struct Node* find(pid_t pid);
struct Node *findbyno(int job_no);
#endif
