#include "basehead.h"
void check(void){
    printf("check");
}
int main(){
    int state;
    printinfo(FUNC);
    state=getstate();
    while(state){
        switch(state){
            case 1:
                check();
                break;
            case 2:
                check();
                break;
            case 3:
                check();
                break;
            case 4:
                check();
                break;
        }
        state=getstate();
    }
    return 0;
}

State getstate(void){
    int state;
    printinfo(FUNC);
    scanf("%d",&state);
    return state;
}

void printinfo(int state){
    if(state==FUNC)
        printf("运算器功能为\n0 退出\n1 加\n2 减\n3 乘\n请输入要进行的运算序号：");
    else if(state==STYLE)
        printf("矩阵的输入形式为i j k,按行主序输入\n");
    else ;
    return ;
}