#include <stdio.h>
#include <stdlib.h>
void Sort();
void kill();
void menu();
typedef struct P_node{
    char t_name[20];///进程名
    long t_id;///进程id
    float t_time;///进程运行时间
    int priority;///进程优先级
}PCB;

///就绪队列
typedef struct Tnode *T;
struct Tnode{
    int data;
    T next;///指向就绪队列的下一个位置
};

///消息缓冲队列
typedef struct Linkqueue{
    T front,rear;///头指针和尾指针分别指向就绪队列的头和尾
}LQ;

LQ L;
PCB pcb[100];///结构体PCB数组，模拟当前内存大小
int N=0;///当前已经创建的进程数目

///就绪队列初始化
void InitQueue(){
    L.rear=L.front=malloc(sizeof(T));
    if(!L.front)
        exit(-2);
    L.front->next=NULL;
    return;
}

///创建进程：申请PCB,填入进程参数
void Create(){
    int n;///要创建的进程的数目
    printf("请输入要创建的进程的数目：");
    scanf("%d",&n);
    ///要申请的进程数大于当前系统的内存
    if(n>100){
        printf("当前内存已满");
        return;
    }
    int i,j;
    long id;
    T t;
        for(i=1;i<=n;i++){
            ///当就绪队列为空时，第一个进程id可以直接写入
            if(L.front->next==NULL){
                printf("请输入进程id：");
                scanf("%ld",&pcb[i+N].t_id);
                getchar();
                printf("请输入进程名：");
                gets(pcb[i+N].t_name);
                printf("请输入进程运行时间：");
                scanf("%f",&pcb[i+N].t_time);
                getchar();
                printf("请输入进程优先级：");
                scanf("%d",&pcb[i+N].priority);
                N++;///当前进程数加1
            }else{
                printf("请输入进程id：");
                scanf("%ld",&id);
                ///当就绪队列不为空时，需要检查所创建的进程id是否重复
                for(j=1;j<i+N;){
                    if(id==pcb[j].t_id){
                        printf("进程ID已经存在！\n请重新输入：");
                        scanf("%ld",&id);
                        j=0;
                    }else{
                        j++;
                    }
                }
                pcb[i+N].t_id=id;
                getchar();
                printf("请输入进程名：");
                gets(pcb[i+N].t_name);
                printf("请输入进程运行时间：");
                scanf("%f",&pcb[i+N].t_time);
                getchar();
                printf("请输入进程优先级：");
                scanf("%d",&pcb[i+N].priority);
                N++;///当前进程数加1
            }
            ///将当前进程加入就绪队列
            t=malloc(sizeof(T));
            t->data=N;
            t->next=NULL;
            ///将就绪队列中的进程加入消息缓冲队列
            L.rear->next=t;
            L.rear=t;

        }
    Sort();
    return;

}
void Sort(){
    int i,j;
     ///将进程按优先级排序
    for(i=1;i<=N;i++){
        for(j=i+1;j<=N;j++){
            if(pcb[i].priority<pcb[j].priority){
                PCB temp=pcb[i];
                pcb[i]=pcb[j];
                pcb[j]=temp;
            }
        }

    }
}

///显示已经就绪的进程
void display(){
    T p;
    p=L.front;
    if(p->next==NULL){
        printf("当前无进程！");
    }
    while(p->next!=NULL){
        p=p->next;
        printf(" 进程ID：%ld\n 进程名：%s \n运行时间:%f \n优先级：%d\n",pcb[p->data].t_id,pcb[p->data].t_name,pcb[p->data].t_time,pcb[p->data].priority);
    }
}
///进程终止
void kill(){
    int id;
    T p;
    p=L.front;
    if(p->next==NULL){
        printf("当前无进程!\n\n");
    }else{
        printf("输入要终止的进程的id：");
        scanf("%ld",&id);
        while(pcb[p->next->data].t_id!=id){
            if(p->next==NULL){
                printf("该进程不存在！\n");
                return;
            }
            p=p->next;
        }
        if(pcb[p->next->data].t_id==id){
            p->next=p->next->next;
            
            /*当L.front->next==NULL时，
            说明当前杀死的进程是系统中最后一个进程，
            此时首位指针指向同一个位置*/
            
            if(L.front->next==NULL){
                L.front=L.rear;
            }
            /*当p->next==NULL时，
            说明当前杀死的进程是队尾进程，
            此时尾指针指向p*/
            if(p->next==NULL){
                L.rear=p;
            }
            ///删除已终止进程的PCB进程控制块信息
            while(p->next!=NULL){
                p->next->data--;
                pcb[p->next->data]=pcb[p->next->data+1];
                p=p->next;
            }
        }
    printf("成功杀死进程！\n");
    return;
    }

}
void menu(){
    int n;
    while(1){
        printf("进程演示系统\n");
        printf("**************************************************\n");
        printf("1.创建进程\n");
        printf("2.查看进程\n");
        printf("3.杀死进程\n");
        printf("4.退出程序\n");
        printf("请输入你的选择（1-4）：");
        scanf("%d",&n);
        switch(n){
            case 1:Create();
            break;
            case 2:display();
            break;
            case 3:kill();
            break;
            case 4:return ;
            default:printf("没有这个选项！");
            break;
        }
    }
    return;
}
int main()
{
    InitQueue();
    menu();
    return 0;
}

