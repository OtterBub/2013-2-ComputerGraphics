#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int ELEMENT;

typedef struct _DATA{
	ELEMENT data;
	_DATA *link;
}DATA;

typedef struct _HEAD{
	DATA *head;
	DATA *tail;
}HEAD;

void InitHead(HEAD* h)
{
	h->head = NULL;
	h->tail = NULL;
}

DATA* SearchTail(HEAD* h)
{
	DATA *i = h->head;
	while(i->link != NULL) i = i->link;

	return i;
}

void AddListData(HEAD *h, ELEMENT data)
{
	DATA *p = h->head;
	DATA *temp = (DATA*)malloc(sizeof(DATA));
	temp->data = data;
	temp->link = NULL;
	

	if(h->head == NULL)
	{
		h->head = temp;
		h->tail = temp;
	}
	else
	{
		p = SearchTail(h);
		p->link = temp;
		h->tail = temp;
	}
}

void printfList(HEAD* h)
{
	DATA *p = h->head;

	if(h->head == NULL)
	{
		printf("List is Empty");
	}
	else
	{
		while(p->link != NULL) {
			printf("%d ", p->data);
			p = p->link;
		}
		printf("%d ", p->data);
	}
}

HEAD CreateList(int amount)
{
	HEAD temp;
	for(int i = 0; i < amount; i++)
	{
		AddListData(&temp, rand());
	}
	return temp;
}

void SearchMinMax(HEAD* h)
{
	DATA* p = NULL;
	DATA* old = NULL;
	ELEMENT Min = INT_MAX;
	ELEMENT Max = 0;

	p = h->head;
	old = p;

	while(p->link != NULL){
		if(Min > p->data)
		{
			Min = p->data;
		}
		if(Max < p->data)
		{
			Max = p->data;
		}
		old = p;
		p = p->link;
	}
	printf("Search Min and Max result\n Min : %d Max : %d\n");
}

void AscendingSort(HEAD* h)
{
	
}

void InascendingSort(HEAD* h)
{

}

int main()
{
	HEAD h;
	InitHead(&h);

	h = CreateList(50);

	printfList(&h);

	return 0;
}