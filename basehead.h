#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 400
#define MAXRC   20

#define EXIT  0
#define ADD   1
#define SUB   2
#define MUL   3
#define ERROR 4
#define FUNC  5
#define STYLE 6
typedef int State;
typedef struct{
    int i; //行
    int j; //列
    int e; //数据
}Triple;

typedef struct{
    Triple data[MAXSIZE+1];
    int rpos; //各行第一个非零元的位置
    int mu;   //行数
    int nu;   //列数
    int tu;   //非零元个数
}TSMatrix;
//用于获取用户输入的状态
State getstate(void);
//用于打印输入信息，格式
void printinfo(int state);
