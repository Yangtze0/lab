#include "linktable.h"

#define CMD_MAX_LEN 128
#define DESC_LEN    1024
#define CMD_NUM     10

int Help();
int Quit();

typedef struct DataNode
{
    tNode *pNext;
    char *cmd;
    char *desc;
    int (*handler)();
}tDataNode;

tDataNode *FindCmd(tLinkTable *head, char *cmd)
{
    tDataNode *pNode = (tDataNode *)Get_Head(head);
    while(pNode != NULL)
    {
	if(strcmp(pNode->cmd, cmd) == 0)
	{
	    return pNode;
	}
	pNode = (tDataNode *)Get_Next(head, (tLinkTable *)pNode);
    }
    return NULL;
}

int ShowAllCmd(tLinkTable *head)
{
    tDataNode *pNode = (tDataNode *)Get_Head(head);
    while(pNode != NULL)
    {
	printf("%s - %s\n", pNode->cmd, pNode->desc);
	pNode = (tDataNode *)Get_Next(head, (tLinkTable *)pNode);
    }
    return 0;
}

int Init(tLinkTable **ppLinkTable)
{
    *ppLinkTable = Cre_LT();
    tDataNode *pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "help";
    pNode->desc = "Menu List:";
    pNode->handler = Help;
    Add_Node(*ppLinkTable, (tNode *)pNode);
    pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "version";
    pNode->desc = "Menu Program V1.0";
    pNode->handler = NULL;
    Add_Node(*ppLinkTable, (tNode *)pNode);
    pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "quit";
    pNode->desc = "Quit from Menu Program V1.0\n";
    pNode->handler = Quit;
    Add_Node(*ppLinkTable, (tNode *)pNode);
    return 0;
}

tLinkTable *head = NULL;

void main()
{
    Init(&head);
    while(1)
    {
	char cmd[CMD_MAX_LEN];
	printf("Input a cmd number > ");
	scanf("%s", cmd);
	tDataNode *p = FindCmd(head, cmd);
	if(p == NULL)
	{
	    printf("This is a wrong cmd!\n");
	    continue;
	}
	printf("%s - %s\n", p->cmd, p->desc);
	if(p->handler != NULL)
	{
	    p->handler();
	}
    }
}

int Help()
{
    ShowAllCmd(head);
    return 0;
}

int Quit()
{
    exit(0);
}
