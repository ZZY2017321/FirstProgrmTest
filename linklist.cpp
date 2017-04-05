#include<stdio.h>
#include<iostream>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

using namespace std;

typedef struct LNode//���嵥����Ľ��
{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

Status InitList(LinkList &L)//������ĳ�ʼ��
{
    L = new LNode;
    L->next = NULL;
    return OK;
    }

Status GetElem(LinkList L, int i, ElemType &e)//ȡֵ�Ӻ���
{
    LNode *p = L->next;
    int j = 1;
    while(p && j < i)
    {
        p = p->next;
        ++j;
        }
    if(!p||j > i) return ERROR;
    e = p->data;
    return OK;
    }

LNode *LocateElem(LinkList L, ElemType e)//��ֵ���ң�����ָ���Ӻ���
{
    LNode *p = L-> next;
    while(p && p->data != e)
    p = p->next;
    return p;
    }

Status ListInsert(LinkList L, int i, ElemType e)//�����Ӻ���
{
    LNode *p = L;
    int j = 0;
    while(p && (j < i - 1))
    {
        p = p->next;
        ++j;
        }
    if(!p||j > i -1) return ERROR;
    LNode *s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
    }

Status ListDelete(LinkList &L, int i)//ɾ���Ӻ���
{
    LNode *p = L;
    int j = 0;
    while((p ->next) && (j < i - 1))
    {
        p = p->next;
        ++j;
        }
    if(!(p->next)||(j > i - 1)) return ERROR;
    LNode *q = p->next;
    p->next = q->next;
    delete q;
    return OK;
    }

void CreateList_R(LinkList &L, int n)//��巨����������
{
    L = new LNode;
    L->next = NULL;
    LNode *r = L;
    for(int i = 0; i < n; ++i)
    {
        LNode *p = new LNode;
        cin >> p->data;
        p->next = NULL;
        r->next = p;
        r = p;
        }
    }

void Output(LinkList L,int n) //���������
{
    LNode *p = L->next;
    int i = 0;
    for(;p && (i < n);p = p->next,i++)
    {
        cout << p->data << " ";
        }
    }


int main()
{
    LinkList L;
    cout << "Please input 5 numbers(eg.5 4 3 5 2): ";//����������
    CreateList_R(L, 5);
    cout << "Now the list is:\n";//�����ʱ�ĵ�����
    Output(L, 5);
    cout << "\nInsert the number e in the nth place, input n(n >= 1) and e(eg. 3 5): ";
    ElemType e;int i;
    scanf("%d %d", &i,&e);
    ListInsert(L, i, e);//�ڵ�iλ��������e
    cout << "Now the list is:\n";//�����ʱ�ĵ�����
    Output(L, 6);
    cout << "\nDelete the nth number, please input n(n >= 1): ";
    cin >> i;
    ListDelete(L, i);//ɾ����iλ������
    cout << "Now the list is:\n";
    Output(L, 5);//�����ʱ�ĵ�����
    cout << "\n";
    return 0;
    }
