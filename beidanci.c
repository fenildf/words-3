#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define k 30000//�޸�kֵ������ʱ�����ɴ洢���ʵ������
struct xuanzeti//�����������ѡ����Ľṹ��
{
    int p;//ѡ��λ��
    int xiabiao;//ѡ���±�
}xuanxiang[4];
struct danci//���浥�ʵĽṹ������
{
    char english[20];
    char chinese[30];
}word[k];
struct shoucang
{
    char english[20];
    char chinese[30];
    struct shoucang * next;//���ڴ洢�ղص��ʱ������
};
static char * trans(char * input)
{
    int j=0;
    static char output[20];
    char * pin;
    pin=input;
    while(*pin!='\0')
    {
        if(*pin>=65&&*pin<=90)
        {
            output[j]=*pin+32;
            j++;
        }
        else if(*pin>=97&&*pin<=122)
        {
            output[j]=*pin;
            j++;
        }
        else
        {

        }
        pin++;
    }
    output[j+1]='\0';
    return output;
}
int count_shoucang(struct shoucang * head)//�ղص��ʱ��������
{
    int count=0;
    struct shoucang * p;
    p=head->next;
    while(p!=NULL)
    {
        count++;
        p=p->next;
    }
    return count;
}
int travel(int a,char b[],int moshi,struct danci word[])//�������飬�ҵ���Ҫ�ĵ��ʣ�������Ѱ�ҵĵ��ʵ��±�
{
    int i,flag=a+1;
    if(moshi==1)
    {
        for(i=0;i<a;i++)
        {
            if(strcmp(b,word[i].english)==0)
                flag=i;
        }
    }//��Ӣ�Ĳ���
    else if(moshi==2)
    {
        for(i=0;i<a;i++)
        {
            if(strcmp(b,word[i].chinese)==0)
                flag=i;
        }
    }//�����Ĳ���
    return flag;
}
void tiankong(int n,struct danci word[])//������������
{
    int cishu,i,j,moshi,zheng=0,wu=0;
    char daan[30];
    printf("���������뱳�ĵ��ʸ�����");
    scanf("%d",&cishu);
    printf("1����Ӣ�뺺��2������Ӣ\n");
    printf("��������ĵ������ģʽ��");
    getchar();
    scanf("%d",&moshi);
    srand(time(NULL));//���������
    if(moshi==1)//Ӣ�뺺
    {
        for(i=0;i<cishu;i++)
        {
            j=rand()%n;
            printf("%s\n",word[j].english);
            printf("������𰸣�");
            scanf("%s",daan);
            if(strcmp(daan,word[j].chinese)==0)
            {
                printf("��ȷ\n");
                zheng++;
            }
            else
            {
                printf("������ȷ����%s\n",word[j].chinese);
                wu++;
            }
        }
        printf("��������%d������ȷ%d��������%d��\n",cishu,zheng,wu);
    }
    else if(moshi==2)//����Ӣ
    {
        for(i=0;i<cishu;i++)
        {
            j=rand()%n;
            printf("%s\n",word[j].chinese);
            printf("������𰸣�");
            scanf("%s",daan);
            if(strcmp(daan,word[j].english)==0)
            {
                printf("��ȷ\n");
                zheng++;
            }
            else
            {
                printf("������ȷ����%s\n",word[j].english);
                wu++;
            }
        }
        printf("��������%d������ȷ%d��������%d��\n",cishu,zheng,wu);
    }
    else
        printf("������������");
}
void dayin(struct shoucang * head)//���ղص��ʱ��������Ļ��
{
    struct shoucang * p;
    p=head->next;
    while(p!=NULL)
    {
        printf("%s %s\n",p->english,p->chinese);
        p=p->next;
    }
}
struct shoucang * luru_shoucang()//���ļ��ж�ȡ�ղص��ʱ�
{
    int i,count;
    struct shoucang *head,*p,*q;
    char cunchu[30],ch;
    FILE * fp;
    p=(struct shoucang *)malloc(sizeof(struct shoucang));
    p->next=NULL;
    head=p;//����һ�����������ݵ�ͷ��㣬����p������Ҫ����ѭ�����ᷢ���仯����ʹ��һ��headָ��ȷ��p��λ�ã�head��λ�ò��ı䣬����Ϊ����ֵ
    fp=fopen("shoucang.txt","r");
    ch=fgetc(fp);
    if(ch==EOF)
    {
        printf("���ղص���\n");//�ж��Ƿ�Ϊ���ļ�������ȡһ���ַ���������ַ���EOF�����˳�����
        return head;
    }
    fclose(fp);
    fp=fopen("shoucang.txt","r");
    if(fp==NULL)
    {
        printf("δ�ҵ�shoucang.txt");
        exit(0);
    }
    for(i=0;i<k;i++)
    {
        q=(struct shoucang *)malloc(sizeof(struct shoucang));
        fscanf(fp,"%s",cunchu);
        strcpy(q->english,cunchu);
        fscanf(fp,"%s",cunchu);
        strcpy(q->chinese,cunchu);//�����ݴ���q�ڵ���
        p->next=q;//��p�ڵ��nextָ��q����ʱ�൱��head�ڵ��nextҲָ����q
        q->next=NULL;//q��nextָ��ָ���
        p=q;//�ƶ������ʾ��ȡ�ڵ�λ�õ�pָ��
        if(feof(fp))
            break;
    }
    fclose(fp);
    printf("�ղص�����д������\n");
    dayin(head);
    return head;
}
int luru(struct danci word[])//����¼���ļ��еĴʱ�
{
    int i,j,count=0;
    FILE * fp;
    fp=fopen("words.txt","r");
    if(fp==NULL)
    {
        printf("�Ҳ���words.txt");
        exit(0);
    }
    for(i=0;i<k;i++)
    {
        fscanf(fp,"%s",word[i].english);
        fscanf(fp,"%s",word[i].chinese);
        count++;
        if(feof(fp))
            break;
    }
    printf("���ι�¼����%d������\n",count);
    return count;
}
void chachong(int n1,struct danci word[])
{
    struct danci bijiao[n1];
    int i,j,count=0;
    FILE * fp;
    for(i=0;i<n1;i++)
    {
        for(j=i+1;j<n1;j++)
        {
            if(strcmp(word[i].english,word[j].english)==0)
                strcpy(word[j].english,"oneman233");
        }
        if(strcmp(word[i].english,"oneman233")==0)
            continue;
        strcpy(bijiao[count].english,word[i].english);
        strcpy(bijiao[count].chinese,word[i].chinese);
        count++;
    }
    fp=fopen("words.txt","w");
    for(i=0;i<count;i++)
    {
        if(i==0)
        {
            fprintf(fp,"%s",bijiao[i].english);
            fprintf(fp,"\n");
            fprintf(fp,"%s",bijiao[i].chinese);
            continue;
        }
        fprintf(fp,"\n");
        fprintf(fp,"%s",bijiao[i].english);
        fprintf(fp,"\n");
        fprintf(fp,"%s",bijiao[i].chinese);
    }
    fclose(fp);
    printf("���������\n");
}
int shanchu(int n2,struct shoucang * head)
{
    int panduan,flag=0;
    struct shoucang *p,*q,*s;
    char a[30];
    FILE * fp;
    dayin(head);
    if(n2==0)
    {
        printf("���ղص���\n");
        return 0;
    }
    printf("����������Ҫɾ�����ղص��ʣ�");
    scanf("%s",a);
    p=head;
    q=head->next;
    while(q!=NULL)
    {
        if(strcmp(a,q->english)==0)
        {
            printf("��Ҫɾ���ĵ�����%s��������˼��%s���Ƿ�ȷ�ϣ�1����ȷ�ϣ���",q->english,q->chinese);
            scanf("%d",&panduan);
            if(panduan==1)
            {
                s=q;//��¼�´�ɾ���ڵ��λ��
                p->next=q->next;
                q=q->next;//������ָ���ڶ�ȡʱ������ɾ���ڵ�ģ�p����ָ��qǰ���һ���ڵ�
                free(s);//ɾ���ڵ�����
                flag=1;
            }
            else
                exit(0);
        }
        else
        {
            p=p->next;
            q=q->next;
        }
    }
    if(flag==0)
    {
        printf("δ�ҵ��õ���\n");
        return n2;
    }
    fp=fopen("shoucang.txt","w");
    p=head->next;
    while(p!=NULL)
    {
        if(p->next==NULL)
        {
            fprintf(fp,"%s",p->english);
            fprintf(fp,"\n");
            fprintf(fp,"%s",p->chinese);
            break;
        }
        fprintf(fp,"%s",p->english);
        fprintf(fp,"\n");
        fprintf(fp,"%s",p->chinese);
        fprintf(fp,"\n");
        p=p->next;
    }
    fclose(fp);
    printf("�ļ��Ѹ��£�������%d���ղص���\n",count_shoucang(head));
    dayin(head);
    return count_shoucang(head);
}
int chazhao(int a,struct danci word[])
{
    int moshi,n;
    char b[30];
    printf("1����Ӣ�뺺��2������Ӣ\n");
    printf("��ѡ����ģʽ��");
    scanf("%d",&moshi);
    getchar();
    printf("��������Ҫ����Ĵ��飺");
    scanf("%s",b);
    n=travel(a,b,moshi,word);
    if(n==a+1)
        printf("�ʱ���û�иõ���\n");
    else
    {
        if(moshi==1)
            printf("������˼Ϊ��%s\n",word[n].chinese);
        else
            printf("Ӣ����˼Ϊ��%s\n",word[n].english);
    }
}
int menu()//�˵�����
{
    int a;
    printf("1������ļ��и��´ʿ�\n");
    printf("2������ҵ���\n");
    printf("3���������\n");
    printf("4������ӵ���\n");
    printf("5������ѡ����\n");
    printf("6������ļ��и��²���ӡ�ղص��ʱ�\n");
    printf("7��������ղص���\n");
    printf("8����ɾ���ղص���\n");
    printf("9�����ʱ����\n");
    printf("10�����ղص����ж���\n\n");
    printf("��ѡ��Ҫʹ�õĹ��ܣ�");
    scanf("%d",&a);
    return a;
}
void xuanze(int n,struct danci word[])//�������ѡ���⺯����n�������ܸ���
{
    int cishu,i,j,zhonglei,answer,m,q,zheng_xiabiao,zheng_p;
    int trans_1,trans_2;
    int count_z=0,count_w=0;
    FILE * fp;//count���ڼ�¼��ȷ��������Ŀ��,answer���ڴ洢�û����������ݣ�i��j��m��n���ڼ�����trans���ڽ����ṹ���е����ݣ�zheng���ڴ洢��ȷ�𰸵��������
    printf("����������������Ŀ����");
    scanf("%d",&cishu);
    getchar();
    printf("��ѡ����Ŀ���ࣨ1����Ӣ�뺺��2������Ӣ����");
    scanf("%d",&zhonglei);
    for(i=0;i<cishu;i++)
    {
        if(zhonglei==1)
        {
            srand(time(NULL));//���������
            xuanxiang[0].xiabiao=rand()%n;//��ʼʱ�ṹ������0���д洢����ȷ��
            zheng_xiabiao=xuanxiang[0].xiabiao;
            xuanxiang[1].xiabiao=rand()%n;
            xuanxiang[2].xiabiao=rand()%n;
            xuanxiang[3].xiabiao=rand()%n;
            while(xuanxiang[1].xiabiao==xuanxiang[0].xiabiao)
                 xuanxiang[1].xiabiao=rand()%n;
            while(xuanxiang[2].xiabiao==xuanxiang[0].xiabiao||xuanxiang[2].xiabiao==xuanxiang[1].xiabiao)
                 xuanxiang[2].xiabiao=rand()%n;
            while(xuanxiang[3].xiabiao==xuanxiang[0].xiabiao||xuanxiang[3].xiabiao==xuanxiang[1].xiabiao||xuanxiang[3].xiabiao==xuanxiang[2].xiabiao)
                 xuanxiang[3].xiabiao=rand()%n;//������ȷ�𰸵��±�����������𰸣���ȷ���±겻�غ�
            printf("%s\n",word[zheng_xiabiao].english);//�����Ŀ
            xuanxiang[0].p=((rand()%4)+1);
            zheng_p=xuanxiang[0].p;
            xuanxiang[1].p=((rand()%4)+1);
            xuanxiang[2].p=((rand()%4)+1);
            xuanxiang[3].p=((rand()%4)+1);
            while(xuanxiang[1].p==xuanxiang[0].p)
                xuanxiang[1].p=((rand()%4)+1);
            while(xuanxiang[2].p==xuanxiang[0].p||xuanxiang[2].p==xuanxiang[1].p)
                xuanxiang[2].p=((rand()%4)+1);
            while(xuanxiang[3].p==xuanxiang[0].p||xuanxiang[3].p==xuanxiang[1].p||xuanxiang[3].p==xuanxiang[2].p)
                xuanxiang[3].p=((rand()%4)+1);//�������ø����𰸵�λ�ã���ȷ��λ�ò��غ�
            for(m=0;m<4;m++)
            {
                for(q=m+1;q<4;q++)
                {
                    if(xuanxiang[q].p<xuanxiang[m].p)
                    {
                        trans_1=xuanxiang[m].xiabiao;
                        xuanxiang[m].xiabiao=xuanxiang[q].xiabiao;
                        xuanxiang[q].xiabiao=trans_1;
                        trans_2=xuanxiang[m].p;
                        xuanxiang[m].p=xuanxiang[q].p;
                        xuanxiang[q].p=trans_2;//����pֵ�Ӵ�С�������нṹ������
                    }
                }
            }
            for(j=0;j<4;j++)
                printf("%d��%s\n",xuanxiang[j].p,word[xuanxiang[j].xiabiao].chinese);
            printf("��������ȷѡ��ǰ����ţ�");
            scanf("%d",&answer);
            if(answer==zheng_p)
            {
                printf("��ȷ\n");
                count_z++;
            }
            else
            {
                printf("������ȷ����%s\n",word[zheng_xiabiao].chinese);
                count_w++;
                fp=fopen("wrong.txt","a");
                fprintf(fp,"%s",word[zheng_xiabiao].english);
                fprintf(fp,"\n");
                fclose(fp);
                printf("���󵥴���������ļ�\n");
            }
        }
        else if(zhonglei==2)
        {
            srand(time(NULL));//���������
            xuanxiang[0].xiabiao=rand()%n;//��ʼʱ�ṹ������0���д洢����ȷ��
            zheng_xiabiao=xuanxiang[0].xiabiao;
            xuanxiang[1].xiabiao=rand()%n;
            xuanxiang[2].xiabiao=rand()%n;
            xuanxiang[3].xiabiao=rand()%n;
            while(xuanxiang[1].xiabiao==xuanxiang[0].xiabiao)
                 xuanxiang[1].xiabiao=rand()%n;
            while(xuanxiang[2].xiabiao==xuanxiang[0].xiabiao||xuanxiang[2].xiabiao==xuanxiang[1].xiabiao)
                 xuanxiang[2].xiabiao=rand()%n;
            while(xuanxiang[3].xiabiao==xuanxiang[0].xiabiao||xuanxiang[3].xiabiao==xuanxiang[1].xiabiao||xuanxiang[3].xiabiao==xuanxiang[2].xiabiao)
                 xuanxiang[3].xiabiao=rand()%n;//������ȷ�𰸵��±�����������𰸣���ȷ���±겻�غ�
            printf("%s\n",word[zheng_xiabiao].chinese);//�����Ŀ
            xuanxiang[0].p=((rand()%4)+1);
            zheng_p=xuanxiang[0].p;
            xuanxiang[1].p=((rand()%4)+1);
            xuanxiang[2].p=((rand()%4)+1);
            xuanxiang[3].p=((rand()%4)+1);
            while(xuanxiang[1].p==xuanxiang[0].p)
                xuanxiang[1].p=((rand()%4)+1);
            while(xuanxiang[2].p==xuanxiang[0].p||xuanxiang[2].p==xuanxiang[1].p)
                xuanxiang[2].p=((rand()%4)+1);
            while(xuanxiang[3].p==xuanxiang[0].p||xuanxiang[3].p==xuanxiang[1].p||xuanxiang[3].p==xuanxiang[2].p)
                xuanxiang[3].p=((rand()%4)+1);//�������ø����𰸵�λ�ã���ȷ��λ�ò��غ�
            for(m=0;m<4;m++)
            {
                for(q=m+1;q<4;q++)
                {
                    if(xuanxiang[q].p<xuanxiang[m].p)
                    {
                        trans_1=xuanxiang[m].xiabiao;
                        xuanxiang[m].xiabiao=xuanxiang[q].xiabiao;
                        xuanxiang[q].xiabiao=trans_1;
                        trans_2=xuanxiang[m].p;
                        xuanxiang[m].p=xuanxiang[q].p;
                        xuanxiang[q].p=trans_2;//����pֵ�Ӵ�С�������нṹ������
                    }
                }
            }
            for(j=0;j<4;j++)
                printf("%d��%s\n",xuanxiang[j].p,word[xuanxiang[j].xiabiao].english);
            printf("��������ȷѡ��ǰ����ţ�");
            scanf("%d",&answer);
            if(answer==zheng_p)
            {
                printf("��ȷ\n");
                count_z++;
            }
            else
            {
                printf("������ȷ����%s\n",word[zheng_xiabiao].english);
                count_w++;
                fp=fopen("wrong.txt","a");
                fprintf(fp,"%s",word[zheng_xiabiao].english);
                fprintf(fp,"\n");
                fclose(fp);
                printf("���󵥴���������ļ�\n");
            }
        }
        else
            printf("������������������");
    }
    printf("��ȷ%d��������%d��\n",count_z,count_w);
}
int tianjia_shoucang(int n2,int a,struct shoucang * head,struct danci word[])
{
    int cishu,flag,count=0,panduan,pin=n2;
    FILE * fp;
    struct shoucang *p,*q,*start,*i;
    printf("��������Ҫ��ӵ��ʵĸ�����");
    scanf("%d",&cishu);
    q=(struct shoucang *)malloc(sizeof(struct shoucang));
    q->next=NULL;
    start=q;
    while(cishu--)//�����±����ڴ洢����
    {
        p=(struct shoucang *)malloc(sizeof(struct shoucang));
        printf("���������ӵ��ʣ�");
        scanf("%s",p->english);
        flag=travel(a,p->english,1,word);
        if(flag==a+1)
        {
            printf("δ�ҵ��õ���\n");
            continue;
        }
        printf("��Ҫ��ӵĵ����ǣ�%s��������˼��%s���Ƿ�ȷ�ϣ�1����ȷ�ϣ���",word[flag].english,word[flag].chinese);
        scanf("%d",&panduan);
        if(panduan!=1)
            exit(0);
        strcpy(p->chinese,word[flag].chinese);
        fp=fopen("shoucang.txt","a");
        if(pin==0)
        {
            fprintf(fp,"%s",p->english);
            fprintf(fp,"\n");
            fprintf(fp,"%s",p->chinese);
            pin++;
            fclose(fp);
            q->next=p;
            p->next=NULL;
            q=p;
            continue;//�����ղص��ʱ�Ϊ��ʱ�����
        }
        fprintf(fp,"\n");
        fprintf(fp,"%s",p->english);
        fprintf(fp,"\n");
        fprintf(fp,"%s",p->chinese);
        fclose(fp);
        q->next=p;//�൱��start��βָ��ָ���˵�һ���������ݵĽڵ㣬��start��������������
        p->next=NULL;
        q=p;//�ƶ�����ָʾ��ָ��q
    }
    printf("�ļ��Ѹ���\n");
    i=head;
    while(i!=NULL)
    {
        if(i->next==NULL)
        {
            i->next=start->next;
            break;
        }
        i=i->next;
    }
    count=count_shoucang(head);
    printf("�ղص���Ŀǰ��%d��\n",count);
    dayin(head);
    return count;
}
void tianjia()//������Ӻ���ʱ��ر�words.txt�������޷�д���ļ�
{
    int i=1,flag;
    char yingwen[20],zhongwen[20],* output;
    while(i==1)
    {
        printf("���������ӵ��ʵ�Ӣ�ģ�");
        scanf("%s",yingwen);
        output=trans(yingwen);
        getchar();
        printf("���������ӵ��ʵ����ģ�");
        scanf("%s",zhongwen);
        printf("��Ҫ��ӵĵ��ʵ�Ӣ���ǣ�%s�������ǣ�%s���Ƿ�ȷ�ϣ�����1����ȷ�ϣ���",output,zhongwen);
        scanf("%d",&flag);
        if(flag!=1)
            exit(0);
        FILE * fp;
        fp=fopen("words.txt","a");
        if(fp==NULL)
        {
            printf("�Ҳ���words.txt");
            exit(0);
        }
        fseek(fp,0,SEEK_END);//������ƶ����ļ�ĩβ
        fprintf(fp,"\n");
        fprintf(fp,"%s",output);
        fprintf(fp,"\n");
        fprintf(fp,"%s",zhongwen);
        fclose(fp);
        printf("��ӳɹ�\n");
        printf("����1������ӣ�");
        scanf("%d",&i);
    }
}
void panduan_shoucang(int n2,struct shoucang * head)
{
    int flag1,flag2,cishu,tixing,input;
    //tixing�����ж������ȷ���Ǵ���,input���ڴ����û�����
    struct shoucang *p1,*p2,*q;
    char shuru[30];
    if(n2==0)
    {
        printf("���ղص���");
        exit(0);
    }
    printf("��ѡ������������Ŀ������");
    scanf("%d",&cishu);
    while(cishu--)
    {
        srand(time(NULL));
        flag1=rand()%n2;//flag1�´洢������Ҫ�����Ӣ�ﵥ��
        flag2=rand()%n2;
        while(flag2==flag1)
            flag2=rand()%n2;
        q=head->next;
        while(flag1--)
        {
            if(flag1==1)
            {
                p1=q;//p1�д洢����Ҫ�����Ӣ�ﵥ��
                break;
            }
            q=q->next;
        }
        q=head->next;
        while(flag2--)
        {
            if(flag2==1)
            {
                p2=q;
                break;
            }
            q=q->next;
        }
        tixing=rand()%2;
        if(tixing==0)
        {
            printf("%s %s\n",p1->english,p1->chinese);
            printf("����1���������ȷ��2����������");
            scanf("%d",&input);
            if(input==1)
                printf("����ˣ�\n");
            else if(input==2)
                printf("����ˣ�����������ȷ\n");
            else
                printf("��������\n");
        }
        else
        {
            printf("%s %s\n",p2->english,p1->chinese);
            printf("����1���������ȷ��2����������");
            scanf("%d",&input);
            if(input==2)
            {
                printf("����ˣ�����������Ӣ�ﵥ�ʵ���ȷ������˼��");
                scanf("%s",shuru);
                if(strcmp(shuru,p2->chinese)==0)
                    printf("����ˣ�\n");
                else
                    printf("����ˣ���ȷ��˼�ǣ�%s\n",p2->chinese);
            }
            else if(input==1)
            {
                printf("����ˣ���ȷ�������£�\n");
                printf("%s %s\n%s %s",p1->english,p1->chinese,p2->english,p2->chinese);
            }
            else
                printf("��������\n");
        }
    }
}
int main()
{
    int n1,n2,judge,moshi,i;
    char panduan[10]="yes";
    struct shoucang * head;
    n1=luru(word);
    head=luru_shoucang();
    n2=count_shoucang(head);
    printf("¼����%d���ղص���\n\n",n2);//��������Զ�����һ�δʿ�
    while(strcmp(panduan,"yes")==0)
    {
        judge=menu();
        if(judge==1)
        {
            system("cls");
            n1=luru(word);
        }
        else if(judge==2)
        {
            system("cls");
            chazhao(n1,word);
        }
        else if(judge==3)
        {
            system("cls");
            tiankong(n1,word);
        }
        else if(judge==4)
        {
            system("cls");
            tianjia();
            n1=luru(word);
        }
        else if(judge==5)
        {
            system("cls");
            xuanze(n1,word);
        }
        else if(judge==6)
        {
            system("cls");
            head=luru_shoucang();
            n2=count_shoucang(head);
            printf("¼����%d���ղص���\n",n2);
        }
        else if(judge==7)
        {
            system("cls");
            n2=tianjia_shoucang(n2,n1,head,word);
        }
        else if(judge==8)
        {
            system("cls");
            n2=shanchu(n2,head);
        }
        else if(judge==9)
        {
            system("cls");
            chachong(n1,word);
            n1=luru(word);
        }
        else if(judge==10)
        {
            system("cls");
            panduan_shoucang(count_shoucang(head),head);
        }
        printf("����yes������");
        scanf("%s",panduan);
	printf("\n");
    }
    return 0;
}
/*powered by oneman233*/
/*��Сд������ ����ĸ����*/
