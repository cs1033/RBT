#include <stdio.h>



typedef struct Node{
	int key;
	int rank;
	struct Node *parent;
}TNode;

TNode T[5000000+10];
int result[5000000+10]; 

void Make_Set(TNode *T)
{
	T->parent = T;
	T->rank = 0;
}

void Link(TNode *x,TNode *y)
{
	if (x==y)
		return ;
	
	if (x->rank > y->rank)
		y->parent = x;
	else{
		x->parent = y;
		if (x->rank == y->rank)
			y->rank += 1; 
	}
}

TNode* Find_Set(TNode* x)
{
	if (x->parent != x)
		x->parent = Find_Set(x->parent);
	return x->parent;
}

void Union(TNode *x,TNode *y)
{
	Link(Find_Set(x),Find_Set(y));
}

int main ()
{
	int n,k,m;
	int x,y;
	int i;
	
	scanf("%d %d %d",&n,&k,&m);
	
	for (i=0;i<n;i++){
		T[i].key = i;
		Make_Set(&T[i]);
	}
	
	for (i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		Union(&T[x],&T[y]);
	}
	
	for (i=0;i<k;i++){
		scanf("%d %d",&x,&y);
		if (Find_Set(&T[x]) == Find_Set(&T[y]))
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
