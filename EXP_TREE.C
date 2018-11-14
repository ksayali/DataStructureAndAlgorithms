/*	Name     :  Sayali S. Kothari
	Title    :  Creating an Expression Tree & Performing 
  Different Recursive and Non-Recursive 
  Traversals on it */

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

// Structure for postfix string creation
struct stack
{
	char data;
	struct stack *next;
};


// Struture for tree Creation
struct Tree
{
	struct Tree *lchild ;
	char data ;
	struct Tree *rchild ;
};

struct TreeStk
{
	struct Tree *tnode;
	struct TreeStk *next;
};

int push(struct stack **,char);
int pop(struct stack **,char *);
int isempty(struct stack *);
int intopost(char[],char[]);
int valid(char[]);
int priority(char);
int menu(void);
int submenu(void);
int pusht(struct TreeStk **, struct Tree *);
int popt(struct TreeStk **, struct Tree **);
int stackempty(struct TreeStk *);
int createTree(struct Tree **,char[]);
void inorder_r(struct Tree *) ;
void inorder_nr(struct Tree *);
void preorder_r(struct Tree *);
void preorder_nr(struct Tree *);
void postorder_r(struct Tree *);
void postorder_nr(struct Tree *);
struct Tree * getStackTop(struct TreeStk *);
void deallocate(struct Tree **);
int main(void)
{
	int succ = 0 ;
	int ch = 0 ;
	int subch = 0;
	int v = 0;
	char instring[50] = {'\0'};
	char post[50] = {'\0'};
	struct Tree *root = NULL ;

	do
	{
		clrscr() ;
		ch = menu() ;
		switch(ch)
		{
			case 1:

				if(root != NULL)
				{
					deallocate(&root);
				}
				printf("\n\t Enter the Infix Expression : ");
				fflush(stdin);
				scanf("%s",instring);

				do
				{
					v = valid(instring);
					if(v == 0)
					{
						printf("\n\t Entered Expression Is Invalid.. Re-enter It : ");
						fflush(stdin);
						scanf("%s",instring);
					}
				}while(v == 0);

				succ = intopost(instring,post);

				if(succ == 0)
				{
					printf("\n\t Error : In Conversion");
				}
				else
				{
					printf("\n Postfix string is : %s",post);

					succ = createTree(&root,post);



					if(succ == 1)
					{
						printf("\n\t Tree created Successfully...");
					}
					else
					{
						printf("\n\t Error : Error In Tree Creation..");
					}
				}
				break;

			case 2:
				if (root == NULL)
				{
					printf("\n\t Tree Not Exist...");
				}
				else
				{
					do
					{
						subch = submenu();
						switch(subch)
						{
						   case 1:
							printf("Inorder Traversal : ");
							inorder_r(root);
							break;

						   case 2:
							printf("Inorder Traversal : ");
							inorder_nr(root);
							break;

						   case 3:
							printf("\n\n\t Switching Back To Main Menu..");
							break;
						}
					}while(subch != 3);
				}

				break ;

			case 3:

				if (root == NULL)
				{
					printf("\n\t Tree Not Exist...");
				}

				else
				{
					do
					{
						subch = submenu();
						switch(subch)
						{
						   case 1:
							printf("Preorder Traversal :");
							preorder_r(root);
							break;

						   case 2:
							printf("Preorder Traversal :");
							preorder_nr(root);
							break;

						   case 3:
							printf("\n\n\t Switching Back To Main Menu..");
							break;
						}
					}while(subch != 3);
				}
				break ;

			case 4:
				if (root == NULL)
				{
					printf("\n\t Tree Not Exist...");
				}
				else
				{
					do
					{
						subch = submenu();
						switch(subch)
						{
						   case 1:
							printf("Postorder Traversal:");
							postorder_r(root);
							break;

						   case 2:
							printf("Postorder Traversal:");
							postorder_nr(root);
							break;

						   case 3:
							printf("\n\n\t Switching Back To Main Menu..");
							break;
						}
					}while(subch != 3);
				}
				break ;

			case 5:
				deallocate(&root);
				break;
		}

		printf ("\n\n Press Any Key To Continue ...");
		fflush(stdin) ;
		getch() ;

	}while(ch != 5);

	return 0 ;
}

int menu(void)
{
	int ch = 0 ;
	do
	{
		printf("\n\n\t\t\t Expression Tree & Traversals..");
		printf("\n\n\t  1 : Create The Tree        \
				\n\n\t  2 : Inorder Traversal      \
				\n\n\t  3 : Preorder	Traversal  \
				\n\n\t  4 : Postorder Traversal    \
				\n\n\t  5 : Exit ");
		printf("\n\n\t Enter Your choice : ");
		scanf("%d",&ch);
	}while(ch < 1 || ch > 5);

	return(ch);
}

