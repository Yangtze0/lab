#ifndef _LINK_TABLE_H_
#define _LINK_TABLE_H_

#include<pthread.h>

typedef struct Node
{
    struct Node *pNext;
}tNode;

typedef struct LinkTable
{
    tNode *pHead;
    tNode *pTail;
    int SumOfNode;
    pthread_mutex_t mutex;
}tLinkTable;

tLinkTable *Cre_LT();
int Del_LT(tLinkTable *);

int Add_Node(tLinkTable *, tNode *);
int Del_Node(tLinkTable *, tNode *);

tNode *Get_Head(tLinkTable *);
tNode *Get_Next(tLinkTable *, tNode *);

#endif
