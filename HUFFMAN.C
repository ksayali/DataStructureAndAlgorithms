/*	Name      :  Sayali Kothari
	Title	:  Implementation of Huffman's Algorithm   */


#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct Tree
{
	struct Tree *lchild;
	char label;
	int freq;
	char hcode[10];
	struct Tree *rchild;
};

struct sll
{
	struct Tree *tnode;
	struct sll *next;
};

struct queue
{
	struct Tree *tnode;
	struct queue *next;
};


void create(struct sll **,struct sll **);
int insertInTree(struct sll **,struct sll **,struct Tree *);
int buildTree(struct sll **,struct sll **,struct Tree **);
int removenode(struct sll **,struct sll **,struct Tree **);
void display(struct Tree *);
void allocHcode(struct Tree **);

int insertq(struct queue **,struct queue**,struct Tree*);
int deleteq(struct queue **,struct queue **,struct Tree **);
int qempty(struct queue *);

void deallocate(struct Tree **);

int main(void)
{
	struct sll *head = NULL;
	struct sll *last = NULL;
	struct Tree *root = NULL;
	int ch = 0;

	do
	{
		clrscr();
		printf("\n\n\t 1. Generate Huffman Code");
		printf("\n\n\t 2. Display Huffman Code");
		printf("\n\n\t 3. Exit");

		printf("\n\n\t Enter Your Choice : ");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1:
					if(root != NULL)
					{
						deallocate(&root);
					}
					create(&head,&last);
					buildTree(&head,&last,&root);
					break;

			case 2:
					display(root);
					break;

			case 3:
					deallocate(&root);
					break;

		}

		printf("\n\n\t Press Any Key To Continue...");
		fflush(stdin);
		getch();

	}while(ch != 3);

	return 0;
}

void create(struct sll **head,struct sll **last)
{
	struct Tree *trnode = NULL;
	char ans = '\0';

	do
	{
		trnode = (struct Tree *)calloc(1,sizeof(struct Tree));
		if(trnode == NULL)
		{
			ans = 'n';
		}
		else
		{
			printf("\n\n\t Enter label : ");
			fflush(stdin);
			scanf("%c",&trnode->label);

			printf("\n\t Enter Frequency : ");
			scanf("%d",&trnode->freq);

			insertInTree(head,last,trnode);
		}
		printf("\n\t Do You Want To Add More (Y/N) : ");
		fflush(stdin);
		scanf("%c",&ans);
	}while(ans == 'y' || ans == 'Y');

}

int buildTree(struct sll **head,struct sll **last, struct Tree **root)
{
	int succ = 0;
	struct Tree *tnode = NULL;

	do
	{
		*root = (struct Tree *)calloc(1,sizeof(struct Tree));
		if(*root == NULL)
		{
			succ = 0;
		}
		else
		{
			succ = removenode(head,last,&tnode);
			if(succ == 1)
			{
				(*root)->lchild = tnode;
				(*root)->freq = tnode->freq;
				succ = removenode(head,last,&tnode);
				if(succ == 0)
				{
				}
				else
				{
					(*root)->rchild = tnode;
					(*root)->freq = (*root)->freq + tnode->freq;
					if(succ == 1)
					{
						insertInTree(head,last,*root);
					}
					else
					{
						printf("Tree To Generate Huffman Code Is Created Successfully..");
					}
				}
			}
			else
			{
				if(succ == 0)
				{
					printf("\n\n\t Linked List Empty..");
				}
				else
				{
				}
			}
		}
	}while(succ != 2);
	allocHcode(root);

	return(succ);
}




