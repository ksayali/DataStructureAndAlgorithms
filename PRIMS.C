//Prim's Algorithm

#include<stdio.h>
#include<conio.h>

void prims(int vertices, int wt[10][10], int markv[10],int l[10],int m[10])
{
	int recent=1;
	int act_vis=1;
	int min=0;
	int u=0;

	l[recent]=0;
	markv[recent]=1;

	while(act_vis!=vertices)
	{
		for(u=1;u<=vertices;u++)
		{
			if(wt[recent][u]!=0)
			{
				if(markv[u]==0)
				{
					if(l[u]>wt[recent][u])
					{
						l[u]=wt[recent][u];
						m[u]=recent;
					}
				}
			}
		}

		min=32767;
		for(u=1;u<=vertices;u++)
		{
			if(markv[u]==0)
			{
				if(l[u]<min)
				{
					min=l[u];
					recent=u;
				}
			}
		}
		markv[recent]=1;
		act_vis++;
	}

	min=0;
	for(u=1;u<=vertices;u++)
	{
		min+=l[u];
	}
	printf("\n Minimum cost of the spanning tree is=%d",min);
	printf("\n\n Minimum cost spanning tree consists of following sets of vertices &edges :");

	for(u=2;u<=vertices;u++)
	{
		printf("\nVertex %d is connected to Vertex %d",u,m[u]);
	}
}

int main()
{
	int vertices=0;
	int u=0;
	int v=0;
	int z=0;
    int wt[10][10] = {(-1,-1)};
    int markv[10] = {0};
    int l[10] = {0};
    int m[10]={0};

    clrscr();

	//accepting values
	do
	{
		printf("\n\nEnter no of vertices in given graph : ") ;
		scanf("%d",&vertices);
	}while(vertices<1 || vertices>=10);

	//initialising weights to -1
	for(u=1;u<=vertices;u++)
	{
		for(v=1;v<=vertices;v++)
		{
			wt[u][v]=-1;
		}
	}

	//initialize vertex travesered or not to 0
	for(u=1;u<=vertices;u++)
	{
		m[u]=markv[u]=0;
		l[u]=32767;     //wt
	}

	for(u=1;u<=vertices;u++)
	{
		for(v=1;v<=vertices;v++)
		{
			if(u==v)
			{
				wt[u][v]=z=0;
			}
			else
			{
				if(wt[u][v]==-1)
				{
					do
					{
						printf("\n\nEnter weight of edge from %d to %d node :",u,v);
						scanf("%d",&z);
					}while(z<0);

					wt[u][v]=z;
					wt[v][u]=z;
				}
			}
		}
	}

	printf("\n\n Weigth of the edges are : \n");

	for(u=1;u<=vertices;u++)
  	{
  		printf("\t%d",u);
	}
  	printf("\n---------------------------------") ;

	for(u=1;u<=vertices;u++)
	{
		printf("\n%d |",u);
		for(v=1;v<=vertices;v++)
		{
			printf("\t%d",wt[u][v]);
		}
	}

	prims(vertices,wt,markv,l,m);
	getch();
	clrscr();
	return 0;
}