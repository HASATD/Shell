#include "linked_list.h"

struct Node *current = NULL;

struct Node *insertNode(pid_t pid, char name[],int job_no)
{
    struct Node *link = (struct Node *)malloc(sizeof(struct Node));
    struct Node *temp = head;

    link->pid = pid;
    strcpy(link->name, name);
    link->job_no = job_no;
    
    link->next = NULL;

    if (head == NULL)
    {
        head = link;
        return head;
    }

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = link;
    return head;
}

struct Node *delete (pid_t pid)
{

    struct Node *current = head;
    struct Node *previous = NULL;

    if (head == NULL)
    {
        return NULL;
    }

    while (current->pid != pid)
    {

        if (current->next == NULL)
        {
            return NULL;
        }
        else
        {

            previous = current;

            current = current->next;
        }
    }

    if (current == head)
    {

        head = head->next;
    }
    else
    {

        previous->next = current->next;
    }

    return current;
}
struct Node *find(pid_t pid)
{

    struct Node *current = head;

    if (head == NULL)
    {
        return NULL;
    }

    while (current->pid != pid)
    {

        if (current->next == NULL)
        {
            return NULL;
        }
        else
        {

            current = current->next;
        }
    }

    return current;
}

struct Node *findbyno(int job_no)
{

    struct Node *current = head;

    if (head == NULL)
    {
        return NULL;
    }

    while (current->job_no != job_no)
    {

        if (current->next == NULL)
        {
            return NULL;
        }
        else
        {

            current = current->next;
        }
    }

    return current;
}