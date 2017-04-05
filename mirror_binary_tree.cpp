#include<stdio.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;

#define MAXSIZE 100

//--------�������Ķ�������洢��ʾ-----------
typedef struct BiTNode{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//--------��������������-------------------
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

//---------�ݹ��㷨�������������--------------------
void InOrderTraverse(BiTree T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		printf("%c",T->data);
		InOrderTraverse(T->rchild);
	}
}

//---------�ݹ��㷨�������������--------------------
void PreOrderTraverse(BiTree T)
{
	if(T)
	{
		printf("%c",T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

//---------�ݹ��㷨�������������--------------------
void PostOrderTraverse(BiTree T)
{
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c",T->data);
	}
}

//---------------ջ����ض���----------

typedef struct{//�洢char�ͱ�����ջ
    BiTNode *base;
    BiTNode *top;
    int stacksize;
}SqStack;

Status InitStack(SqStack &S)//��ʼ��
{
    S.base = new BiTNode[MAXSIZE];
    if(!S.base) return ERROR;
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}

Status Push(SqStack &S, BiTNode e)//��ջ
{
    if((S.top - S.base) == S.stacksize) return ERROR;
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S, BiTNode &e)//��ջ
{
    if(S.top == S.base) return ERROR;
    e = *--S.top;
    return OK;
}

BiTNode GetTop(SqStack S)//��ȡջ��ֵ
{
    if(S.top != S.base)
    return *(S.top - 1);
}

//------------��������������ķǵݹ��㷨---------
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

//------------���е���ض���-----------

typedef struct QNode//��ʽ�洢�ṹ
{
	BiTree data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue &Q)//����һ���ն���
{
	Q.front = Q.rear = new QNode;
	Q.front->next = NULL;
	return OK;
}

Status EnQueue(LinkQueue &Q, BiTree e)//���
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
//----------���������������ȱ�����------------
void LevelOrderTraverse(BiTree T)
{
	BiTree  c,cc,temp;
	LinkQueue q;
	InitQueue(q);//����һ���ն���
 //����Ԫ��ΪBiTree����
	if(T == NULL) return;
	c = T;
	EnQueue(q, c); //���������������
	while(q.front != q.rear)
    {
		c = FrontQueue(q);
		DeQueue(q, temp);
		printf("%c",c->data);
      //�Ӷ����ײ�ȡ��������������
	    cc = c->lchild;
		if(cc != NULL)
			EnQueue(q,cc);
      //���������������
        cc = c->rchild;
		if(cc != NULL)
			EnQueue(q,cc);
     //���������������
     }
}

//----------����������------------
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
	CreateBiTree(T);//��ʼ��������
	printf("\nBy pre-order-traverse(recursive algorithm), the tree is:");
	PreOrderTraverse(T);//����������ݹ��㷨��������
	printf("\nBy in-order-traverse(recursive algorithm), the tree is:");
	InOrderTraverse(T);//����������ݹ��㷨��������
	printf("\nBy post-order-traverse(recursive algorithm), the tree is:");
	PostOrderTraverse(T);//����������ݹ��㷨��������
	printf("\nBy in-order-traverse(non-recursive algorithm), the tree is:");
	InOrderTraverse_stack(T);//����������ǵݹ��㷨��������
	printf("\nBy lever-order-traverse, the tree is:");
	LevelOrderTraverse(T);//�������������
	printf("\nAfter mirroring, by pre-order-traverse(recursive algorithm), the tree is:");
	MirrorBitree(T);//�����������
	PreOrderTraverse(T);//����������ݹ��㷨��������
	return 0;
}