int submenu(void)
{
	int subch = 0 ;
	do
	{
		printf("\n\n\t\t  1 : Recursive	          \
				  \n\n\t\t  2 : Non - Recursive     \
				  \n\n\t\t  3 : Switch to Main Menu ");
		printf("\n\n\t\t Enter Your sub choice : ");
		scanf("%d", &subch);
	}while(subch < 1 || subch > 4);

	return(subch);
}


int pusht(struct TreeStk **last,struct Tree *pnode)
{
	int succ = 0;
	struct TreeStk *newnode = NULL;

	newnode = (struct TreeStk *)calloc(1,sizeof(struct TreeStk));

	if(newnode == NULL)
	{
		succ = 0;
	}

	else
	{
		newnode->tnode=pnode;

		if(*last != NULL)
		{
			newnode->next = (*last);
		}
		*last = newnode;
		succ = 1;
	}
	return(succ);
}


int popt(struct TreeStk **last, struct Tree **pnode)
{
	int succ = 0;
	struct TreeStk *dnode = NULL;

	if(*last == NULL)
	{
		succ = 0;
	}
	else
	{
		dnode = *last;
		*pnode = dnode->tnode;
		*last = (*last)->next;
		dnode->next = NULL;
		free(dnode);
		dnode = NULL;
		succ = 1;
	}
	return(succ);
}



int stackempty(struct TreeStk *last)
{
	 int succ = 0 ;
	 if(last == NULL)
	 {
		succ = 1 ;  // i.e. stack is empty
	 }
	 else
	 {
		 succ = 0;
	 }
	 return(succ);
}

int createTree(struct Tree **root,char postfix[])
{
	int succ = 0;
	int i = 0;
	struct Tree *newnode = NULL;
	struct Tree *opnd1 = NULL;
	struct Tree *opnd2 = NULL;
	struct TreeStk *top = NULL;

	while(postfix[i] != '\0')
	{
		newnode = (struct Tree *)calloc(1,sizeof(struct Tree));

		if(newnode == NULL)
		{
			succ = 0;
		}
		else
		{
			newnode->data = postfix[i];
			if((postfix[i]>96 && postfix[i]<122) 
||(postfix[i]>64 && postfix[i]<91))
			{
				succ = pusht(&top,newnode);
				if(succ == 0)
				{
					printf("\n\t\t Error : Error in pushing data..");
				}
				else
				{

				}
			}
			else
			{
				succ = popt(&top,&opnd2);
				succ = popt(&top,&opnd1);
				newnode->lchild = opnd1;
				newnode->rchild = opnd2;
				succ = pusht(&top,newnode);
			}
		}
		i++;
	}
	succ = popt(&top,root);
	return(succ);
}

void inorder_r(struct Tree *node)
{
	if (node != NULL)
	{
		inorder_r(node->lchild) ;
		printf (" %2c", node->data) ;
		inorder_r(node->rchild) ;
	}
}

void inorder_nr(struct Tree *root)
{
	 int succ =0;
	 struct TreeStk *last =NULL;
	 struct Tree *temp = NULL;
	 temp = root;
	 do
	 {
		while(temp != NULL)
		{
			succ = pusht(&last,temp);
			if(succ == 0)
			{
			}
			else
			{
				temp = temp->lchild ;
			}
		}
		if(stackempty(last) != 1)
		{
			 succ = popt(&last,&temp);
			 if(succ == 1)
			 {
				printf(" %2c", temp->data);
				temp = temp->rchild ;
			 }
		}
	 }while(temp!=NULL || stackempty(last) != 1) ;

}





void preorder_r(struct Tree *root)
{
	if(root != NULL)
	{
		printf(" %2c", root->data) ;
		preorder_r(root->lchild) ;
		preorder_r(root->rchild) ;
	}
}

void preorder_nr(struct Tree *root)
{
	struct TreeStk *last =NULL;
	struct Tree *temp = NULL;
	int succ = 0;

	temp = root;
	do
	{
		while(temp != NULL)
		{
			printf(" %2c",temp->data);
			succ = pusht(&last,temp);
			if(succ == 0)
			{

			}
			else
			{
				temp = temp->lchild;
			}
		}
		if(!stackempty(last))
		{
			succ = popt(&last,&temp);
			if(succ == 0)
			{

			}
			else
			{
				temp = temp->rchild;
			}
		}
	}while(temp != NULL || stackempty(last) != 1);
}

void postorder_r(struct Tree *root)
{
	 if(root != NULL)
	 {
		postorder_r(root->lchild) ;
		postorder_r(root->rchild) ;
		printf(" %2c", root->data) ;
	 }
}

