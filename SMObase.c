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
        printf("\n\n");
        state = getstate();
    }
    return 0;
}

State getstate(void) {
    int state;
    printinfo(FUNC);
    scanf("%d", &state);
    return state;
}

void printinfo(int state) {
    if (state == FUNC)
        printf("  MENU:\n0 EXIT\n1 ADD\n2 SUB\n3 MUL\nPlease enter the sequence number:");
    else if (state == STYLE)
        printf("\nEnter matrix in line main order\nInput stype: i j k\n");
    else;
    return;
}

void add(void){
    TSMatrix *A;
    TSMatrix *B;
    TSMatrix *Q;
    A = lalloc();
    B = lalloc();
    Q = lalloc();
    int na,nb,nq,e;
    na = 0;
    nb = 0;
    nq = 0;
    getinput(A, 'A');
    getinput(B, 'B');
    if(A->mu!=B->mu || A->nu!=B->nu){
        printf("\nERROR: wrong input data\n");
        printf("Hint: matrices should have the same size\n");
        return ;
    }
    Q->mu = A->mu;
    Q->nu = A->nu;
    while(na < A->tu && nb < B->tu){
        e = A->data[na].e + B->data[nb].e;
        //当位置(i,j)对应的a,b同时有数时
        if(A->data[na].i == B->data[nb].i && A->data[na].j == B->data[nb].j){
            if(e != 0){
                Q->data[nq].e = e;
                Q->data[nq].i = A->data[na].i;
                Q->data[nq].j = A->data[na].j;
                nq++;
            }
            na++;
            nb++;
        }
        //判断A,B谁的位置更靠前，可以提出来作为一个函数
        //如果在同一行
        else if(A->data[na].i == B->data[nb].i && A->data[na].j != B->data[nb].j){
            if(A->data[na].j > B->data[nb].j){
                //A比B靠后，先处理B
                Q->data[nq].e = B->data[nb].e;
                Q->data[nq].i = B->data[nb].i;
                Q->data[nq].j = B->data[nb].j;
                nq++;
                nb++;
            }else{
                Q->data[nq].e = A->data[na].e;
                Q->data[nq].i = A->data[na].i;
                Q->data[nq].j = A->data[na].j;
                nq++;
                na++;
            }
        }
        //如果不在同一行
        else if(A->data[na].i != B->data[nb].i){
            if(A->data[na].i > B->data[nb].i){
                //A比B靠后，先处理B
                Q->data[nq].e = B->data[nb].e;
                Q->data[nq].i = B->data[nb].i;
                Q->data[nq].j = B->data[nb].j;
                nq++;
                nb++;
            }else{
                Q->data[nq].e = A->data[na].e;
                Q->data[nq].i = A->data[na].i;
                Q->data[nq].j = A->data[na].j;
                nq++;
                na++;
            }
        }

    }
    while(na < A->tu){
        Q->data[nq].e = A->data[na].e;
        Q->data[nq].i = A->data[na].i;
        Q->data[nq].j = A->data[na].j;
        nq++;
        na++;
    }
    while(nb < B->tu){
        Q->data[nq].e = B->data[nb].e;
        Q->data[nq].i = B->data[nb].i;
        Q->data[nq].j = B->data[nb].j;
        nq++;
        nb++;        
    }
    printf("A is \n");
    output(A);
    printf("B is \n");
    output(B);
    printf("The result of A + B:\n");
    output(Q);
    //printrpos(A);

}

void sub(void){
    TSMatrix *A;
    TSMatrix *B;
    TSMatrix *Q;
    A = lalloc();
    B = lalloc();
    Q = lalloc();
    int na,nb,nq,e;
    na = 0;
    nb = 0;
    nq = 0;
    getinput(A, 'A');
    getinput(B, 'B');
    if(A->mu!=B->mu || A->nu!=B->nu){
        printf("\nERROR: wrong input data\n");
        printf("Hint: matrices should have the same size\n");
        return ;
    }
    Q->mu = A->mu;
    Q->nu = A->nu;
    while(na < A->tu && nb < B->tu){
        e = A->data[na].e - B->data[nb].e;
        //当位置(i,j)对应的a,b同时有数时
        if(A->data[na].i == B->data[nb].i && A->data[na].j == B->data[nb].j){
            if(e != 0){
                Q->data[nq].e = e;
                Q->data[nq].i = A->data[na].i;
                Q->data[nq].j = A->data[na].j;
                nq++;
            }
            na++;
            nb++;
        }
        //判断A,B谁的位置更靠前，可以提出来作为一个函数
        //如果在同一行
        else if(A->data[na].i == B->data[nb].i && A->data[na].j != B->data[nb].j){
            if(A->data[na].j > B->data[nb].j){
                //A比B靠后，先处理B
                Q->data[nq].e = - B->data[nb].e;
                Q->data[nq].i = B->data[nb].i;
                Q->data[nq].j = B->data[nb].j;
                nq++;
                nb++;
            }else{
                Q->data[nq].e = A->data[na].e;
                Q->data[nq].i = A->data[na].i;
                Q->data[nq].j = A->data[na].j;
                nq++;
                na++;
            }
        }
        //如果不在同一行
        else if(A->data[na].i != B->data[nb].i){
            if(A->data[na].i > B->data[nb].i){
                //A比B靠后，先处理B
                Q->data[nq].e = - B->data[nb].e;
                Q->data[nq].i = B->data[nb].i;
                Q->data[nq].j = B->data[nb].j;
                nq++;
                nb++;
            }else{
                Q->data[nq].e = A->data[na].e;
                Q->data[nq].i = A->data[na].i;
                Q->data[nq].j = A->data[na].j;
                nq++;
                na++;
            }
        }

    }
    while(na < A->tu){
        Q->data[nq].e = A->data[na].e;
        Q->data[nq].i = A->data[na].i;
        Q->data[nq].j = A->data[na].j;
        nq++;
        na++;
    }
    while(nb < B->tu){
        Q->data[nq].e = B->data[nb].e;
        Q->data[nq].i = B->data[nb].i;
        Q->data[nq].j = B->data[nb].j;
        nq++;
        nb++;        
    }
    printf("A is \n");
    output(A);
    printf("B is \n");
    output(B);
    printf("The result of A - B:\n");
    output(Q);
    //printrpos(A);

}

