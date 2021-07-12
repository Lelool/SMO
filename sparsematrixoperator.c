#include "basehead.h"
int main() {
    int state;
    state = getstate();
    while (state) {
        switch (state) {
        case 1:
            add();
            break;
        case 2:
            sub();
            break;
        case 3:
            mul();
            break;
        default :
            //printinfo(FUNC);
            break;
        }
        state = getstate();
    }
    return 0;
}

State getstate(void) {
    int state;
    printinfo(FUNC);
    scanf_s("%d", &state);
    return state;
}

void printinfo(int state) {
    if (state == FUNC)
        printf("运算器功能为\n0 退出\n1 加\n2 减\n3 乘\n请输入要进行的运算序号：");
    else if (state == STYLE)
        printf("矩阵的输入形式为i,j,k,按行主序输入\n");
    else;
    return;
}

void add(void){
    TSMatrix *A;
    TSMatrix *B;
    A = lalloc();
    B = lalloc();
    getinput(A, 'A');
    getinput(B, 'B');
    output(A);

}

void sub(void){
}

void mul(void){
    //getinput();
}

void getinput(TSMatrix *A, char name){
    int num;
    int i, j, k;
    int index=0;
    int preline = -1;
    //注意，此处下标是从0开始的
    printf("请输入%c矩阵的行数：",name);
    scanf_s("%d", &i);
    printf("请输入%c矩阵的列数：",name);
    scanf_s("%d", &j);
    printf("请输入%c矩阵中非零元素个数：",name);
    scanf_s("%d", &k);
    A->mu = i;
    A->nu = j;
    A->tu = k;
    printf("mu:%d nu:%d tu:%d", A->mu, A->nu, A->tu);
    printinfo(STYLE);
    for (num = 0; num < A->tu; num++) {
        scanf_s("%d,%d,%d", &i, &j, &k);
        printf("num is %d\n", num);
        A->data[num].i = i;
        A->data[num].j = j;
        A->data[num].e = k;
        //初始化rpos，每行第一个数的下标
        //若i!-preline说明换行
       //if (i > preline) {
         //   while (i > preline + 1){
           //     //空行首地址下标-1
             //   A->rpos[++preline] = -1;
            //}
            //printf("out");
            //A->rpos[++preline] = num;
        //}
    } 
}



void output(TSMatrix *A){
    int i;
    int j;
    int k;
    k = 0;
    for (i = 0; i < A->nu; i++) {
        for (j = 0; j < A->mu; j++) {
            if (A->data[k].i == i && A->data[k].j==j) {
                printf("%d ", A->data[k].e);
                k++;
            }
            else
                printf("0 ");
        }
        printf("\n");
    }
}

TSMatrix* lalloc(void){
    return (TSMatrix *)malloc(sizeof(TSMatrix));
}
