#include<stdio.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;

#define MAXSIZE 100

//--------二叉树的二叉链表存储表示-----------
typedef struct BiTNode{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//--------先序建立二叉链表-------------------
void CreateBiTree(BiTree &T)
{
	char ch;
	scanf("%c",&ch);
	if(ch == '#') T = NULL;
	else
	{
		T = new BiTNode;
		T -> data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}

//---------递归算法中序遍历二叉树--------------------
void InOrderTraverse(BiTree T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		printf("%c",T->data);
		InOrderTraverse(T->rchild);
	}
}

//---------递归算法先序遍历二叉树--------------------
void PreOrderTraverse(BiTree T)
{
	if(T)
	{
		printf("%c",T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

//---------递归算法后序遍历二叉树--------------------
void PostOrderTraverse(BiTree T)
{
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c",T->data);
	}
}

//---------------栈的相关定义----------

typedef struct{//存储char型变量的栈
    BiTNode *base;
    BiTNode *top;
    int stacksize;
}SqStack;

Status InitStack(SqStack &S)//初始化
{
    S.base = new BiTNode[MAXSIZE];
    if(!S.base) return ERROR;
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}

Status Push(SqStack &S, BiTNode e)//入栈
{
    if((S.top - S.base) == S.stacksize) return ERROR;
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S, BiTNode &e)//出栈
{
    if(S.top == S.base) return ERROR;
    e = *--S.top;
    return OK;
}

BiTNode GetTop(SqStack S)//获取栈顶值
{
    if(S.top != S.base)
    return *(S.top - 1);
}

//------------中序遍历二叉树的非递归算法---------
void InOrderTraverse_stack(BiTree T)
{
	SqStack S;
	InitStack(S);
	BiTree p = T;
	BiTree q = new BiTNode;
	while(p||S.top != S.base)
	{
		if(p)
		{
			Push(S,*p);
			p = p->lchild;
		}
		else
		{
			Pop(S,*q);
			printf("%c",q->data);
			p = q->rchild;
		}
	}
}

//------------队列的相关定义-----------

typedef struct QNode//链式存储结构
{
	BiTree data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue &Q)//构造一个空队列
{
	Q.front = Q.rear = new QNode;
	Q.front->next = NULL;
	return OK;
}

Status EnQueue(LinkQueue &Q, BiTree e)//入队
{
	QueuePtr p = new QNode;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

Status DeQueue(LinkQueue &Q, BiTree &e)
{
	if(Q.front == Q.rear) return ERROR;
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p) Q.rear = Q.front;
	delete p;
	return OK;
}

BiTree FrontQueue(LinkQueue Q)
{
    BiTree p = NULL;
	if(Q.front == Q.rear) return NULL;
	else
	{
		p = Q.front->next->data;
		return p;
	}
}
//----------层序遍历（广度优先遍历）------------
void LevelOrderTraverse(BiTree T)
{
	BiTree  c,cc,temp;
	LinkQueue q;
	InitQueue(q);//构造一个空队列
 //队列元素为BiTree类型
	if(T == NULL) return;
	c = T;
	EnQueue(q, c); //将二叉树送入队列
	while(q.front != q.rear)
    {
		c = FrontQueue(q);
		DeQueue(q, temp);
		printf("%c",c->data);
      //从队列首部取出二叉树并访问
	    cc = c->lchild;
		if(cc != NULL)
			EnQueue(q,cc);
      //将左子树送入队列
        cc = c->rchild;
		if(cc != NULL)
			EnQueue(q,cc);
     //将右子树送入队列
     }
}

//----------二叉树镜像------------
void MirrorBitree(BiTree T)
{
    if(T)
    {
        BiTNode *p = T->lchild;
        T->lchild = T->rchild;
        T->rchild = p;
    }
    else return;
    MirrorBitree(T->lchild);
    MirrorBitree(T->rchild);
    return;

}
int main()
{
	BiTree T;
	printf("Please input a binary tree pre-orderly(eg.AB#C##DE##F##):");
	CreateBiTree(T);//初始化二叉树
	printf("\nBy pre-order-traverse(recursive algorithm), the tree is:");
	PreOrderTraverse(T);//先序遍历（递归算法）二叉树
	printf("\nBy in-order-traverse(recursive algorithm), the tree is:");
	InOrderTraverse(T);//中序遍历（递归算法）二叉树
	printf("\nBy post-order-traverse(recursive algorithm), the tree is:");
	PostOrderTraverse(T);//后序遍历（递归算法）二叉树
	printf("\nBy in-order-traverse(non-recursive algorithm), the tree is:");
	InOrderTraverse_stack(T);//中序遍历（非递归算法）二叉树
	printf("\nBy lever-order-traverse, the tree is:");
	LevelOrderTraverse(T);//层序遍历二叉树
	printf("\nAfter mirroring, by pre-order-traverse(recursive algorithm), the tree is:");
	MirrorBitree(T);//镜像处理二叉树
	PreOrderTraverse(T);//先序遍历（递归算法）二叉树
	return 0;
}