void mul(void){
    TSMatrix *A;
    TSMatrix *B;
    int i,j;
    int ja;
    int ib;
    int nb;
    int na;
    int Q[MAXRC][MAXRC];
    A = lalloc();
    B = lalloc();
    getinput(A, 'A');
    getinput(B, 'B');
    if(A->nu != B->mu){
        printf("ERROR: wrong input data\n");
        printf("Hint: The number of columns in A should be equal to the number of rows in B\n");
        return ;
    }
    initialarray(Q, A->mu, B->nu);
    if(A->tu * B->tu == 0){
        outputarray(Q, A->mu, B->nu);
        return ;
    }

    //用于检验是否正确
    // output(A);
    // printf("the rpos of A is:");
    // printrpos(A);
    //处理A的每一行
    for(i = 0; i < A->mu; i++){
        if(A->rpos[i] == -1){
            ;
        }else{
            for(na = A->rpos[i]; (na < A->tu) && A->data[na].i == i; na++){
                ib = A->data[na].j;//找到对应元在B中的行号
                if(B->rpos[ib] == -1){
                    ;
                    //这一行b没有数据
                }else{
                    for(nb = B->rpos[ib]; (nb < B->tu) && B->data[nb].i == ib; nb++){
                        j = B->data[nb].j;
                        Q[i][j] += A->data[na].e * B->data[nb].e;
                    }
                }
            }
        }
    }
    printf("The result of A * B is\n");
    outputarray(Q, A->mu, B->nu);
}

void getinput(TSMatrix *A, char name){
    int num;
    int i, j, k;
    int index=0;
    int preline = -1;
    //注意，此处下标是从0开始的
    printf("Matrix %c   row:",name);
    scanf("%d", &i);
    printf("Matrix %c   column:",name);
    scanf("%d", &j);
    printf("Matrix %c    non-zero elements:",name);
    scanf("%d", &k);
    A->mu = i;
    A->nu = j;
    A->tu = k;
    //printf("mu:%d nu:%d tu:%d", A->mu, A->nu, A->tu);
    printinfo(STYLE);
    for (num = 0; num < A->tu; num++) {
        scanf("%d %d %d", &i, &j, &k);
        //printf("num is %d\n", num);
        A->data[num].i = i;
        A->data[num].j = j;
        A->data[num].e = k;
        //初始化rpos，每行第一个数的下标
        //若i!-preline说明换行
       if (i > preline) {
            while (i > preline + 1){
           //     //空行首地址下标-1
           //空行首地址下标-1
                A->rpos[++preline] = -1;
            }
            A->rpos[++preline] = num;
        }
    } 
}



void output(TSMatrix *A){
    int i;
    int j;
    int k;
    k = 0;
    for (i = 0; i < A->mu; i++) {
        for (j = 0; j < A->nu; j++) {
            if (A->data[k].i == i && A->data[k].j==j) {
                printf("%d ", A->data[k].e);
                k++;
            }else
                printf("0 ");
        }
        printf("\n");
    }
}

TSMatrix* lalloc(void){
    return (TSMatrix *)malloc(sizeof(TSMatrix));
}

void printrpos(TSMatrix *A){
    int i;
    for(i=0;i<A->mu;i++){
        printf("line %d is %d\n",i,A->rpos[i]);
    }
}


void initialarray(int a[][MAXRC], int m, int n){
    int i,j;
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            a[i][j]=0;
        }
    }
}

void outputarray(int a[][MAXRC], int m, int n){
    int i,j;
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }    
}