int insertInTree(struct sll **head,struct sll **last, struct Tree *trnode)
{
	struct sll *newnode = NULL;
	struct sll *pnode = NULL;
	struct sll *temp = NULL;
	int succ = 0;

	newnode = (struct sll*)calloc(1,sizeof(struct sll));
	if(newnode == NULL)
	{
		succ = 0;
	}
	else
	{
		newnode->tnode = trnode;
		if(*head == NULL)
		{
			*head = newnode;
			*last = newnode;
		}
		else
		{
			temp =  *head;
			while(temp != NULL)
			{
				if(trnode->freq < (temp->tnode)->freq)
				{
					if(temp == *head)
					{
						newnode->next = *head;
						*head = newnode;
					}
					else
					{
						pnode->next=newnode;
						newnode->next=temp;
					}
					temp=NULL;
				}
				else
				{
					pnode=temp;
					temp=temp->next;
				}
			}

			if(newnode->next==NULL)
			{
				(*last)->next=newnode;
				(*last)=newnode;
			}
		}
		succ = 1;
	}
	return(succ);

}


int removenode(struct sll **head,struct sll **last, struct Tree **ptnode)
{
	int succ = 0;
	struct sll *dnode = NULL;

	if(*head == NULL)
	{
		succ = 0;
	}
	else
	{
		*ptnode = (*head)->tnode;
		dnode = *head;
		if(*head == *last)
		{
			*head = NULL;
			*last = NULL;
			succ = 2;
		}
		else
		{
			*head = (*head)->next;
			succ = 1;
		}
		dnode->next = NULL;
		free(dnode);
		dnode = NULL;
	}
	return(succ);
}



int insertq(struct queue **rear,struct queue **front, struct Tree *pnode)
{
	int succ = 0;
	struct queue *newnode = NULL;

	newnode = (struct queue *)calloc(1,sizeof(struct queue));

	if(newnode == NULL)
	{
		succ = 0;
	}
	else
	{
		newnode->tnode = pnode;

		if(*rear == NULL)
		{
			*rear = newnode;
			*front = newnode;
		}
		else
		{
			(*rear)->next = newnode;
			*rear = newnode;
		}
		succ = 1;
	}

	return(succ);
}



int deleteq(struct queue **rear,struct queue **front, struct Tree **pnode)
{
	int succ = 0;
	struct queue *dnode = NULL;

	if(*front == NULL)
	{
		succ = 0;
	}



	else
	{
		dnode = *front;
		*pnode = dnode->tnode;

		if(*front == *rear)
		{
			*front = NULL;
			*rear = NULL;
		}
		else
		{
			*front = (*front)->next;
		}
		dnode->next = NULL;
		free(dnode);
		dnode = NULL;
		succ = 1;
	}
	return(succ);
}


int qempty(struct queue *front)
{
	int succ = 0;
	if(front == NULL)
	{
		succ = 1;
	}
	else
	{
		succ = 0;
	}
	return(succ);
}


void allocHcode(struct Tree **root)
{
	struct queue *front = NULL;
	struct queue *rear = NULL;
	struct Tree *troot = NULL;
	char code[2] = {'\0'};

	troot = *root;

	do
	{
		code[0] = '0';
		code[1] = '\0';

		if(troot->lchild != NULL)
		{
			strcat((troot->lchild)->hcode,troot->hcode);
			strcat((troot->lchild)->hcode,code);
		}
		insertq(&rear,&front,troot->lchild);

		code[0] = '1';
		code[1] = '\0';

		if(troot->rchild != NULL)
		{
			strcat((troot->rchild)->hcode,troot->hcode);
			strcat((troot->rchild)->hcode,code);
		}
		insertq(&rear,&front,troot->rchild);

		do
		{
			deleteq(&rear,&front,&troot);
		}while(troot == NULL && qempty(front) != 1);

	}while(troot != NULL || qempty(front) != 1);
	root = &troot;
}

void display(struct Tree *root)
{
	if(root != NULL)
	{
		display(root->lchild);

		if(root->lchild == NULL && root->rchild == NULL)
		{
			printf("\n\t %2c %3d %s",root->label, root->freq,root->hcode);
		}

		display(root->rchild);
	}
}



void deallocate(struct Tree **root)
{
	struct Tree *dnode = NULL;
	 if(*root != NULL)
	 {
		deallocate(&((*root)->lchild));
		deallocate(&((*root)->rchild));
		dnode = *root;
		dnode->lchild = NULL;
		dnode->rchild = NULL;
		free(dnode);
		dnode = NULL;
	 }
}
