#include<stdio.h>
#include<stdlib.h>
#include"linktable.h"

tLinkTable *Cre_LT()
{
    tLinkTable *pLinkTable = (tLinkTable *)malloc(sizeof(tLinkTable));
    if(pLinkTable == NULL)
    {
	return NULL;
    }
    pLinkTable->pHead = NULL;
    pLinkTable->pTail = NULL;
    pLinkTable->SumOfNode = 0;
    pthread_mutex_init(&(pLinkTable->mutex), NULL);
    return pLinkTable;
}

int Del_LT(tLinkTable *pLinkTable)
{
    if(pLinkTable == NULL)
    {
	return -1;
    }
    while(pLinkTable->pHead != NULL)
    {
	tNode *p = pLinkTable->pHead;
	pthread_mutex_lock(&(pLinkTable->mutex));
	pLinkTable->pHead = pLinkTable->pHead->pNext;
	pLinkTable->SumOfNode -= 1;
	pthread_mutex_unlock(&(pLinkTable->mutex));
	free(p);
    }
    pLinkTable->pHead = NULL;
    pLinkTable->pTail = NULL;
    pLinkTable->SumOfNode = 0;
    pthread_mutex_destroy(&(pLinkTable->mutex));
    free(pLinkTable);
    return 0;
}

int Add_Node(tLinkTable *pLinkTable, tNode *pNode)
{
    if(pLinkTable == NULL || pNode == NULL)
    {
	return -1;
    }
    pNode->pNext = NULL;
    pthread_mutex_lock(&(pLinkTable->mutex));
    if(pLinkTable->pHead == NULL)
    {
	pLinkTable->pHead = pNode;
    }
    if(pLinkTable->pTail == NULL)
    {
	pLinkTable->pTail = pNode;
    }
    else
    {
	pLinkTable->pTail->pNext = pNode;
	pLinkTable->pTail = pNode;
    }
    pLinkTable->SumOfNode += 1;
    pthread_mutex_unlock(&(pLinkTable->mutex));
    return 0;
}    

int Del_Node(tLinkTable *pLinkTable, tNode *pNode)
{
    if(pLinkTable == NULL || pNode == NULL)
    {
	return -1;
    }
    pthread_mutex_lock(&(pLinkTable->mutex));
    if(pLinkTable->pHead == pNode)
    {
	pLinkTable->pHead = pLinkTable->pHead->pNext;
	pLinkTable->SumOfNode -= 1;
	if(pLinkTable->SumOfNode == 0)
	{
	    pLinkTable->pTail = NULL;
	}
	pthread_mutex_unlock(&(pLinkTable->mutex));
	return 0;
    }
    tNode *pTempNode = pLinkTable->pHead;
    while(pTempNode != NULL)
    {
	if(pTempNode->pNext == pNode)
	{
	    pTempNode->pNext = pTempNode->pNext->pNext;
	    pLinkTable->SumOfNode -= 1;
	    if(pLinkTable->SumOfNode == 0)
	    {
		pLinkTable->pTail = NULL;
	    }
	    pthread_mutex_unlock(&(pLinkTable->mutex));
	    return 0;
	}
	pTempNode = pTempNode->pNext;
    }
    pthread_mutex_unlock(&(pLinkTable->mutex));
    return -1;
}

tNode *Get_Head(tLinkTable *pLinkTable)
{
    if(pLinkTable == NULL)
    {
	return NULL;
    }
    return pLinkTable->pHead;
}

tNode *Get_Next(tLinkTable *pLinkTable, tNode *pNode)
{
    if(pLinkTable == NULL || pNode == NULL)
    {
	return NULL;
    }
    tNode *pTempNode = pLinkTable->pHead;
    while(pTempNode != NULL)
    {
	if(pTempNode == pNode)
	{
	    return pTempNode->pNext;
	}
	pTempNode = pTempNode->pNext;
    }
    return NULL;
}
