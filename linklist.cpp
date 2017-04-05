#include<stdio.h>
#include<iostream>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

using namespace std;

typedef struct LNode//定义单链表的结点
{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

Status InitList(LinkList &L)//单链表的初始化
{
    L = new LNode;
    L->next = NULL;
    return OK;
    }

Status GetElem(LinkList L, int i, ElemType &e)//取值子函数
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

LNode *LocateElem(LinkList L, ElemType e)//按值查找，返回指针子函数
{
    LNode *p = L-> next;
    while(p && p->data != e)
    p = p->next;
    return p;
    }

Status ListInsert(LinkList L, int i, ElemType e)//插入子函数
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

Status ListDelete(LinkList &L, int i)//删除子函数
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

void CreateList_R(LinkList &L, int n)//后插法创建单链表
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

void Output(LinkList L,int n) //输出单链表
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
    cout << "Please input 5 numbers(eg.5 4 3 5 2): ";//创建单链表
    CreateList_R(L, 5);
    cout << "Now the list is:\n";//输出此时的单链表
    Output(L, 5);
    cout << "\nInsert the number e in the nth place, input n(n >= 1) and e(eg. 3 5): ";
    ElemType e;int i;
    scanf("%d %d", &i,&e);
    ListInsert(L, i, e);//在第i位插入数据e
    cout << "Now the list is:\n";//输出此时的单链表
    Output(L, 6);
    cout << "\nDelete the nth number, please input n(n >= 1): ";
    cin >> i;
    ListDelete(L, i);//删除第i位的数据
    cout << "Now the list is:\n";
    Output(L, 5);//输出此时的单链表
    cout << "\n";
    return 0;
    }
