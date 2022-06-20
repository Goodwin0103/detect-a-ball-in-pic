#include <stdio.h>
#include <stdlib.h>
 
struct ListNode{
    int value;
    ListNode* next;
};
 
 
ListNode* CreateListNode(int value){
    ListNode* pNode = new ListNode();
    pNode->value = value;
    pNode->next = NULL;
    return pNode;
}
 
void ConnectListNode(ListNode* pCurrent, ListNode* pNext){
    if(pCurrent == NULL){
        printf("Error to connect two nodes.\n");
        exit(1);
    }
 
    pCurrent->next = pNext;
}
 
void PrintListNode(ListNode* pNode){
    if(pNode == NULL)
        printf("The node is null.\n");
    else
        printf("The key in node is %d.\n", pNode->value);
}
 
void PrintList(ListNode* pHead){
    ListNode* pNode = pHead;
    while(pNode){
        printf("%d\t", pNode->value);
        pNode = pNode->next;
    }
 
    printf("\n");
}
 
void DestroyList(ListNode* pHead){
    ListNode* pNode = pHead;
    while(pNode){
        ListNode* pNext = pNode->next;
        delete pNode;
        pNode = pNext;
    }
}
 
void AddToTail(ListNode** pHead, int value){
    ListNode* pNode = new ListNode();
    pNode->value = value;
    pNode->next = NULL;
 
    if(*pHead == NULL)
        *pHead = pNode;
    else{
        ListNode* pCurrent = *pHead;
        while(pCurrent->next)
            pCurrent = pCurrent->next;
 
        pCurrent->next = pNode;
    }
}
 
void RemoveHead(ListNode** pHead, int value){
    if(pHead == NULL || *pHead == NULL)
        return;
 
    ListNode* pToBeDeleted = NULL;
    if((*pHead)->value == value){
        pToBeDeleted = *pHead;
        *pHead = (*pHead)->next;
    }else{
        ListNode* pNode = *pHead;
        while(pNode->next != NULL && pNode->next->value != value)
            pNode = pNode->next;
 
        if(pNode->next != NULL && pNode->next->value == value){
            pToBeDeleted = pNode->next;
            pNode->next = pNode->next->next;
        }
    }
 
    if(pToBeDeleted != NULL){
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
}