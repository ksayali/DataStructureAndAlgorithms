#include<stdio.h>
#include<conio.h>

int prime(int n);
int gcd(int a, int b);
int exteuc(int n, int r2);
int sqnmul(int a, int x, int n);
void encrypt(int n, int e);
void decrypt(int d, int n);

int main(void)
{
	int p=0;
	int q=0;
	int e=0;
	int n=0;
	int d=0; 			// private key
	int et=0;			// eulers totient
	int ch=0;
	int ch1=0;
	int check=0;
	clrscr();
	do
	{
		printf("\n\n\t RSA ALGORITHM \n\
			\n\t MENU \
			\n 1. RSA \
			\n\n 2. EXIT \
			\n\n ENTER CHOICE  :  ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1 : printf("\n ENTER VALUES  :  \n");
				 do
				 {
					printf("\n p  :  ");
					scanf("%d",&p);
					check=prime(p);
					if(check==1)
					{
						printf("\n NOT A PRIME NUMBER!! \n");
					}
				 }while(check==1);
				 do
				 {
					printf("\n q  :  ");
					scanf("%d",&q);
					check=prime(q);
					if(check==1)
					{
						printf("\n NOT A PRIME NUMBER!! \n");
					}
				 }while(check==1);
				 n=p*q;
				 et=(p-1)*(q-1);
				 do
				 {
					printf("\n e  :  ");
					scanf("%d",&e);
					if(e>1&&e<et)
					{
						check=gcd(e,et);
						if(check==1)
						{
							printf("\n INVALID NUMBER!! \n");
						}
					}
					else
					{
						check=1;
						printf("\n INVALID RANGE!! \n");
					}
				 }while(check==1);
				 d=exteuc(et,e);
				 printf("\n PUBLIC KEY  :  ( %d, %d ) ",n,e);
				 printf("\n\n PRIVATE KEY  :  ( %d, %d ) \n",n,d);
				 do
				 {
					printf("\n\n\n\t SUBMENU \n\
						\n 1. ENCRYPT \
						\n\n 2. DECRYPT \
						\n\n 3. BACK TO MAIN MENU \
						\n\n ENTER CHOICE  :  ");
					scanf("%d",&ch1);
					switch(ch1)
					{
						case 1 :  encrypt(n,e);
							  break;
						case 2 :  decrypt(d,n);
							  break;
						case 3 : break;
						default : printf("\n INVALID CHOICE!! \n");
					}
				 }while(ch1!=3);
				 break;

			case 2 : break;

			default : printf("\n INVALID CHOICE!! \n");
		}
		printf("\n\n PRESS ANY KEY TO CONTINUE.... ");
		getch();
		clrscr();
	}while(ch!=2);
	return(0);
}

int prime(int n)
{
	int i=0;
	int nh=0;
	int succ=0;
	if(n%2==0)
	{
		succ=1;
	}
	else
	{
		i=3;
		nh=n/2;
		while(i<nh)
		{
			if(n%i==0)
			{
				succ=1;
				i=nh;
			}
			i+=2;
		}
	}
	return(succ);
}

int gcd(int a, int b)
{
	int rem=0;
	int succ=1;
	do
	{
		rem=a%b;
		a=b;
		b=rem;
	}
	while(rem>0);
	if(a==1)
	{
		succ=0;
	}
	return(succ);
}

int exteuc(int n, int r2)
{
	int q=0;
	int r=0;
	int t=0;
	int t1=0;
	int t2=1;
	int r1=0;
	int binverse=-1;
	r1=n;
	while(r2>0)
	{
		q=r1/r2;
		r=r1-(q*r2);
		r1=r2;
		r2=r;
		t=t1-q*t2;
		t1=t2;
		t2=t;
	}
	if(r1==1)
	{
		binverse=t1;
		if(binverse<0)
		{
			binverse+=n;
		}
	}
	return binverse;
}

int sqnmul(int a, int x, int n)
{
	int y=0;
	int i=0;
	int nxb=0;			// no: of bits in x
	int xb[10]={0};

	// convert x to binary
	while(x>0)
	{
		xb[i]=x%2;
		x=x/2;
		i++;
	}
	nxb=i;
	y=1;
	for(i=0;i<=nxb-1;++i)
	{
		if(xb[i]==1)
		{
			y=(a*y)%n;
		}
		a=(a*a)%n;
	}
	return(y);
}

void encrypt(int n, int e)
{
	int p=0;
	int c=0;
	do
	{
		printf("\n ENTER PLAINTEXT  :  ");
		scanf("%d",&p);
		if(p>n)
		{
			printf("\n INVALID!! \n");
		}
	}while(p>n);
	c=sqnmul(p,e,n);
	printf("\n CIPHERTEXT IS  :  %d",c);
}

void decrypt(int d, int n)
{
	int p=0;
	int c=0;
	printf("\n ENTER CIPHERTEXT  :  ");
	scanf("%d",&c);
	p=sqnmul(c,d,n);
	printf("\n PLAINTEXT IS  :  %d",p);
}




