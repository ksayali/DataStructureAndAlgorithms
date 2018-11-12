/*   NAME    : Sayali S. Kothari
	Roll no : 2621
	Title   : DFS-BFS of Graph     */


#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

struct vertex
{
	int value;
	struct vertex * next;
	struct vertex * prev;
};
struct queue
{
	int data;
	struct queue *next;
};
struct stack
{
	struct stack *next;
	int data;
};


int menu(void);
int empty(struct queue * head);
int dequeue(struct queue **head,int *xdata);
int enqueue(struct queue **head,struct queue **last,int xdata);
int stackempty(struct stack **last);
int push(struct stack **last,int c);
int pop(struct stack **s2,int *pop_ele);

int creategraph(struct vertex *G[]);
int insert(int v1,int v2,struct vertex *G[]);
int dispchain(struct vertex *head[10]);
int BFS(int vert,struct vertex *G[]);
int DFS(int i,struct vertex *G[]) ;

int adjmatrix(int n,int mat[15][15]);
int BFSmat(int vert,int mat[][15]);
int DFSmat(int vert,int mat[][15]);
int create();

int main(void)
{
	int ch=0;
	int v=0;
	int mat[15][15];
	int n=0;
	int i,j=0;
	struct vertex *head[15]={NULL};
//	struct vertex *q=NULL;
	int choice=0;
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			mat[i][j]=0;
		}
	}
	clrscr();
	do
	{
		ch=menu();
		clrscr();
		switch(ch)
		{
			case 1: printf("\n1.Create by adjacency list\n 2.Create by adjacency matrix\nEnter Choice:");
				scanf("%d",&choice);
				if(choice==1)
				{
					creategraph(head);

				}
				else if(choice==2)
				{
					n=create();
					adjmatrix(n,mat);
				}
				else
				{
					printf("\nInvalid Choice!");
				}
				break;
			case 2: if(choice==1)
				{
					printf("\nEnter the vertex:");
					scanf("%d",&v);
					printf("\n\nThe BFS is:");
					BFS(v,head);
				}
				else if(choice==2)
				{
					printf("\nEnter the vertex:");
					scanf("%d",&v);
					printf("\n\nThe BFS is:");
					BFSmat(v,mat);
				}
				else
				{
					printf("\nError:Graph not created!");
				}
				break;
			case 3: if(choice==1)
				{
					printf("\nEnter the vertex:");
					scanf("%d",&v);
					printf("\n\nThe DFS is:");
					DFS(v,head);
				}
				else if(choice==2)
				{
					printf("\nEnter the vertex:");
					scanf("%d",&v);
					printf("\n\nThe DFS is:");
					DFSmat(v,mat);
				}
				else
				{
					printf("\nError:Graph not created!");
				}
				break;
		}
	}while(ch!=4);
	getch();
	return 0;
}

int menu(void)
{
	int choice=0;
	do
	{
		printf("\nMenu\n");
		printf("\n1.Create");
		printf("\n2.BFS");
		printf("\n3.DFS");
		printf("\n4.Exit");
		printf("\nEnter Choice::");
		scanf("%d",&choice);
	}while(choice<0||choice>4);
	return choice;
}


int creategraph(struct vertex *G[])
{
	int i=0;
	int vi=0;
	int vj=0;
	int noe=0;
	int n=0;
	printf("\nEnter the number of vertices:");
	scanf("%d",&n);
	printf("\nEnter the number of edges:");
	scanf("%d",&noe);
	for(i=0;i<noe;i++)
	{
		printf("\nEnter an edge (vertex i, vertex j):");
		scanf("%d %d",&vi,&vj);
		insert(vi,vj,G);
		insert(vj,vi,G);
	}
	return 0;
}

int insert(int v1,int v2,struct vertex *G[])
{
	struct vertex *p=NULL;
	struct vertex *q=NULL;
	q=(struct vertex *)calloc(1,sizeof(struct vertex));
	q->value=v2;
	q->next=NULL;
	if(G[v1]==NULL)
	{
		G[v1]=q;
	}
	else
	{
		p=G[v1];
		while(p->next!=NULL)
		{
			p=p->next;
		}
		p->next=q;
		q->prev=p;
	}
	return 0;
}

/*int dispchain(struct vertex *head[10])
{
	int loc=0;
	struct vertex *q=NULL ;
	for(loc=0;loc<10;loc++)
	{
		printf("\n");
		q = head[loc] ;
		if(q!=NULL)
		{
			printf("%d->",loc);
		}
		while(q!=NULL)
		{
			if(q->next!=NULL)
			{
				printf("%d->",q->value);
			}
			else
			{
				printf("%d",q->value);
			}
			q=q->next;
		}
	}
	return 0;
} */

int enqueue(struct queue **head,struct queue **last,int xdata)
{
	struct queue *newnode=NULL;
	newnode=(struct queue *)calloc(1,sizeof(struct queue));
	newnode->data=xdata;
	newnode->next=NULL;
	if(*head==NULL)
	{
		*head=*last=newnode;
	}
	else
	{
		(*last)->next=newnode;
		(*last)=(*last)->next;
	}
	return 0;
}

