#include <stdio.h>
#include <stdlib.h>
void Sort();
void kill();
void menu();
typedef struct P_node{
    char t_name[20];///������
    long t_id;///����id
    float t_time;///��������ʱ��
    int priority;///�������ȼ�
}PCB;

///��������
typedef struct Tnode *T;
struct Tnode{
    int data;
    T next;///ָ��������е���һ��λ��
};

///��Ϣ�������
typedef struct Linkqueue{
    T front,rear;///ͷָ���βָ��ֱ�ָ��������е�ͷ��β
}LQ;

LQ L;
PCB pcb[100];///�ṹ��PCB���飬ģ�⵱ǰ�ڴ��С
int N=0;///��ǰ�Ѿ������Ľ�����Ŀ

///�������г�ʼ��
void InitQueue(){
    L.rear=L.front=malloc(sizeof(T));
    if(!L.front)
        exit(-2);
    L.front->next=NULL;
    return;
}

///�������̣�����PCB,������̲���
void Create(){
    int n;///Ҫ�����Ľ��̵���Ŀ
    printf("������Ҫ�����Ľ��̵���Ŀ��");
    scanf("%d",&n);
    ///Ҫ����Ľ��������ڵ�ǰϵͳ���ڴ�
    if(n>100){
        printf("��ǰ�ڴ�����");
        return;
    }
    int i,j;
    long id;
    T t;
        for(i=1;i<=n;i++){
            ///����������Ϊ��ʱ����һ������id����ֱ��д��
            if(L.front->next==NULL){
                printf("���������id��");
                scanf("%ld",&pcb[i+N].t_id);
                getchar();
                printf("�������������");
                gets(pcb[i+N].t_name);
                printf("�������������ʱ�䣺");
                scanf("%f",&pcb[i+N].t_time);
                getchar();
                printf("������������ȼ���");
                scanf("%d",&pcb[i+N].priority);
                N++;///��ǰ��������1
            }else{
                printf("���������id��");
                scanf("%ld",&id);
                ///���������в�Ϊ��ʱ����Ҫ����������Ľ���id�Ƿ��ظ�
                for(j=1;j<i+N;){
                    if(id==pcb[j].t_id){
                        printf("����ID�Ѿ����ڣ�\n���������룺");
                        scanf("%ld",&id);
                        j=0;
                    }else{
                        j++;
                    }
                }
                pcb[i+N].t_id=id;
                getchar();
                printf("�������������");
                gets(pcb[i+N].t_name);
                printf("�������������ʱ�䣺");
                scanf("%f",&pcb[i+N].t_time);
                getchar();
                printf("������������ȼ���");
                scanf("%d",&pcb[i+N].priority);
                N++;///��ǰ��������1
            }
            ///����ǰ���̼����������
            t=malloc(sizeof(T));
            t->data=N;
            t->next=NULL;
            ///�����������еĽ��̼�����Ϣ�������
            L.rear->next=t;
            L.rear=t;

        }
    Sort();
    return;

}
void Sort(){
    int i,j;
     ///�����̰����ȼ�����
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

///��ʾ�Ѿ������Ľ���
void display(){
    T p;
    p=L.front;
    if(p->next==NULL){
        printf("��ǰ�޽��̣�");
    }
    while(p->next!=NULL){
        p=p->next;
        printf(" ����ID��%ld\n ��������%s \n����ʱ��:%f \n���ȼ���%d\n",pcb[p->data].t_id,pcb[p->data].t_name,pcb[p->data].t_time,pcb[p->data].priority);
    }
}
///������ֹ
void kill(){
    int id;
    T p;
    p=L.front;
    if(p->next==NULL){
        printf("��ǰ�޽���!\n\n");
    }else{
        printf("����Ҫ��ֹ�Ľ��̵�id��");
        scanf("%ld",&id);
        while(pcb[p->next->data].t_id!=id){
            if(p->next==NULL){
                printf("�ý��̲����ڣ�\n");
                return;
            }
            p=p->next;
        }
        if(pcb[p->next->data].t_id==id){
            p->next=p->next->next;
            
            /*��L.front->next==NULLʱ��
            ˵����ǰɱ���Ľ�����ϵͳ�����һ�����̣�
            ��ʱ��λָ��ָ��ͬһ��λ��*/
            
            if(L.front->next==NULL){
                L.front=L.rear;
            }
            /*��p->next==NULLʱ��
            ˵����ǰɱ���Ľ����Ƕ�β���̣�
            ��ʱβָ��ָ��p*/
            if(p->next==NULL){
                L.rear=p;
            }
            ///ɾ������ֹ���̵�PCB���̿��ƿ���Ϣ
            while(p->next!=NULL){
                p->next->data--;
                pcb[p->next->data]=pcb[p->next->data+1];
                p=p->next;
            }
        }
    printf("�ɹ�ɱ�����̣�\n");
    return;
    }

}
void menu(){
    int n;
    while(1){
        printf("������ʾϵͳ\n");
        printf("**************************************************\n");
        printf("1.��������\n");
        printf("2.�鿴����\n");
        printf("3.ɱ������\n");
        printf("4.�˳�����\n");
        printf("���������ѡ��1-4����");
        scanf("%d",&n);
        switch(n){
            case 1:Create();
            break;
            case 2:display();
            break;
            case 3:kill();
            break;
            case 4:return ;
            default:printf("û�����ѡ�");
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

