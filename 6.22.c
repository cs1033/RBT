#include <stdio.h>



typedef struct Node{
	int p;
	int rank;
}TNode;

TNode T[5000000+10];
int result[5000000+10]; 

void Make_Set(int x)
{
	T[x].p = x;
	T[x].rank = 0;
}

void Link(int x,int y)
{
	if (x==y)
		return ;
	
	if (T[x].rank > T[y].rank)
		T[y].p = x;
	else{
		T[x].p = y;
		if (T[x].rank == T[y].rank)
			T[y].rank += 1;
	}
}

int Find_Set(int x)
{
	if (T[x].p != x)
		T[x].p = Find_Set(T[x].p);
	return T[x].p;
}

void Union(int x,int y)
{
	Link(Find_Set(x),Find_Set(y));
}

int main ()
{
	int n,k,m;
	int x,y;
	int i;
	
	scanf("%d%d%d",&n,&k,&m);
	
	for (i=0;i<=n;i++){
		Make_Set(i);
	}
	
	for (i=0;i<m;i++){
		scanf("%d%d",&x,&y);
		Union(x,y);
		//Union(&T[x],&T[y]);
	}
	for (i=0;i<k;i++){
		scanf("%d%d",&x,&y);
		if (Find_Set(x) == Find_Set(y))
			result[i]=1;	
		else
			result[i]=0;	
	}
	
	for(i=0;i<k;i++)
	{
		printf("%d ",result[i]);
	}
	
	
	return 0;
}