int dequeue(struct queue **qhead,int *xdata)
{
	struct queue *temp;
	int succ=0;
	if(qhead==NULL)
	{
		succ=0;
	}
	else
	{
		temp=(*qhead);
		*xdata = temp->data;
		(*qhead)=(*qhead)->next;
		free(temp);
		temp=NULL;
		succ=1;
	}
	return succ;
}
int empty(struct queue * head)
{
	int emp=0;
	if(head==NULL)
	{
		emp=1;
	}
	else
	{
		emp=0;
	}
	return emp;
}

int BFS(int vert,struct vertex *G[])
{

	int w=0;
	int visited[20]={0};
	struct queue *head=NULL;
	struct queue *last=NULL;
	struct vertex *node=NULL;
	enqueue(&head,&last,vert);
	visited[vert]=1;
	printf("%d\t",vert);
	while(empty(head)!=1)
	{
		dequeue(&head,&vert);
		for(node=G[vert];node!=NULL;node=node->next)
		{
			w=node->value;
			if(visited[w]==0)
			{
				enqueue(&head,&last,w);
				visited[w]=1;
				printf("%d\t",w);
			}
		}
	}
	return 0;
}

int push(struct stack **last,int c)
{
	struct stack *newnode=NULL;
	newnode=(struct stack *)calloc(1,sizeof(struct stack));
	newnode->data=c;
	newnode->next=NULL;
	if(*last==NULL)
	{
		*last=newnode;
	}
	else
	{
		newnode->next= * last;
		*last=newnode;
	}
	return 0;
}

int pop(struct stack **s2,int *pop_ele)
{
	struct stack *temp=NULL;
	temp=*s2;
	*pop_ele=(*s2)->data;
	*s2=(*s2)->next;
	temp->next=NULL;
	free(temp);
	temp=NULL;
	return 0;
}

int stackempty(struct stack **last)
{
	int empty=0;
	if(*last==NULL)
	{
		empty=1;
	}
	else
	{
		empty=0;
	}
	return empty;
}

int DFS(int vert,struct vertex *G[])
{
	int visited[20]={0};
	struct stack *last=NULL;
	struct vertex *p=NULL;
	int i=0;
	push(&last,vert);
	while(stackempty(&last)!=1)
	{

		pop(&last,&vert);
		i=vert;
		if(visited[i]==0)
		{
			 printf("%d\t",vert);
			 visited[i]=1;
			 for(p=G[i];p->next!=NULL;p=p->next);
			 while(p!=NULL)
			{
				i=p->value;
				if(visited[i]==0)
				{
					push(&last,i);
				}
				p=p->prev;
			}

		}
	}
	return 0;
}
int adjmatrix(int n,int mat[15][15])
{
//	struct vertex * p=NULL;
//	struct vertex * q=NULL;
	int x=9,y=6;

//	char ch ='\0';
	int i=0;
	int j=0;
//	int visited[15]={0};

	for(i=0;i<n;i++)
	{
		printf("\t%d",i);
	}

	for(i=0;i<n;i++)
	{

		printf("\n%d",i);
		y=y+2;
		for(j=0;j<n;j++)
		{
			gotoxy(x,y);
			scanf("%d",&mat[i][j]);
			x=x+8;

		}
		x=x-(8*j);
	}

	return n;
}



int BFSmat(int vert,int mat[][15])
{

	int w=0;
	int visited[20]={0};
	struct queue *head=NULL;
	struct queue *last=NULL;
	int node=0;
	enqueue(&head,&last,vert);
	visited[vert]=1;
	printf("%d\t",vert);
	while(empty(head)!=1)
	{
		dequeue(&head,&vert);
		node=0;
		for(w=mat[vert][node];node<10;node=node+1)
		{
			w=node;
			if(visited[w]==0 &&(mat[vert][node]!=0))
			{
				enqueue(&head,&last,w);
				visited[w]=1;
				printf("%d\t",w);
			}
		}
	}
	return 0;
}

int create()
{
	int n=0;
//	int i=0;
//	struct vertex *temp=NULL;
	printf("\nEnter the number of vertices:");
	scanf("%d",&n);
	return n;
}

int DFSmat(int vert,int mat[][15])
{
	int visited[20]={0};
	int lastele[20]={0};
	struct stack *last=NULL;
	int w=0;
	int i=0;
	int j=0;
	int node=0;
	int matj[15]={0};
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			if(mat[i][j]!=0)
			{
				lastele[i]=mat[i][j];
				matj[i]=j;
			}
		}
	}
	push(&last,vert);
	while(stackempty(&last)!=1)
	{
		pop(&last,&vert);
		w=vert;
		if(visited[w]==0)
		{
			 printf("%d\t",w);
			 visited[w]=1;
			 node=matj[w];
			 i=node;
			 while(i>0)
			 {
			i=node;
			if(visited[i]==0&&mat[vert][i]!=0)
			{
				push(&last,i);
			}
			node=node-1;
			 }
		}
	}
	return 0;
}
