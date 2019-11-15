#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define RED 1
#define BLACK 2


typedef struct RBT{
	int color;
	int size;
	struct RBT * p ,*left, *right;
	int key;
}RBTree;


typedef struct{
	RBTree *root,*nil;
}RBT;




/**************************************/
void InOrder(RBTree *T)
{
    if (T->size){
        InOrder(T->left);
        printf("%d %d   %d\n",T->key,T->color,T->size);
        InOrder(T->right);
    }
}


/********************左旋*****************/
void LeftRotate(RBT *T,RBTree *x)
{
	RBTree *y = x->right;

	x->right = y->left;
	if (y->left != T->nil)
		y->left->p = x;

	y->p = x->p;
	if (x->p == T->nil)
		T->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;

	y->left = x;
	x->p = y;
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}



/********************右旋*****************/
void RightRotate(RBT *T,RBTree *y)
{
	RBTree *x = y->left;

	y->left = x->right;
	if (x->right != T->nil)
		x->right->p = y;

	x->p = y->p;
	if (y->p == T->nil)
		T->root = x;
	else if (y == y->p->left)
		y->p->left = x;
	else
		y->p->right = x;

	x->right = y;
	y->p = x;
	x->size = y->size;
	y->size = y->left->size + y->right->size + 1;
}
//


/*******************插入************************/
void RBInsertFixup(RBT *T,RBTree *m)
{
	RBTree *y,*z=m;
	while (z->p->color == RED){
		if (z->p == z->p->p->left){
			y = z->p->p->right;
			if (y->color == RED){		//case1
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else if (z == z->p->right){	//case 2
				z = z->p;
				LeftRotate(T,z);
			}
			else {					//case 3
                z->p->color = BLACK;
                z->p->p->color = RED;
                RightRotate(T,z->p->p);
			}
		}
		else{
			y = z->p->p->left;
			if (y->color == RED){		//case1
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else if (z == z->p->left){	//case 2
				z = z->p;
				RightRotate(T,z);
			}
			else {					//case 3
                z->p->color = BLACK;
                z->p->p->color = RED;
                LeftRotate(T,z->p->p);
			}
		}
	}
	T->root->color = BLACK;
}

void UPSize(RBT *T,RBTree *z)
{
	RBTree *y = z->p;
	if (z == T->root)
		return ;

	while (y!=T->nil )
	{
		y->size ++;
		y = y->p;
	}
}

void RBInsert(RBT *T,RBTree *z)
{
	RBTree *y=T->nil;
	RBTree *x=T->root;

	while (x != T->nil ){
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == T->nil)
		T->root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->left = T->nil;
	z->right = T->nil;
	z->color = RED;
	UPSize(T,z);
	RBInsertFixup(T,z);

}

/********************Search****************************/

int RBTSearch(RBT *T,int Size)
{
	int size = Size;
	RBTree *root = T->root;
	RBTree *nil = T->nil;

	while (root != nil){
		if (size < root->left->size + 1){
			root = root->left;
		}
		else if (size == root->left->size +1){
			return root->key;
		}
		else {
			size -= root->left->size + 1;
			root = root->right;
		}
	}

}

RBTree * NodeSearch(RBTree *T,int key)
{
    RBTree *y = T;

    while (y->size){
        if (y->key == key)
            return y;
        else if (y->key > key)
            return NodeSearch(T->left,key);
        return NodeSearch(T->right,key);
    }

}




/*******************删除*******************************/

void RBTransplant(RBT *T,RBTree *u,RBTree *v)
{
	if (u->p == T->nil)
        T->root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;

    v->p = u->p;
}

RBTree* TreeMinimum(RBTree *z)
{
    RBTree *y=z;
    while(y->left->size != 0){
        y = y->left;
    }

    return y;
}

void RBDeleteFixup(RBT *T,RBTree *x)
{
    RBTree *w;

   // printf("-100\n");
    while (x != T->root && x->color == BLACK){
       //printf("-200\n");
        if (x == x->p->left){
            w = x->p->right;
            //printf("-300\n");
            if (w->color == RED){               //case 1
                w->color = BLACK;
                x->p->color = RED;
                LeftRotate(T,x->p);
                w = x->p->right;
            }
            else {
                if (w->left->color == BLACK && w->right->color == BLACK){           //case 2
                    w->color = RED;
                    x = x->p;
                }
                else if (w->right->color == BLACK){                     //case 3
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(T,w);
                    w = x->p->right;
                }
                else {              //case 4
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->right->color = BLACK;
                    LeftRotate(T,x->p);
                    x = T->root;
                }
            } //else
        }//if

        else {
            w = x->p->left;
            //printf("-400\n");
            if (w->color == RED){               //case 1
                w->color = BLACK;
                x->p->color = RED;
                RightRotate(T,x->p);
                w = x->p->left;
            }
            else {
                if (w->left->color == BLACK && w->right->color == BLACK){           //case 2
                    w->color = RED;
                    x = x->p;
                }
                else if (w->left->color == BLACK){                     //case 3
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(T,w);
                    w = x->p->left;
                }
                else {              //case 4
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->left->color = BLACK;
                    RightRotate(T,x->p);
                    x = T->root;
                }
            } //else

        }

    }//while
    //printf("-500\n");
    x->color = BLACK;
}

void SUBSize(RBT *T,RBTree *z)
{
    RBTree *y = z->p;

    while (y != T->nil){
        y->size --;
        y = y->p;
    }
}


void RBDelete(RBT *T,RBTree *z)
{
    RBTree *y = z,*x;
    int y_original_color = y->color;

    if (z->left == T->nil){
        SUBSize(T,z);
        x = z->right;
        RBTransplant(T,z,z->right);
    }
    else if (z->right == T->nil){
        SUBSize(T,z);
        x = z->left;
        RBTransplant(T,z,z->left);
    }
    else {
        y = TreeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        SUBSize(T,y);
        if (y->p == z)
            x->p = y;
        else{
            RBTransplant(T,y,y->right);
            y->right = z->right;
            y->right->p = y;
        }

        RBTransplant(T,z,y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
        y->size = z->size;
    }

    if (y_original_color == BLACK)
        RBDeleteFixup(T,x);
    free(z);

}



int AtoI(char s[])
{
    int key = 0;
    int i;

    for (i=2;i<strlen(s);i++)
        key = key * 10 + (s[i] - '0');

    return key;
}



int main()
{
	int n;
	int i;
	char c;
	char s[20];
	int key;
	RBT *T;
	RBTree *Node,*y;


	T = (RBT *)malloc(sizeof(RBT));
	if (!T)
		exit(0);
	RBTree *NIL = (RBTree *)malloc(sizeof(RBTree));	//哨兵
	if (!NIL)
		exit(0);
	NIL->color = BLACK;
	NIL->size = 0;
	T->root = NIL;
	T->nil = NIL;


    gets(s);
    n=atoi(s);
	for (i=1;i<=n;i++){
		gets(s);
		c = s[0];
		key = AtoI(s);
		if (c == 'I'){
			Node = (RBTree *)malloc(sizeof(RBTree));
            if (!Node)	exit(0);
            Node->key = key;
            Node->size = 1;

			RBInsert(T,Node);
			//printf("%d",T->root->key);
			//InOrder(T->root);
		}
		else if (c == 'K') {
			printf("%d\n",RBTSearch(T,key));
		}
		else {
            y = NodeSearch(T->root,key);
            RBDelete(T,y);
           // InOrder(T->root);
		}
	}



	return 0;
}
