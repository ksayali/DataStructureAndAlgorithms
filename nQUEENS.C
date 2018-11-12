#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void queens(int,int, int []);
void display(int,int[]);
int place(int,int []);

int main(void)
{
	int pos[15]={0};
	int q=1,n=0;
	clrscr();
	printf("\n\n\t Enter number of queens :");
	scanf("%d",&n);
	while(n<4)
	{
		printf("\n\n\t Queens cannot be placed !!");
		printf("\n\n\t Enter number greater than equal to 4 :");
		scanf("%d",&n);
	}
	queens(n,q,pos);
	getch();
	return 0;
}

void display(int n, int pos[])
{
	int i=0,j=0,x=10,y=8;
	for(i=1;i<=n;i++)
	{
		gotoxy(x,y);
		printf("%d",i);
		x=x+4;
	}
	y=y+2;
	x=7;
	for(i=1;i<=n;i++)
	{
		gotoxy(x,y);
		printf("%d",i);
		y=y+2;
	}
	x=10;
	y=10;
	for(i=1;i<=n;i++)
	{

	    x=10;
	    for(j=1;j<pos[i];j++)
	    {
		x=x+4;

	    }
	    gotoxy(x,y);
	    printf("%c",'Q');
	    y=y+2;
	}
}


void queens(int n,int q,int pos[15])
{
	int i=0,succ=0;
	if(q<=n)
	{
		pos[q]=pos[q]+1;
		succ=place(q,pos);
		while(pos[q]<=n && succ==0)
		{
			pos[q]=pos[q]+1;
			succ=place(q,pos);
		}
		if(pos[q]<=n)
		{
			if(q==n)
			{
				printf("\n\t Solution is:");
				display(n,pos);
			}
			else
			{
				q=q+1;
				queens(n,q,pos);
			}

		}
		else
		{
			pos[q]=0;
			q=q-1;		// Backtrack
			queens(n,q,pos);

		}
	}

}


int place(int k, int pos[8])
{
	int i=0,succ=1;
	for(i=0;i<k;i++)
	{
		if((pos[i]==pos[k]) || (abs(pos[i]-pos[k])==abs(i-k)))
		{
			succ=0;
			i=k;
		}
	}
	return succ;
}