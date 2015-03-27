#include <stdio.h>
#include <malloc.h>

typedef struct _POSITION{
	double x;
	double y;
	double z;
}POSITION;

typedef POSITION ELEMENT;
//typedef int ELEMENT;

ELEMENT InitElement(double x, double y, double z)
{
	ELEMENT temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	return temp;
}

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

void PrintfList(HEAD* h)
{
	DATA *p = h->head;

	if(h->head == NULL)
	{
		printf("List is Empty \n");
	}
	else
	{
		while(p->link != NULL) {
			printf("%d ", p->data);
			p = p->link;
		}
		printf("%d \n", p->data);
	}
}

int GetListLength(HEAD* h)
{
	DATA *p = h->head;
	int length = 1;

	if(h->head == NULL)
	{
		printf("List is Empty \n");
		return 0;
	}
	else
	{
		while(p->link != NULL) {
			length++;
			p = p->link;
		}
	}
	return length;
}

void EnQueue(HEAD* h, ELEMENT d)
{
	AddListData(h, d);
}

ELEMENT DeQueue(HEAD* h)
{
	ELEMENT temp;
	temp.x = 0;
	temp.y = 0;
	temp.z = 0;
	if(h->head != NULL)
	{
		temp = h->head->data;
		h->head = h->head->link;
		return temp;
	}
	else
	{
		printf("Queue is Empty\n");
		return temp;
	}
	
}

void Push(HEAD* h, ELEMENT d)
{
	AddListData(h, d);
}

ELEMENT Pop(HEAD* h)
{
	DATA *p = NULL;
	DATA *old = NULL;
	ELEMENT temp = {0, 0, 0};
	if(h->tail != NULL && h->head != NULL)
	{
		p = h->head;

		if(h->head->link == NULL){
			//printf("Pop %d\n", h->head->data);
			temp = h->head->data;
			h->tail = NULL;
			h->head = NULL;
			return temp;
		}
		else{
			//printf("Pop %d\n", h->tail->data);
			temp = h->tail->data;
		}

		while(p->link != NULL){
			old = p;
			p = p->link;
		}

		p = NULL;
		h->tail = old;
		old->link = NULL;
		
		return temp;
	}
	else
	{
		printf("ERROR : Stack is Empty\n");
		return temp;
	}
}

int main()
{
	HEAD Stack;
	HEAD Queue;

	ELEMENT data;

	char select = '\0';

	InitHead(&Stack);
	InitHead(&Queue);

	while(select != 'q' && select != 'Q')
	{
		printf("\n Select Menu\n");
		printf("(Q)uit, (E)nqueue, (D)equeue, (+)Push, (-)Pop \n");
		select = getchar();
		printf("Select is %c\n", select);

		switch(select)
		{
		case 'Q':
		case 'q':
			printf("\nProgram quit\n");
			break;
		case 'E':
		case 'e':
			printf("\nEnqueue \n");
			scanf("%lf %lf %lf", &data.x, &data.y, &data.z);
			EnQueue(&Queue, data);
			break;
		case 'D':
		case 'd':
			printf("\nDequeue \n");
			data = DeQueue(&Queue);
			printf("%f %f %f", data.x, data.y, data.z);
			break;
		case '+':
			printf("\nPush \n");
			scanf("%lf %lf %lf", &data.x, &data.y, &data.z);
			Push(&Stack, data);
			break;
		case '-':
			printf("\nPop \n");
			data = Pop(&Stack);
			printf("%f %f %f", data.x, data.y, data.z);
			break;
		case 'c':
		case 'C':
			InitHead(&Stack);
			InitHead(&Queue);
			break;
		case 'L':
		case 'l':
			printf("Queue length : %d \n", GetListLength(&Queue));
			printf("Stack length : %d \n", GetListLength(&Stack));
			break;
		default:
			printf("\nplease select only \"q(Q), e(E), d(D), +, - \n");
		}
		fflush(stdin);
	}
}