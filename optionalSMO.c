#include "optionalhead.h"

int main() {
    int state;
    printf("\n==================================\n");
    printf("\n    Sparse Matrix Operator\n");
    printf("\n----------------------------------\n");
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
        case 4:
            inv();
            break;
        default :
            break;
        }
        printf("\n==================================\n");
        state = getstate();
    }
    printf("\n----------------------------------\n");
    printf("\n  Thanks  :)\n");
    printf("\n==================================\n");
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
        printf("  MENU :)\n0 EXIT\n1 ADD\n2 SUB\n3 MUL\n4 INV\nPlease enter the sequence number:");
    else if (state == STYLE)
        printf("\nEnter matrix in line main order\nInput stype: i j k\n");
    else;
    return;
}

void add(void){
    CrossList a,b,q;
    OLNode *pa;    //第i行中a的当前结点
    OLNode *pb;    //第i行中B的当前结点
    OLNode *pr;    //用于连接行的结点，每次使用都要先初始赋值；
    int i,e;
    if(inputhint(&a,&b,&q)==0)
        return ;
    for(i=0; i<q.mu; i++){
        pa=a.rhead[i]->right;
        pb=b.rhead[i]->right;
        pr=q.rhead[i];
        while(pa!=NULL && pb!=NULL){
            e = pa->e + pb->e;
            if(pa->j == pb->j && e!=0){
                insertnode(&q,pa->i,pa->j,e);//插入
                pa=pa->right;//更新指针
                pb=pb->right;
                pr=pr->right;
            }else if(pa->j < pb->j){
                insertnode(&q,pa->i,pa->j,pa->e);
                pa=pa->right;
                pr=pr->right;
            }else if(pa->j > pb->j){
                insertnode(&q,pb->i,pb->j,pb->e);
                pb=pb->right;
                pr=pr->right;
            }else if(pa->j == pb->j && e==0){
                pa=pa->right;
                pb=pb->right;
            }else
                printf("ERROR:undefined state\n");
        }
        while(pa!=NULL){
                insertnode(&q,pa->i,pa->j,pa->e);
                pa=pa->right;
                pr=pr->right;
        }
        while(pb!=NULL){
                insertnode(&q,pb->i,pb->j,pb->e);
                pb=pb->right;
                pr=pr->right;
        }
    }
    outputhint(&a,&b,'+');
    outputlist(q);
}

void sub(void){
    CrossList a,b,q;
    OLNode *pa;    //第i行中a的当前结点
    OLNode *pb;    //第i行中B的当前结点
    OLNode *pr;    //用于连接行的结点，每次使用都要先初始赋值；
    int i,e;
    if(inputhint(&a,&b,&q)==0)
        return ;
    for(i=0; i<q.mu; i++){
        pa=a.rhead[i]->right;
        pb=b.rhead[i]->right;
        pr=q.rhead[i];
        while(pa!=NULL && pb!=NULL){
            e = pa->e - pb->e;
            if(pa->j == pb->j && e!=0){
                insertnode(&q,pa->i,pa->j,e);
                pa=pa->right;
                pb=pb->right;
                pr=pr->right;
            }else if(pa->j < pb->j){
                insertnode(&q,pa->i,pa->j,pa->e);
                pa=pa->right;
                pr=pr->right;
            }else if(pa->j > pb->j){
                insertnode(&q,pb->i,pb->j,-pb->e);
                pb=pb->right;
                pr=pr->right;
            }else if(pa->j == pb->j && e==0){
                pa=pa->right;
                pb=pb->right;
            }else
                printf("ERROR:undefined state\n");
        }
        while(pa!=NULL){
                insertnode(&q,pa->i,pa->j,pa->e);
                pa=pa->right;
                pr=pr->right;
        }
        while(pb!=NULL){
                insertnode(&q,pb->i,pb->j,-pb->e);
                pb=pb->right;
                pr=pr->right;
        }
    }
    outputhint(&a,&b,'-');
    outputlist(q);
}

