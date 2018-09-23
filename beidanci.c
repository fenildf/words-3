#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define k 30000//修改k值可以随时调整可存储单词的最大量
struct xuanzeti//定义用于随机选择题的结构体
{
    int p;//选项位置
    int xiabiao;//选项下标
}xuanxiang[4];
struct danci//储存单词的结构体数组
{
    char english[20];
    char chinese[30];
}word[k];
struct shoucang
{
    char english[20];
    char chinese[30];
    struct shoucang * next;//用于存储收藏单词表的链表
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
int count_shoucang(struct shoucang * head)//收藏单词表计数函数
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
int travel(int a,char b[],int moshi,struct danci word[])//遍历数组，找到需要的单词，返回所寻找的单词的下标
{
    int i,flag=a+1;
    if(moshi==1)
    {
        for(i=0;i<a;i++)
        {
            if(strcmp(b,word[i].english)==0)
                flag=i;
        }
    }//按英文查找
    else if(moshi==2)
    {
        for(i=0;i<a;i++)
        {
            if(strcmp(b,word[i].chinese)==0)
                flag=i;
        }
    }//按中文查找
    return flag;
}
void tiankong(int n,struct danci word[])//随机产生填空题
{
    int cishu,i,j,moshi,zheng=0,wu=0;
    char daan[30];
    printf("请输入你想背的单词个数：");
    scanf("%d",&cishu);
    printf("1代表英译汉，2代表汉译英\n");
    printf("请输入你的单词填空模式：");
    getchar();
    scanf("%d",&moshi);
    srand(time(NULL));//随机数种子
    if(moshi==1)//英译汉
    {
        for(i=0;i<cishu;i++)
        {
            j=rand()%n;
            printf("%s\n",word[j].english);
            printf("请输入答案：");
            scanf("%s",daan);
            if(strcmp(daan,word[j].chinese)==0)
            {
                printf("正确\n");
                zheng++;
            }
            else
            {
                printf("错误，正确答案是%s\n",word[j].chinese);
                wu++;
            }
        }
        printf("共背单词%d个，正确%d个，错误%d个\n",cishu,zheng,wu);
    }
    else if(moshi==2)//汉译英
    {
        for(i=0;i<cishu;i++)
        {
            j=rand()%n;
            printf("%s\n",word[j].chinese);
            printf("请输入答案：");
            scanf("%s",daan);
            if(strcmp(daan,word[j].english)==0)
            {
                printf("正确\n");
                zheng++;
            }
            else
            {
                printf("错误，正确答案是%s\n",word[j].english);
                wu++;
            }
        }
        printf("共背单词%d个，正确%d个，错误%d个\n",cishu,zheng,wu);
    }
    else
        printf("输入有误，请检查");
}
void dayin(struct shoucang * head)//将收藏单词表输出到屏幕上
{
    struct shoucang * p;
    p=head->next;
    while(p!=NULL)
    {
        printf("%s %s\n",p->english,p->chinese);
        p=p->next;
    }
}
struct shoucang * luru_shoucang()//从文件中读取收藏单词表
{
    int i,count;
    struct shoucang *head,*p,*q;
    char cunchu[30],ch;
    FILE * fp;
    p=(struct shoucang *)malloc(sizeof(struct shoucang));
    p->next=NULL;
    head=p;//分配一个不储存数据的头结点，但是p在下面要参与循环，会发生变化，故使用一个head指针确定p的位置，head的位置不改变，并作为返回值
    fp=fopen("shoucang.txt","r");
    ch=fgetc(fp);
    if(ch==EOF)
    {
        printf("无收藏单词\n");//判断是否为空文件，即读取一个字符，如果该字符是EOF，则退出函数
        return head;
    }
    fclose(fp);
    fp=fopen("shoucang.txt","r");
    if(fp==NULL)
    {
        printf("未找到shoucang.txt");
        exit(0);
    }
    for(i=0;i<k;i++)
    {
        q=(struct shoucang *)malloc(sizeof(struct shoucang));
        fscanf(fp,"%s",cunchu);
        strcpy(q->english,cunchu);
        fscanf(fp,"%s",cunchu);
        strcpy(q->chinese,cunchu);//将数据存入q节点中
        p->next=q;//将p节点的next指向q，此时相当于head节点的next也指向了q
        q->next=NULL;//q的next指针指向空
        p=q;//移动负责表示读取节点位置的p指针
        if(feof(fp))
            break;
    }
    fclose(fp);
    printf("收藏单词已写入链表\n");
    dayin(head);
    return head;
}
int luru(struct danci word[])//用于录入文件中的词表
{
    int i,j,count=0;
    FILE * fp;
    fp=fopen("words.txt","r");
    if(fp==NULL)
    {
        printf("找不到words.txt");
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
    printf("本次共录入了%d个单词\n",count);
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
    printf("查重已完成\n");
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
        printf("无收藏单词\n");
        return 0;
    }
    printf("请输入你想要删除的收藏单词：");
    scanf("%s",a);
    p=head;
    q=head->next;
    while(q!=NULL)
    {
        if(strcmp(a,q->english)==0)
        {
            printf("你要删除的单词是%s，中文意思是%s，是否确认（1代表确认）：",q->english,q->chinese);
            scanf("%d",&panduan);
            if(panduan==1)
            {
                s=q;//记录下待删除节点的位置
                p->next=q->next;
                q=q->next;//用两个指针在读取时跳过待删除节点的，p总是指向q前面的一个节点
                free(s);//删除节点数据
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
        printf("未找到该单词\n");
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
    printf("文件已更新，现在有%d个收藏单词\n",count_shoucang(head));
    dayin(head);
    return count_shoucang(head);
}
int chazhao(int a,struct danci word[])
{
    int moshi,n;
    char b[30];
    printf("1代表英译汉，2代表汉译英\n");
    printf("请选择翻译模式：");
    scanf("%d",&moshi);
    getchar();
    printf("请输入需要翻译的词组：");
    scanf("%s",b);
    n=travel(a,b,moshi,word);
    if(n==a+1)
        printf("词表中没有该单词\n");
    else
    {
        if(moshi==1)
            printf("中文意思为：%s\n",word[n].chinese);
        else
            printf("英文意思为：%s\n",word[n].english);
    }
}
int menu()//菜单函数
{
    int a;
    printf("1代表从文件中更新词库\n");
    printf("2代表查找单词\n");
    printf("3代表单词填空\n");
    printf("4代表添加单词\n");
    printf("5代表单词选择题\n");
    printf("6代表从文件中更新并打印收藏单词表\n");
    printf("7代表添加收藏单词\n");
    printf("8代表删除收藏单词\n");
    printf("9代表单词表查重\n");
    printf("10代表收藏单词判断题\n\n");
    printf("请选择要使用的功能：");
    scanf("%d",&a);
    return a;
}
void xuanze(int n,struct danci word[])//产生随机选择题函数，n代表单词总个数
{
    int cishu,i,j,zhonglei,answer,m,q,zheng_xiabiao,zheng_p;
    int trans_1,trans_2;
    int count_z=0,count_w=0;
    FILE * fp;//count用于记录正确与错误的题目数,answer用于存储用户的输入数据，i、j、m、n用于计数，trans用于交换结构体中的数据，zheng用于存储正确答案的相关数据
    printf("请输入你想做的题目数：");
    scanf("%d",&cishu);
    getchar();
    printf("请选择题目种类（1代表英译汉，2代表汉译英）：");
    scanf("%d",&zhonglei);
    for(i=0;i<cishu;i++)
    {
        if(zhonglei==1)
        {
            srand(time(NULL));//随机数种子
            xuanxiang[0].xiabiao=rand()%n;//开始时结构体数组0号中存储着正确答案
            zheng_xiabiao=xuanxiang[0].xiabiao;
            xuanxiang[1].xiabiao=rand()%n;
            xuanxiang[2].xiabiao=rand()%n;
            xuanxiang[3].xiabiao=rand()%n;
            while(xuanxiang[1].xiabiao==xuanxiang[0].xiabiao)
                 xuanxiang[1].xiabiao=rand()%n;
            while(xuanxiang[2].xiabiao==xuanxiang[0].xiabiao||xuanxiang[2].xiabiao==xuanxiang[1].xiabiao)
                 xuanxiang[2].xiabiao=rand()%n;
            while(xuanxiang[3].xiabiao==xuanxiang[0].xiabiao||xuanxiang[3].xiabiao==xuanxiang[1].xiabiao||xuanxiang[3].xiabiao==xuanxiang[2].xiabiao)
                 xuanxiang[3].xiabiao=rand()%n;//产生正确答案的下标与三个错误答案，并确保下标不重合
            printf("%s\n",word[zheng_xiabiao].english);//输出题目
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
                xuanxiang[3].p=((rand()%4)+1);//产生放置各个答案的位置，并确保位置不重合
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
                        xuanxiang[q].p=trans_2;//按照p值从大到小重新排列结构体数组
                    }
                }
            }
            for(j=0;j<4;j++)
                printf("%d、%s\n",xuanxiang[j].p,word[xuanxiang[j].xiabiao].chinese);
            printf("请输入正确选项前的序号：");
            scanf("%d",&answer);
            if(answer==zheng_p)
            {
                printf("正确\n");
                count_z++;
            }
            else
            {
                printf("错误，正确答案是%s\n",word[zheng_xiabiao].chinese);
                count_w++;
                fp=fopen("wrong.txt","a");
                fprintf(fp,"%s",word[zheng_xiabiao].english);
                fprintf(fp,"\n");
                fclose(fp);
                printf("错误单词已输出到文件\n");
            }
        }
        else if(zhonglei==2)
        {
            srand(time(NULL));//随机数种子
            xuanxiang[0].xiabiao=rand()%n;//开始时结构体数组0号中存储着正确答案
            zheng_xiabiao=xuanxiang[0].xiabiao;
            xuanxiang[1].xiabiao=rand()%n;
            xuanxiang[2].xiabiao=rand()%n;
            xuanxiang[3].xiabiao=rand()%n;
            while(xuanxiang[1].xiabiao==xuanxiang[0].xiabiao)
                 xuanxiang[1].xiabiao=rand()%n;
            while(xuanxiang[2].xiabiao==xuanxiang[0].xiabiao||xuanxiang[2].xiabiao==xuanxiang[1].xiabiao)
                 xuanxiang[2].xiabiao=rand()%n;
            while(xuanxiang[3].xiabiao==xuanxiang[0].xiabiao||xuanxiang[3].xiabiao==xuanxiang[1].xiabiao||xuanxiang[3].xiabiao==xuanxiang[2].xiabiao)
                 xuanxiang[3].xiabiao=rand()%n;//产生正确答案的下标与三个错误答案，并确保下标不重合
            printf("%s\n",word[zheng_xiabiao].chinese);//输出题目
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
                xuanxiang[3].p=((rand()%4)+1);//产生放置各个答案的位置，并确保位置不重合
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
                        xuanxiang[q].p=trans_2;//按照p值从大到小重新排列结构体数组
                    }
                }
            }
            for(j=0;j<4;j++)
                printf("%d、%s\n",xuanxiang[j].p,word[xuanxiang[j].xiabiao].english);
            printf("请输入正确选项前的序号：");
            scanf("%d",&answer);
            if(answer==zheng_p)
            {
                printf("正确\n");
                count_z++;
            }
            else
            {
                printf("错误，正确答案是%s\n",word[zheng_xiabiao].english);
                count_w++;
                fp=fopen("wrong.txt","a");
                fprintf(fp,"%s",word[zheng_xiabiao].english);
                fprintf(fp,"\n");
                fclose(fp);
                printf("错误单词已输出到文件\n");
            }
        }
        else
            printf("输入有误，请重新输入");
    }
    printf("正确%d道，错误%d道\n",count_z,count_w);
}
int tianjia_shoucang(int n2,int a,struct shoucang * head,struct danci word[])
{
    int cishu,flag,count=0,panduan,pin=n2;
    FILE * fp;
    struct shoucang *p,*q,*start,*i;
    printf("请输入你要添加单词的个数：");
    scanf("%d",&cishu);
    q=(struct shoucang *)malloc(sizeof(struct shoucang));
    q->next=NULL;
    start=q;
    while(cishu--)//建立新表用于存储数据
    {
        p=(struct shoucang *)malloc(sizeof(struct shoucang));
        printf("请输入待添加单词：");
        scanf("%s",p->english);
        flag=travel(a,p->english,1,word);
        if(flag==a+1)
        {
            printf("未找到该单词\n");
            continue;
        }
        printf("你要添加的单词是：%s，中文意思是%s，是否确认（1代表确认）：",word[flag].english,word[flag].chinese);
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
            continue;//考虑收藏单词表为空时的情况
        }
        fprintf(fp,"\n");
        fprintf(fp,"%s",p->english);
        fprintf(fp,"\n");
        fprintf(fp,"%s",p->chinese);
        fclose(fp);
        q->next=p;//相当于start的尾指针指向了第一个存有数据的节点，但start本身并不保存数据
        p->next=NULL;
        q=p;//移动用于指示的指针q
    }
    printf("文件已更新\n");
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
    printf("收藏单词目前有%d个\n",count);
    dayin(head);
    return count;
}
void tianjia()//运行添加函数时须关闭words.txt，否则将无法写入文件
{
    int i=1,flag;
    char yingwen[20],zhongwen[20],* output;
    while(i==1)
    {
        printf("请输入待添加单词的英文：");
        scanf("%s",yingwen);
        output=trans(yingwen);
        getchar();
        printf("请输入带添加单词的中文：");
        scanf("%s",zhongwen);
        printf("您要添加的单词的英文是：%s，中文是：%s，是否确认（输入1代表确认）：",output,zhongwen);
        scanf("%d",&flag);
        if(flag!=1)
            exit(0);
        FILE * fp;
        fp=fopen("words.txt","a");
        if(fp==NULL)
        {
            printf("找不到words.txt");
            exit(0);
        }
        fseek(fp,0,SEEK_END);//将光标移动到文件末尾
        fprintf(fp,"\n");
        fprintf(fp,"%s",output);
        fprintf(fp,"\n");
        fprintf(fp,"%s",zhongwen);
        fclose(fp);
        printf("添加成功\n");
        printf("输入1继续添加：");
        scanf("%d",&i);
    }
}
void panduan_shoucang(int n2,struct shoucang * head)
{
    int flag1,flag2,cishu,tixing,input;
    //tixing用来判断输出正确还是错误,input用于储存用户输入
    struct shoucang *p1,*p2,*q;
    char shuru[30];
    if(n2==0)
    {
        printf("无收藏单词");
        exit(0);
    }
    printf("请选择你想做的题目道数：");
    scanf("%d",&cishu);
    while(cishu--)
    {
        srand(time(NULL));
        flag1=rand()%n2;//flag1下存储的是需要输出的英语单词
        flag2=rand()%n2;
        while(flag2==flag1)
            flag2=rand()%n2;
        q=head->next;
        while(flag1--)
        {
            if(flag1==1)
            {
                p1=q;//p1中存储着需要输出的英语单词
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
            printf("输入1代表搭配正确，2代表搭配错误：");
            scanf("%d",&input);
            if(input==1)
                printf("你对了！\n");
            else if(input==2)
                printf("你错了！上述搭配正确\n");
            else
                printf("输入有误\n");
        }
        else
        {
            printf("%s %s\n",p2->english,p1->chinese);
            printf("输入1代表搭配正确，2代表搭配错误：");
            scanf("%d",&input);
            if(input==2)
            {
                printf("你对了！请输入上述英语单词的正确中文意思：");
                scanf("%s",shuru);
                if(strcmp(shuru,p2->chinese)==0)
                    printf("你对了！\n");
                else
                    printf("你错了！正确意思是：%s\n",p2->chinese);
            }
            else if(input==1)
            {
                printf("你错了！正确搭配如下：\n");
                printf("%s %s\n%s %s",p1->english,p1->chinese,p2->english,p2->chinese);
            }
            else
                printf("输入有误\n");
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
    printf("录入了%d个收藏单词\n\n",n2);//启动后会自动更新一次词库
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
            printf("录入了%d个收藏单词\n",n2);
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
        printf("输入yes继续：");
        scanf("%s",panduan);
	printf("\n");
    }
    return 0;
}
/*powered by oneman233*/
/*大小写不敏感 按字母排序*/