void postorder_nr(struct Tree *root)
{
	struct TreeStk *last = NULL;
	struct Tree *troot = NULL;
	struct Tree *temp = NULL;
	int succ = 0;

	troot = root;

	while(troot != NULL || !stackempty(last))
	{
		if(troot == NULL)
		{
			while(stackempty(last) != 1 && troot == (temp = getStackTop(last))->rchild)
			{
				troot = getStackTop(last);
				succ = popt(&last,&temp);
				printf(" %2c",troot->data);
			}

			troot = stackempty(last) ? NULL :(temp = getStackTop(last))->rchild;
		}

		if(troot != NULL)
		{
			pusht(&last,troot);
			troot = troot->lchild;
		}
	}
}






struct Tree* getStackTop(struct TreeStk *top)
{
	struct Tree *tnode = NULL;
	if(top == NULL)
	{
	}
	else
	{
		tnode = top->tnode;
	}
	return(tnode);
}


int intopost(char infix[50],char post[50])
{
	struct stack *top = NULL;
	char dsymbol ='\0';
	int succ = 0;
	int psucc = 0;
	int esucc = 0;
	int j = 0;
	int i = 0;
	int inop = 0;
	int stop = 0;

	while(infix[i] != '\0')
	{
		if((infix[i]>96 && infix[i]<122)
||(infix[i]>64 && infix[i]<91))
		{

			post[j] = infix[i];
			post[j+1] = '\0';
			j++;
			i++;
		}
		else
		{
			if(infix[i] != ')')
			{
				esucc = isempty(top);
				if(esucc == 1)
				{
					succ = push(&top,infix[i]);
				}
				else
				{
					do
					{
						if(infix[i] == '(')
						{
							succ = push(&top,infix[i]);
						}
						else
						{
							inop = priority(infix[i]);
							stop = priority(top->data);

							if(inop > stop)
							{
							succ = push(&top,infix[i]);
							}
							else
							{
								succ = pop(&top,&dsymbol);

								if(dsymbol != '(')
								{
									post[j] = dsymbol;
									post[j+1] = '\0';
									j++;
								}
							}
						}
					}while(inop <= stop);
				}
			}

			if(infix[i] == ')')
			{
				esucc = 0;
				do
				{
					esucc = isempty(top);
					succ = pop(&top,&dsymbol);
					if(dsymbol != '(')
					{
						post[j] = dsymbol;
						post[j+1] = '\0';
						j++;
					}

					else
					{
						esucc = 1;
					}
				}while(esucc != 1);
			}
			i++;
		}
	}

	do
	{
		esucc = isempty(top);
		psucc = pop(&top,&dsymbol);
		if(psucc == 1)
		{
			post[j] = dsymbol;
			post[j+1] = '\0';
			j++;
		}
		succ = 1;
	}while(esucc != 1);
	return(succ);
}

int priority (char x)
{
	int ret = 0;
	switch(x)
	{
		case '+':
		case '-':
					ret = 1;
					break;
		case '*':
		case '/':
		case '%':
					ret = 2;
					break;
		case '^':
					ret = 3;
					break;
	}
	return(ret);
}


int push(struct stack **top,char data)
{
	int succ = 0;
	struct stack *newnode = NULL;
	newnode = (struct stack *)calloc(1,sizeof(struct stack));
	if(newnode == NULL)
	{
		printf("\n\t Error : Memory Allocation Failed..");
		succ = 0;
	}
	else
	{
		newnode->data = data;
		newnode->next = *top;
		*top = newnode;
		succ = 1;
	}
	return(succ);
}


int pop(struct stack **top,char *data)
{
	int succ = 0;
	struct stack *dnode = NULL;

	if(*top == NULL)
	{
		succ = 0;
	}
	else
	{
		dnode = *top;
		*top = (*top)->next;
		dnode->next = NULL;
		*data = dnode->data;
		free(dnode);
		dnode = NULL;
		succ = 1;
	}
	return(succ);
}





int isempty(struct stack *top)
{
	int succ = 0;
	if(top == NULL)
	{
		succ = 1;
	}
	else
	{
		succ = 0;
	}
	return(succ);
}

int valid(char d[10])
{
	int rank = 0;
	int i = 0;
	int sum = 0;
	int rank1 = 0;
	while(d[i] != '\0')
	{
		if(d[i] == '+' || d[i] == '-' || d[i] == '*' ||
 d[i] == '/'|| d[i] == '^')
		{
			rank = -1;
		}
		else if(d[i] == '(' || d[i] == ')')
		{
			rank = 0;
		}
		else if((d[i]>96 && d[i]<122) || (d[i]>64 && d[i]<91))
		{
			rank = 1;
		}
		sum = sum + rank;
		i++;
	}
	if(sum == 0 || sum == 1)
	{
			rank1 = 1;
	}
	else
		rank1 = 0;

	return(rank1);
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
