//Kruskal's Algorithm

#include<stdio.h>
#include<conio.h>

#define MAX 999

struct graph
{
	int v1,v2,cost;
};

void create(int,int, struct graph[]);
void spanningtree(int,int, struct graph[]);
int minimum(int, struct graph[]);
int find(int,int[]);
void union1(int,int,int[]);

int main(void)
{
	int tn=0,te=0;
    struct graph g[20];

	clrscr();

	create(tn,te,g);

	getch();
	return 0;
}


void create(int tn,int te, struct graph g[20])
{
	int k;

	printf("\n\nEnter total number of node :");
	scanf("%d",&tn);

	printf("\n\nEnter total number of edges :");
	scanf("%d",&te);

	for(k=0;k<te;k++)
	{
		printf("\n Enter edge in (v1 v2)form :");
		scanf("%d%d",&g[k].v1,&g[k].v2);
		printf("\n Enter correspounding cost :");
		scanf("%d",&g[k].cost);
	}

	spanningtree(tn,te,g);
}


void spanningtree(int tn,int te, struct graph g[20])
{
	int count=0,k=0,v1=0,v2=0,i=0,j=0;
    int tree[10][10]={(0,0)}, parent[10]={0};
    int pos=0,sum=0;

	for(i=0;i<tn;i++)
	{
		parent[i]=i;
	}

	while(count!=tn-1)
	{
		pos=minimum(te,g);

		if(pos==-1)
		{
			break;
		}

		v1=g[pos].v1;
		v2=g[pos].v2;

		i=find(v1,parent);
		j=find(v2,parent);

		if(i != j)
		{
			tree[k][0]=v1;
			tree[k][1]=v2;
			k++;
			count++;
			sum += g[pos].cost;
			union1(i,j,parent);
		}
		g[pos].cost=MAX;
	}

	if(count == tn-1)
	{
		printf("\nSpanning Tree is...");
		printf("\n--------------------\n");

		for(i=0;i<tn-1;i++)
		{
			printf("[%d",tree[i][0]);
			printf("-");
			printf("%d]",tree[i][1]);
		}

		printf("\nCost of spanning tree = %d",sum);
	}
	else
	{
		printf("\nThere is no Spanning Tree");
	}
}


int minimum(int n, struct graph g[20])
{
	int i,small,pos;

	small=MAX;
	pos=-1;

	for(i=0;i<n;i++)
	{
		if(g[i].cost<small)
		{
			small=g[i].cost;
			pos=i;
		}
	}
	return pos;
}


int find(int v2,int parent[])
{
	while(parent[v2]!=v2)
	{
		v2=parent[v2];
	}
	return v2;
}


void union1(int i,int j,int parent[])
{
	if(i<j)
	{
		parent[j]=i;
	}
	else
	{
		parent[i]=j;
	}
}