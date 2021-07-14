#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXSIZE 400
#define MAXRC   20

#define EXIT  0
#define ADD   1
#define SUB   2
#define MUL   3
#define INV   4
#define ERROR 5
#define FUNC  6
#define STYLE 7
#define CHECK 8
typedef int State;
 
//十字链表的结点
typedef struct olnode{
    //line
    int i;
    //row
    int j;
    //elemtype
    int e;
    //right
    struct olnode *right;
    //down
    struct olnode *down;
}OLNode;

//存储行和列的头
typedef struct { 
    OLNode *rhead[MAXRC];//行
    OLNode *chead[MAXRC];//列
    //line
    int mu;
    //row
    int nu;
    //element
    int tu;
}CrossList;

//用于获取用户输入的状态
State getstate(void);
//用于打印输入信息，格式
void printinfo(int state);
void add(void);
void sub(void);
void mul(void);
void inv(void);
//获取输入并存入十字链表
void getinv(CrossList *A, char name);
//申请十字链表中的结点的存储空间
OLNode *oalloc(void);
//初始化结点
void initialhead(CrossList *p);
//初始化数组
void initialarray(int a[][MAXRC], int m, int n);
//打印二维数组
void outputarray(int a[][MAXRC], int m, int n);
//打印十字链表
void outputlist(CrossList A);
//求矩阵行列式,递归
int determinant(CrossList a, int n);
//求余子式，并存入数组
void minor(CrossList a, int b[][MAXRC]);
//将i,j,k结点插入链表中
void insertnode(CrossList *a, int i, int j, int k);
//打印输出提示
void outputhint(CrossList *a, CrossList *b, char op);
//打印输入提示
int inputhint(CrossList *a, CrossList *b, CrossList *q);
