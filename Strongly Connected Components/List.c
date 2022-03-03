/*********************************************************************************
* Julian Lafond, jmlafond
:wq
;wq
:wq
visual
:wq

q:a


* 2022 Winter CSE101 PA 3
* List.c
* List ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"


List newList()
{
    List L = (List)malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = L->index1 = 0;
    return L;
}


void freeList(List *pL)
{
	if ((*pL) == NULL)
	{
		fprintf(stderr, "Pointer to list is null");
		return;
	}
	
    Node cur = (*pL)->front;
    for(int i = 0; i < (*pL)->length;i++)
    {
	Node tmp = cur;
	cur = cur->next;
	free(tmp);
    }
    free(*pL);
    pL = NULL;
}

int length(List L)
{
    if (L == NULL)
    {
	fprintf(stderr, "List is empty");
    }	
    return L->length;
}


int front(List L)
{	
	if (L == NULL)
	{
		fprintf(stderr, "List is empty");
		exit(1);
	}
      if (length(L) < 0)
       {
	fprintf(stderr, "\nList Error: Calling Front() on an empty list");
	exit(1); 
        }
   return L->front->data;
}

int index(List L)
{
	if (L == NULL)
	{
		fprintf(stderr, "List is empty");
		exit(1);
	}
	else if (L->index1 < 0 || L->index1 >= length(L))
	{
		return -1;
	}
	else	
	{	
		return L->index1;
	}
}
			

int back(List L)
{
	if (L == NULL)
	{
		fprintf(stderr, "List is empty");
		exit(1);
	} 
    if (length(L) < 0)
    {
	fprintf(stderr, "\nList Error: calling Back() on an empty list");
    	exit(1);
	}

    return L->back->data;
}

int get(List L)
{	
	if (L == NULL)
	{
		fprintf(stderr, "Empty list");
		exit(1);
	}
	if ((length(L) <= 0) || (index(L) < 0))
	{
		fprintf(stderr, "Calling get() on empty list");	
		exit(1);
	}
	if (L->cursor == NULL)
	{
		return -1;
	}
	return L->cursor->data;
}

bool equals(List A, List B)
{
	if (A == NULL || B == NULL)
	{
		fprintf(stderr, "List is empty");
		exit(1);
	}
	Node cu = A->front;
	Node tm = B->front;
	while ((cu!= NULL) & (tm!= NULL))
	{
		if (cu->data != tm->data)
		{
			return false;
		}
		cu = cu->next;
		tm = tm->next;
	}
	return ((tm == NULL) & (cu == NULL));
}

void clear(List L)
{
	if (L == NULL)
	{
		fprintf(stderr, "List is empty");
		exit(1);
	}
	Node cur = L->front;
	while (cur!= NULL)
	{
		cur = cur->next;
		free(cur);	
	}
	L->front = L->back = L->cursor = NULL;
        L->length = L->index1 = 0;
}	

void set(List L, int x)
{
	if (L == NULL)
	{
		fprintf(stderr, "List is empty");
		exit(1);
	}
	else if (length(L) > 0 && index(L) >= 0)
	{
		L->cursor->data = x;
	}
}

void moveFront(List L)
{
	if (length(L) > 0) 
	{
		L->cursor = L->front;
		L->index1 = 0;
	}
}

void moveBack(List L)
{
	if (length(L) > 0)
	{
		L->cursor = L->back;
		L->index1 = length(L) - 1;
	}
}

void movePrev(List L)
{
	if (L->index1 >= 0 && L->cursor->prev!=NULL)
	{
		L->cursor = L->cursor->prev;
	}
	L->index1-=1;
}

void moveNext(List L)
{
	if (L->index1 >= 0 && L->cursor->next!=NULL)
	{
		L->cursor = L->cursor->next;
	}
	L->index1+=1;
}


void prepend(List L, int x) 
{
    if (length(L) == 0)
    {
	append(L,x);
    }
    else 
	{
		Node new_node = (Node)malloc(sizeof(NodeObj));
    		new_node->data = x;    
    		new_node->next = L->front;
		new_node->prev = NULL;
		L->front->prev = new_node;
		L->front = new_node;
		L->length+=1;
		L->index1+=1;
	}
}
void append(List L, int x)
{
	Node new_node = (Node)malloc(sizeof(NodeObj));
	new_node->data = x;		
	new_node->next = NULL;
	if (L->front == NULL)
	{
		new_node->prev = NULL;
		L->front = L->back = new_node;
		L->length+=1;
		return;
	}
	new_node->prev = L->back;
	L->back->next = new_node;	
	L->back = new_node;
	L->length+=1;	
	return;
}


void insertBefore(List L, int x)
{
	if (length(L) < 0 && index(L) <= 0)
        {
                fprintf(stderr, "\nList Error: calling insertBefore() on empty List");
                exit(1);
        }
        else
        {
                Node tmp = L->front;
                for (int i = 0; i < L->index1 - 1; i++)
                {
                        tmp = tmp->next;
                }
		if (L->index1 == 0)
                {       
                        prepend(L,x);
                }
                else if (L->index1 == length(L) - 1)
                {       
                        prepend(L,x);
                }
                else
                {
			Node new_node = (Node)malloc(sizeof(NodeObj));
                        new_node->data = x;
                        L->cursor->prev = new_node;
                        new_node->next = L->cursor;
                        tmp->next = new_node;
                        new_node->prev = tmp;
                        L->length+=1;
                }
	  }
}			

void insertAfter(List L, int x)
{
	if (length(L) < 0 && index(L) <= 0)
        {       
                fprintf(stderr, "\nList Error: Calling insertAfter() on empty list");
	}
        else    
        {		
		Node tmp = L->front;
		for (int i = 0; i < L->index1; i+=1)
		{
			
			tmp = tmp->next;
		}
		
		if (L->index1 < 0 || L->index1 >= L->length)
		{
			printf("We cannot insert since index is out of range\n");
		
		}
		else if (L->index1 == L->length - 1)
		{
			tmp = tmp->next;
			append(L,x);
		}
		
		else
		{	
			Node new_node = (Node)malloc(sizeof(NodeObj));
			tmp = tmp->next;
			new_node->data = x;
			tmp->prev = new_node;
			new_node->next = tmp;
			L->cursor->next = new_node;
			new_node->prev = L->cursor;
			L->length+=1;	
		}			
	}
}


void deleteFront(List L)
{	 
	Node tmp;
	if (L == NULL)
	{
		fprintf(stderr, "Empty List");
		exit(1);
	}
	else if (L->front->next == NULL)
	{
		free(L->front);
		L->front = NULL;
		L->back = NULL;	
		L->index1 = -1;
	}
	else
	{
		tmp = L->front;
		L->front = L->front->next;
		L->front->prev = NULL;
		free(tmp);
		if (L->index1 == 0)
		{
			L->index1 = -1;
		}
		L->index1-=1;
	}
	L->length-=1;				
}

void deleteBack(List L)
{
	Node tmp;
	if (L==NULL)
	{
		fprintf(stderr, "Empty List");
		exit(1);
	}
	else if (L->back->prev == NULL)
	{
		free(L->front);
		L->back = NULL;
		L->front = NULL;
		L->index1 = -1;
	}
	else
	{
		tmp = L->back;
		L->back = L->back->prev;
		L->back->next = NULL;
		free(tmp);
		if (L->index1 == length(L) - 1)
		{
			L->index1 = -1;
		}
	}
	L->length-=1;
}

void delete(List L)
{
	if (L == NULL)
	{
		fprintf(stderr, "List is empty");
		exit(1);
	}
	else if (L->index1 == 0)
	{
		moveFront(L);
		deleteFront(L);
		L->cursor = NULL;
	}
	else if (L->index1 == length(L) - 1)
	{
		moveBack(L);
		deleteBack(L);
		L->cursor = NULL;
	}
	else
	{
		L->cursor->next->prev = L->cursor->prev;
		L->cursor->prev->next = L->cursor->next;
		free(L->cursor);
		L->cursor = NULL;
	}
}


void printList(FILE *out, List L)
{
    Node new_node; 
    new_node = L->front; 
    while (new_node!=NULL)   
    {
	  
	fprintf(out, "%d ", new_node->data);    
        new_node = new_node->next;        
    }
}


List copyList(List L)
{
	if (L == NULL)
	{
		fprintf(stderr, "List is empty");
		exit(1);
	}
	List L1 = newList();
	Node cur = L->front;
	while (cur!=NULL)
	{
		append(L1, cur->data);
		cur = cur->next;
	}
	L1->cursor = NULL;
	return L1;


}