void mul(void){
    CrossList a,b;
    int q[MAXRC][MAXRC];
    OLNode *pa;
    OLNode *pb;
    int i,j,ib;
    getinv(&a, 'A');    //获取输入
    getinv(&b, 'B');
    if(a.nu != b.mu){
        printf("ERROR: wrong input data\n");
        printf("Hint: The number of columns in A should be equal to the number of rows in B\n");
        return ;
    }
    initialarray(q, a.mu, b.nu);
    for(i=0;i<a.mu;i++){    
        for(pa=a.rhead[i]->right;pa!=NULL;pa=pa->right){
            ib = pa->j;
            for(pb=b.rhead[ib]->right;pb!=NULL;pb=pb->right){
                j = pb->j;
                q[i][j] += pa->e * pb->e;
            }
        }
    }
    outputhint(&a,&b,'*');
    outputarray(q, a.mu, b.nu);
}

void inv(void){
    int det,i,j,temp,signal;
    CrossList a;
    int b[MAXRC][MAXRC];
    float c[MAXRC][MAXRC];
    getinv(&a, 'A');
    if(a.mu != a.nu){
        printf("ERROR: wrong input data\n");
        printf("Hint: A should be a square matrix\n");
        return ;
    }
    printf("A is\n");
    outputlist(a);
    det=determinant(a,a.mu);
    printf("\ndet(A) is %d\n",det);//行列式
    if(det==0){
        printf("ERROR: Matrix A has no inverse matrix\n");
        return ;
    }
    minor(a,b);//得到余子式
    for(i=0;i<a.mu;i++){
        for(j=0;j<a.nu;j++){
            signal=((i+j)%2) ? -1 : 1;
            c[j][i] = (float) signal * b[i][j] / det;
        }
    }
    printf("\n**********************************\n");
    printf("Input A is \n");
    outputlist(a);
    printf("\n----------------------------------\n");
    printf("The inverse of matrix A is\n");
    for(i=0;i<a.mu;i++){
        for(j=0;j<a.nu;j++){
            printf("%.4f\t",c[i][j]);
        }
        printf("\n");
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

void getinv(CrossList *A, char name){
    //!TODO
    int n,i,j,k;
    OLNode *pwork;
    OLNode *ppoint;
    printf("Matrix %c   row:",name);
    scanf("%d", &A->mu);
    printf("Matrix %c   column:",name);
    scanf("%d", &A->nu);
    printf("Matrix %c    non-zero elements:",name);
    scanf("%d", &A->tu);
    initialhead(A);//对A初始化
    for(n = 0; n < A->tu; n++){
        scanf("%d %d %d", &i, &j, &k);
        insertnode(A,i,j,k);
    }
}

OLNode *oalloc(void){
    return (OLNode *)malloc(sizeof(OLNode));
}

void initialhead(CrossList *p){
    int i;
    OLNode *pwork;
    //将行的头结点初始化
    for(i=0;i<p->mu;i++){
        pwork=oalloc();
        pwork->down=NULL;
        pwork->right=NULL;
        p->rhead[i]=pwork;
    }
    //将列的头结点初始化
    for(i=0;i<p->nu;i++){
        pwork=oalloc();
        pwork->down=NULL;
        pwork->right=NULL;
        p->chead[i]=pwork;
    }
    
    return ;
}


void outputlist(CrossList a){
    int i,j;
    OLNode *p;
    for(i=0;i<a.mu;i++){
        p=a.rhead[i]->right;
        for(j=0;j<a.nu-1;j++){
            if(p!=NULL && j<p->j){
                printf("0 ");
            }else if(p!=NULL && j==p->j){
                printf("%d ",p->e);
                //打印当前结点，右移
                p=p->right;
            }else if(p!=NULL && j>p->j){
                printf("error:j>p->j\n");
            }else if(p==NULL){
                printf("0 ");
            }
        }
        //打印最后一个结点
        if(p==NULL){
            printf("0\n");
        }else{
            printf("%d\n",p->e);
        }
    }    
}


int determinant(CrossList a, int n){
    OLNode *p;
    int z,j,k,r,temp,i;
    int b[MAXRC][MAXRC];
    temp=0;
    if(n>2){
        for(z=0;z<n;z++){    //展开方式为第0行第z列
            CrossList c;
            c.mu = a.mu-1;
            c.nu = a.nu-1;
            initialhead(&c);
            for(j=0;j<n-1;j++){
                p=a.rhead[j+1]->right;
                while(p!=NULL){
                    if(p->j<z){
                        insertnode(&c,p->i-1,p->j,p->e);
                        p=p->right;   
                    }else if(p->j > z){
                        insertnode(&c,p->i-1,p->j-1,p->e);
                        p=p->right;
                    }else
                        p=p->right;
                }
            }
            if(z%2 == 0){
                p=a.chead[z]->down;
                if(p!=NULL && p->i==0)
                    r=p->e * determinant(c,n-1);
                else
                    r=0;
            }else{
                p=a.chead[z]->down;
                if(p!=NULL && p->i==0)
                    r=(-1) * p->e * determinant(c,n-1);
                else
                    r=0;             
            }
            temp += r;
        }
    }else if(n==2){
        for(i=0;i<2;i++){
            p=a.rhead[i]->right;
            b[i][0]=0;
            b[i][1]=0;
            if(p!=NULL && p->j==0){
                b[i][0]=p->e;
                p=p->right;
            }
            if(p!=NULL && p->j==1)
                b[i][1]=p->e;
        }
        temp=b[0][0]*b[1][1]-b[1][0]*b[0][1];
    }else{
        p=a.rhead[0]->right;
        return (p==NULL) ? 0:p->e;
    }
    return temp;
}

void minor(CrossList a, int b[][MAXRC]){
    initialarray(b,a.mu,a.nu);
    OLNode *p;
    OLNode *pc;
    OLNode *pnew;
    int z,j,k,l,n,m;
    n=a.mu;
    for(z=0;z<n;z++){
        l=z;
        for(j=0;j<n;j++){
            m=j;
            CrossList c;
            c.mu=n-1;
            c.nu=n-1;
            initialhead(&c);
            for(k=0;k<n;k++){
                p=a.rhead[k]->right;
                while(p!=NULL){
                    if(p->i<z && p->j<j){
                        insertnode(&c,p->i,p->j,p->e);
                        p=p->right; 
                    }else if(p->i<z && p->j>j){
                        insertnode(&c,p->i,p->j-1,p->e);
                        p=p->right;   
                    }else if(p->i>z && p->j<j){
                        insertnode(&c,p->i-1,p->j,p->e);
                        p=p->right;
                    }else if(p->i>z && p->j>j){
                        insertnode(&c,p->i-1,p->j-1,p->e);
                        p=p->right;
                    }else{
                        p=p->right;
                    }
                }
            }
            b[z][j]=determinant(c,n-1);
        }
    }
}

void insertnode(CrossList *a, int i, int j, int k){
    OLNode *pnew;
    OLNode *p;
    pnew = oalloc();
    pnew->e = k;
    pnew->i = i;
    pnew->j = j;
    pnew->right = NULL;
    pnew->down = NULL;
    //进行行插入
    p = a->rhead[i];
    while(p->right!=NULL){
        p = p->right;
    }
    p->right=pnew;
    //完成列插入
    p=a->chead[pnew->j];
    while(p->down!=NULL){
        p=p->down;
    }
    p->down=pnew; 
}

void outputhint(CrossList *a, CrossList *b, char op){
    printf("\n**********************************\n");
    printf("Input A is \n");
    outputlist(*a);
    printf("\nInput B is \n");
    outputlist(*b);
    printf("\n----------------------------------\n");
    printf("The result of A %c B is\n", op);
}

int inputhint(CrossList *a, CrossList *b,CrossList *q){
    getinv(a, 'A');
    getinv(b, 'B');
    if(a->mu != b->mu || a->nu != b->nu){
        printf("\nERROR: wrong input data\n");
        printf("Hint: matrices should have the same size\n");
        return 0;
    }
    q->mu = a->mu;
    q->nu = a->nu;
    initialhead(q);
    return 1;
}
