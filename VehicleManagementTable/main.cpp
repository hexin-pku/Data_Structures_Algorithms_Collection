#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

//建立了四种数据结构：违章记录结点，违章记录链表，车辆信息结点，车辆管理线性表
typedef struct RecordNode//建立一次违章记录
{
    int idx;
    int Time;//时间可以扩充为数据类型
    char Place[6];//地点最多5位
    char Code[12];//
    char Treat[3];//Y或N
    RecordNode* link;
}RN, *PRN;

typedef struct RecordList//建立一辆车的违章记录表
{
    //int car_id;//表示记录的车辆
    int rcd_total;//表示一共的违章次数
    PRN rcd_head;//再次犯了结构体内的指针也应该动态分配的问题！！！
}RL, *PRL;

typedef struct CarInfor//建立一个车辆信息记录
{
    char Car_idnum[3];
    char Car_type[6];
    int Car_buytime;
    int Car_price;
    char Car_owner[13];
    PRL Car_rlist;
}Car, *PCar;

typedef struct CarList//建立一张车辆信息记录表，最多100辆车
{
    int cartotal;
    Car cars[100];
}CList, *PCL;

PCL InitRcd_Lst(PCL pcl, const char* id, int ridx, int time, const char* place, const char* code, const char* treat);
PCL InputRcdInfo(PCL pcl);//实现违章记录的输入
PCL InputCarInfo();//实现管理车辆的输入

PCar FindCar(PCL pcl, const char* id);//逆向查找给定车号的车，返回指针
PCar FindOwnr(PCL pcl, const char* owner);
int FindIdx(PCL pcl, const char* id);//正向查找给定车号的车，返回数组中的位置
int BeenAllTreated(PCL pcl, Car car);//判断违章是否处理完毕

int ShowRcdInfo(PRL rlist);//实现违章记录的输出
int ShowCarInfo(PCL pcl);//实现所有车的输出
int ShowIdRcdInfo(PCL pcl, const char* id);//实现给定车号所有违章记录的输出
int ShowOwnrRcdInfo(PCL pcl, const char* owner);

//以下函数实现统计功能
int StatCarRecord(PCL pcl, const char* id);//统计给定车号的违章记录
int MarchTime(PRL prl, int t1, int t2);//统计时间段是否违章，返回违章次数
int StatTimeRecord(PCL pcl, int t1, int t2);
int MarchPlace(PRL prl, const char* place);//统计地点是否违章，返回违章次数
int StatPlaceRecord(PCL pcl, const char* place);
int MarchCode(PRL prl, const char* code);//统计某一代码的违章，返回违章次数
int StatCodeRecord(PCL pcl, const char* code);

//添加更改删除车辆信息的操作
PCar Init_ZeroRcd(PCar car);//为新车分配违章记录的初始化内存
PCL AddCarInfo(PCL pcl, const char* carid ,const char* Owner, const char* type, int btime, int bprice);
PCL AddCar_Lst(PCL pcl, const char* carid);//新加车辆
PCL AlertCarInfo_Lst(PCL pcl, const char* id, const char* carowner, const char* cartype, int buytime, int buyprice);//更改车辆不存在将自动创建
PCL DelCar_Lst(PCL pcl, const char* carid);//删除车辆

//添加更改删除违章信息的操作
Car AddRcd_Car(Car car,int ridx, int time, const char* place, const char* code, const char* treat);//需要一个idx
PCL AddRcd_Lst(PCL pcl, const char* id, int time, const char* place, const char* code, const char* treat);//不需要一个idx

Car AlertRcd_Car(Car car, int ridx, int time, const char* place, const char* code, const char* treat);//需要一个idx
PCL AlertRcd_Lst(PCL pcl, const char* id, int time, const char* place, const char* code, const char* treat);//更改内容不存在将自动创建
Car DelRcd_Car(Car car, int time, const char* place);
PCL DelRcd_Lst(PCL pcl, const char* id, int time, const char* place);

//释放总内存空间
int DelLst(PCL pcl);

int main(void)
{
    //实现文件输入输出

    freopen("d:\\codefile\\datafile\\dataout2.txt", "w", stdout);

    //以下两行实现输入和输出
    PCL pcarlist=InputCarInfo();
    pcarlist=InputRcdInfo(pcarlist);
    ShowCarInfo(pcarlist);//输出整体车辆的信息

    //实现违章记录的统计功能
    ShowOwnrRcdInfo(pcarlist, "hans");
    ShowOwnrRcdInfo(pcarlist, "jojo");
    StatCarRecord(pcarlist,"20");//输出车号2的违章信息
    StatTimeRecord(pcarlist,20170105,20170106);//统计5-10时间段的违章记录
    StatPlaceRecord(pcarlist,"Rd_7");//统计100022地点的违章记录
    StatCodeRecord(pcarlist,"Accident");//统计代码违章记录


    //实现车辆的添加、更改和删除
    pcarlist=AddCarInfo(pcarlist, "0", "wang","BENZ",20170306,220000);//0表示车牌号自动添加

    pcarlist=DelCar_Lst(pcarlist,"13");
    pcarlist=DelCar_Lst(pcarlist,"36");
    ShowCarInfo(pcarlist);


    //实现违章记录的添加、更改和删除
    pcarlist=AddRcd_Lst(pcarlist, "29", 20170307, "Rd_10", "Accident", "N");//添加一个违章记录，返回线性表

    //释放内存空间
    DelLst(pcarlist);

    return 0;
}

PCL InputRcdInfo(PCL pcl)
{
    freopen("d:\\codefile\\datafile\\accident.txt", "r", stdin);
    char tmpid[3]="1";//初始化
    char id[3]="00";
    int i=0;
    while( i < pcl->cartotal)
    {
        scanf("%s",tmpid);
        if(strcmp(tmpid, "0")!=0)
        {
            strncpy(id,tmpid,3);
            i++;
        }

        int ridx;scanf("%d",&ridx);
        if(ridx==0)continue;
        char place[6];scanf("%s",place);
        int time;scanf("%d", &time);
        char code[12];scanf("%s",code);
        char treat[3];scanf("%s",treat);
        pcl=InitRcd_Lst(pcl, id, ridx, time, place, code, treat);
    }

    return pcl;//因为仍然有指针指向内存，所以程序终结rlist清除但内存没有泄露；
}

PCL InputCarInfo()//实现车辆信息的输入
{
    FILE* fin=fopen("d:\\codefile\\datafile\\CarData.txt", "r");
    PCL carlist=(PCL)malloc(sizeof(CList));//申请一个管理车辆的数组
    carlist->cartotal=0;

    int i=0;
    while(fscanf(fin,"%s",(carlist->cars[i].Car_idnum))!=EOF && carlist->cartotal < 100)//对每一辆车逐一进行信息输入
    {
        carlist->cartotal++;
        //信息输入
        fscanf(fin,"%s",(carlist->cars[i].Car_type));
        fscanf(fin,"%d",&(carlist->cars[i].Car_buytime));
        fscanf(fin,"%d",&(carlist->cars[i].Car_price));
        fscanf(fin,"%s",(carlist->cars[i].Car_owner));//s代表指针，所以char数组本身即指针，不用再次取址
        carlist->cars[i].Car_rlist=(PRL)malloc(sizeof(RL));
        carlist->cars[i].Car_rlist->rcd_total=0;
        carlist->cars[i].Car_rlist->rcd_head=(PRN)malloc(sizeof(RN));
        carlist->cars[i].Car_rlist->rcd_head->link=NULL;
        i++;//一定要放后面才对
    }
    return carlist;//只是建好管理表，没有导入违章记录
}

PCL InitRcd_Lst(PCL pcl, const char* id, int ridx, int time, const char* place, const char* code, const char* treat)//用于带违章编号的初始化
{
    int idx=FindIdx(pcl, id);
    if(idx==-1)
    {
        pcl=AddCar_Lst(pcl,id);//如果不存在，在列表后面新加一辆车
        Car tmp=pcl->cars[pcl->cartotal-1];
        pcl->cars[pcl->cartotal-1]=AddRcd_Car(tmp, tmp.Car_rlist->rcd_total+1, time, place, code, treat);
        printf("    车号%s不存在，已经创建并添加记录。\n", id);
        return pcl;
    }
    pcl->cars[idx]=AddRcd_Car(pcl->cars[idx], ridx, time, place, code, treat);
    return pcl;
}

PCar FindCar(PCL pcl, const char* id)//给出一个车号，从后向前找到这辆车并返回指针
{
    PCar findcar=pcl->cars+(pcl->cartotal-1);//从最后一辆车查找
    for(int i=pcl->cartotal; strcmp(findcar->Car_idnum, id)!=0 && findcar!=pcl->cars && i>0;findcar--,i--);//倒序查找更符合添加的情况
    if(findcar==pcl->cars && strcmp(findcar->Car_idnum, id)!=0)
    {
        return NULL;//表示查找异常
    }
    else return findcar;
}

int FindIdx(PCL pcl, const char* id)//给你一个车号，找出这辆车在列表中的位置idx，编号idx从0开始计数
{
    int i=0;
    while(strcmp(pcl->cars[i].Car_idnum, id)!=0 && i < (pcl->cartotal)-1)//cartotal-1注意要减1
    {
        i++;
    }
    if(i==pcl->cartotal-1 && strcmp(pcl->cars[i].Car_idnum, id)!=0)
    {
        return -1;//表示没有查到
    }
    else return i;
}

PCar FindOwnr(PCL pcl, const char* owner)//给你一个车号，找出这辆车在列表中的位置idx，编号idx从0开始计数
{
    int i=0;
    while(strcmp(pcl->cars[i].Car_owner, owner)!=0 && i < (pcl->cartotal)-1)//cartotal-1注意要减1
    {
        i++;
    }
    if(i==pcl->cartotal-1 && strcmp(pcl->cars[i].Car_idnum, owner)!=0)
    {
        return NULL;//表示没有查到，注意到返回空指针
    }
    else return pcl->cars+i;
}

int ShowRcdInfo(PRL rlist)//实现一辆车的所有违章记录的输出
{
    PRN head=rlist->rcd_head->link;
    if(head==NULL)
    {
        printf("    没有违章\n\n");
        return 1;
    }
    for(int i=0;i<(rlist->rcd_total)&&(head!=NULL);i++)//???
    {
        printf("    违章编号%-3d:     违章时间:%-11d  违章地点:%-9.6s  违章代码:%-12.10s  违章处理:%-2s\n",head->idx,head->Time,head->Place,head->Code,head->Treat);
        head=head->link;
    }
    printf("\n");
    return 0;
}

int ShowCarInfo(PCL pcl)//实现所有车的违章记录的输出
{
    printf("记录的车辆一共%d辆：\n",pcl->cartotal);

    for(int i = 0;i < pcl->cartotal;i++)
    {
        printf("车辆号码:%-10.2s",pcl->cars[i].Car_idnum);
        printf("车辆类型:%-9.6s",pcl->cars[i].Car_type);
        printf("车辆购买时间:%-11d",pcl->cars[i].Car_buytime);
        printf("车辆价格:%d        ",pcl->cars[i].Car_price);
        printf("车辆车主:%-12.12s\n",pcl->cars[i].Car_owner);
        ShowRcdInfo(pcl->cars[i].Car_rlist);
    }
    printf("\n");
    return 0;
}

int ShowIdRcdInfo(PCL pcl, const char* id)//实现某一辆车的违章记录的输出
{
    printf("查询车辆车号为 %-3.2s 的违章记录：\n",id);
    PCar findcar=FindCar(pcl, id);
    if(findcar==NULL)
    {
        printf("    不存在这辆车的车号，请确认！\n\n");
        return 1;//表示查找异常
    }
    if(findcar->Car_rlist->rcd_head->link==NULL)
    {
        printf("    车号为%-3.2s的车辆没有违章记录！\n\n",id);
        return 0;
    }
    ShowRcdInfo(findcar->Car_rlist);
    return 0;
}

int ShowOwnrRcdInfo(PCL pcl, const char* owner)//实现某一辆车的违章记录的输出
{
    printf("查询车辆车主为  %-5.5s 的违章记录：\n",owner);
    PCar findownr=FindOwnr(pcl, owner);
    if(findownr==NULL)
    {
        printf("    不存在这个车主，请确认！\n\n");
        return 1;//表示查找异常
    }
    if(findownr->Car_rlist->rcd_head->link==NULL)
    {
        printf("    车主  %-5.5s的车辆没有违章记录！\n\n",owner);
        return 0;
    }
    ShowRcdInfo(findownr->Car_rlist);
    return 0;
}

int StatCarRecord(PCL pcl, const char* id)//寻找一辆车的所有违章记录
{
    printf("查找车号为%-5.2s车辆的违章记录：\n",id);
    PCar findcar=FindCar(pcl, id);
    if(findcar==NULL)
    {
        printf("    车号为%s的车辆信息不存在，请核实！\n\n",id);
        return 1;//1表示寻找异常
    }
    printf("    车辆号码:%-10.2s",findcar->Car_idnum);
    printf("车辆类型:%-9.6s",findcar->Car_type);
    printf("车辆购买时间:%-11d",findcar->Car_buytime);
    printf("车辆价格:%d        ",findcar->Car_price);
    printf("车辆车主:%-12.12s\n",findcar->Car_owner);

    printf("    该车辆一共违章%d次：\n",findcar->Car_rlist->rcd_total);
    ShowRcdInfo(findcar->Car_rlist);
    return 0;
}

int MarchTime(PRL prl, int t1, int t2)//统计时间段是否违章，返回违章次数
{
    PRN head=prl->rcd_head->link;
    int cnt=0;
    while(head!=NULL)
    {
        if((head->Time)>=t1 && (head->Time) < t2)
        {
            cnt++;
        }
        head=head->link;
    }
    return cnt;
}

int StatTimeRecord(PCL pcl, int t1, int t2)
{
    printf("查找违章时间段在%d--%d内的违章车辆：\n",t1,t2);
    int haveone=0;
    for(int i=0;i<pcl->cartotal;i++)//i没有初始化
    {
        int sum=MarchTime(pcl->cars[i].Car_rlist,t1, t2);
        if(sum)
        {
            printf("    车辆车号%-3.2s：    违章%d次\n",pcl->cars[i].Car_idnum,sum);
            haveone=1;
        }
    }
    if(!haveone)printf("    这个时间段内没有违章车辆。\n");
    printf("\n");
    return 0;
}

int MarchPlace(PRL prl, const char* place)
{
    PRN head=prl->rcd_head->link;
    int cnt=0;
    while(head!=NULL)
    {
        if(*(head->Place) ==*place)
        {
            cnt++;
        }
        head=head->link;
    }
    return cnt;
}

int StatPlaceRecord(PCL pcl, const char* place)
{
    printf("查找违章地点在%s的违章车辆：\n",place);
    int haveone=0;
    for(int i=0;i<pcl->cartotal;i++)
    {
        int sum=MarchPlace(pcl->cars[i].Car_rlist,place);
        if(sum)
        {
            printf("    车辆车号%-3.2s：    违章%d次\n",pcl->cars[i].Car_idnum,sum);
            haveone=1;
        }
    }
    if(!haveone)printf("    这个地点内没有违章记录。\n");
    printf("\n");
    return 0;
}

int MarchCode(PRL prl, const char* code)
{
    PRN head=prl->rcd_head->link;
    int cnt=0;
    while(head!=NULL)
    {
        if(strcmp(head->Code, code)==0)
        {
            cnt++;
        }
        head=head->link;
    }
    return cnt;
}

int StatCodeRecord(PCL pcl, const char* code)
{
    printf("查找违章代码%s对应的违章车辆：\n",code);
    int haveone=0;
    for(int i=0;i<pcl->cartotal;i++)
    {
        int sum=MarchCode(pcl->cars[i].Car_rlist,code);
        if(sum)
        {
            printf("    车辆车号%-3.2s：    违章%d次\n",pcl->cars[i].Car_idnum,sum);
            haveone=1;
        }
    }
    if(!haveone)
    {
        printf("    这个违章代码没有违章记录。\n\n");//使用sum会有问题，换成haveone
        return 1;
    }
    printf("\n");
    return 0;
}

PCar Init_ZeroRcd(PCar car)
{
    car->Car_rlist=(PRL)malloc(sizeof(RL));
    car->Car_rlist->rcd_total=0;
    car->Car_rlist->rcd_head=(PRN)malloc(sizeof(RN));
    car->Car_rlist->rcd_head->link=NULL;
    return car;
}

PCL AddCar_Lst(PCL pcl, const char* carid)//考虑到先添加再赋值，否者参数写多太多
{
    printf("添加车辆车号%s到列表中：\n",carid);
    if(FindCar(pcl, carid)!=NULL)
    {
        printf("    车辆已经存在，无法添加。\n");
        return pcl;
    }
    if((pcl->cartotal+1)>100)
    {
        printf("    溢出，无法添加！\n\n");
        return pcl;
    }
    PCar findcar=pcl->cars+pcl->cartotal;
    strncpy(pcl->cars[pcl->cartotal].Car_idnum,carid,3);
    strncpy(pcl->cars[pcl->cartotal].Car_type,"----",4);//type初始化
    pcl->cars[pcl->cartotal].Car_buytime=-1;
    pcl->cars[pcl->cartotal].Car_price=-1;
    strncpy(pcl->cars[pcl->cartotal].Car_owner,"------",4);//owner初始化
    findcar=Init_ZeroRcd(findcar);

    pcl->cartotal++;
    return pcl;
}

PCL AddCarInfo(PCL pcl, const char* carid, const char* owner, const char* type, int btime, int bprice)
{
    PCar findcar;
    if(strcmp(carid, "0")==0)
    {
        char sid[3];
        findcar=pcl->cars+pcl->cartotal;//
        sprintf(sid, "%d", pcl->cartotal+1);
        strncpy(findcar->Car_idnum,sid,3);
        strncpy(findcar->Car_owner,owner,12);
        strncpy(findcar->Car_type,type,6);
        findcar->Car_buytime=btime;
        findcar->Car_price=bprice;
        pcl->cartotal++;
        findcar=Init_ZeroRcd(findcar);
        return pcl;
    }
    else findcar=FindCar(pcl, carid);
    if(findcar!=NULL )
    {
        printf("    该车辆已经存在，无法再次添加！\n");
        return pcl;
    }
    strncpy(findcar->Car_idnum,carid,3);
    strncpy(findcar->Car_owner,owner,12);
    strncpy(findcar->Car_type,type,6);
    findcar->Car_buytime=btime;
    findcar->Car_price=bprice;
    pcl->cartotal++;
    return pcl;
}

PCL AlertCarInfo_Lst(PCL pcl, const char* id, const char* carowner, const char* cartype, int buytime, int buyprice)//修改或补充车辆信息，暂时没有太多的功能——————————————————————
{
    printf("更改 车号%s 的车辆信息：", id);
    PCar findcar=pcl->cars+pcl->cartotal-1;//从最后一辆车查找
    for(int i=pcl->cartotal; *(findcar->Car_idnum) != *id && findcar!=pcl->cars;findcar--,i--);//倒序查找更符合添加的情况
    if(findcar==pcl->cars && *(findcar->Car_idnum)!=*id)
    {
        pcl=AddCar_Lst(pcl,id);//如果不存在，在列表后面新加一辆车
        pcl=AlertCarInfo_Lst(pcl, id, carowner, cartype, buytime, buyprice);//新加后再将信息输入
        printf("    该车辆不存在并重新创建！\n");
        return pcl;//这个return不能省略！！
    }
    findcar->Car_buytime=buytime;
    strncpy(findcar->Car_owner,carowner,10);
    findcar->Car_price=buyprice;
    strncpy(findcar->Car_type,cartype,5);
    printf("    更改完成请查看。\n");
    return pcl;
}

int BeenAllTreated(PCL pcl, Car car)
{
    PRN head=car.Car_rlist->rcd_head;
    while(head->link!=NULL)
    {
        head=head->link;
        if(strcmp(head->Treat,"N")==0)return 0;//如果有没有处理的违章，返回0
    }
    return 1;//违章全部处理
}

PCL DelCar_Lst(PCL pcl, const char* carid)
{
    printf("搜索并删除车号%s的车辆：\n",carid);
    int idx=FindIdx(pcl, carid);
    if(idx==-1)
    {
        printf("    删除车辆没有找到！\n\n");
        return pcl;
    }
    if(BeenAllTreated(pcl, pcl->cars[idx])==0)
    {
        printf("    还有违章没有处理，无法删除！\n\n");
        return pcl;
    }
    for(;idx<(pcl->cartotal-1);idx++)
    {
        pcl->cars[idx]=pcl->cars[idx+1];
    }
    strncpy(pcl->cars[pcl->cartotal-1].Car_idnum,"none",4);//none表示置空不存在车辆???
    pcl->cartotal--;
    printf("    删除完成！\n\n");
    return pcl;
}

Car AddRcd_Car(Car car,int ridx, int time, const char* place, const char* code, const char* treat)//添加某个已知车辆的一次违章
{
    //AddRcd_Car(pcl->cars[idx], ridx, time, place, code, treat);
    PRN newrcd=(PRN)malloc(sizeof(RN));
    newrcd->idx=ridx;
    newrcd->Time=time;
    strncpy(newrcd->Place,place,6);
    strncpy(newrcd->Code,code, 12);
    strncpy(newrcd->Treat,treat,3);
    PRN tail=car.Car_rlist->rcd_head;
    while(tail->link!=NULL)tail=tail->link;//tail不能在for中命名，新记录加在违章记录的末尾
    tail->link=newrcd;
    newrcd->link=NULL;
    car.Car_rlist->rcd_total++;//注意自增
    return car;
}

PCL AddRcd_Lst(PCL pcl, const char* id, int time, const char* place, const char* code, const char* treat)//添加某个车辆车号的一次违章（车辆不存在将自动创建），返回列表
{
    printf("添加 车号%s 的一次违章记录：\n", id);
    int idx=FindIdx(pcl, id);
    if(idx==-1)
    {
        pcl=AddCar_Lst(pcl,id);//如果不存在，在列表后面新加一辆车
        Car tmp=pcl->cars[pcl->cartotal-1];
        pcl->cars[pcl->cartotal-1]=AddRcd_Car(tmp, (tmp.Car_rlist->rcd_total+1), time, place, code, treat);
        printf("    改车号不存在，已经创建并添加记录。\n\n");
        return pcl;
    }
    pcl->cars[idx]=AddRcd_Car(pcl->cars[idx], pcl->cars[idx].Car_rlist->rcd_total+1, time, place, code, treat);
    printf("    添加完成请查看。\n\n");
    return pcl;
}

Car AlertRcd_Car(Car car, int ridx, int time, const char* place, const char* code, const char* treat)
{
    PRN head=car.Car_rlist->rcd_head;
    int haveone=0;
    while(head->link!=NULL)
    {
        head=head->link;
        if(head->idx==ridx && head->Time==time && strcmp(head->Place, place)==0 && strcmp(head->Code, code)==0)
        {
            strncpy(head->Treat, treat, 3);
            haveone=1;
        }
    }
    if(!haveone)
    {
        car=AddRcd_Car(car, car.Car_rlist->rcd_total+1, time, place, code, treat);//如果没有找到更改目标，将自动在违章记录的末尾创建
    }
    return car;
}

PCL AlertRcd_Lst(PCL pcl, const char* id, int time, const char* place, const char* code, const char* treat)
{
    printf("添加车号为%s的的一条违章记录：\n", id);
    int idx=FindIdx(pcl, id);
    if(idx==-1)
    {
        printf("    车辆不存在，将自动创建并读入数据！\n\n");
        pcl=AddCar_Lst(pcl, id);
        int tmprtot=pcl->cars[pcl->cartotal-1].Car_rlist->rcd_total;
        pcl->cars[pcl->cartotal-1]=AlertRcd_Car(pcl->cars[pcl->cartotal-1], tmprtot+1, time, place, code, treat);
        return pcl;
    }
    int tmprtot=pcl->cars[pcl->cartotal-1].Car_rlist->rcd_total;
    pcl->cars[idx]=AlertRcd_Car(pcl->cars[idx], tmprtot, time, place, code, treat);
    printf("    添加完成！\n\n");
    return pcl;
}

Car DelRcd_Car(Car car, int time, const char* place)//删除某时间地点的违章记录
{
    PRN head=car.Car_rlist->rcd_head;
    PRN prehead=head;
    int OriRLTol=car.Car_rlist->rcd_total;
    while(head->link!=NULL)
    {
        head=head->link;
        if(head->Time==time && strcmp(head->Place, place)==0)
        {
            if(head->link!=NULL)
            {
                head=head->link;//一个特殊地可以连续删除节点的方案
                free(prehead->link);
                prehead->link=head;
                head=prehead;
                car.Car_rlist->rcd_total--;
            }
            else
            {
                free(head);
                prehead->link=NULL;
                car.Car_rlist->rcd_total--;
            }
        }
        else prehead=prehead->link;
    }
    if(car.Car_rlist->rcd_total==OriRLTol)
        printf("    该车辆不存在复合要求的违章信息！\n");
    return car;
}

PCL DelRcd_Lst(PCL pcl, const char* id, int time, const char* place)
{
    printf("删除 车号%s 时间%d 地点%s 内的违章信息：\n", id, time, place);
    int idx=FindIdx(pcl, id);
    if(idx==-1)
    {
        printf("    该车辆不存在！\n\n");
        return pcl;
    }
    pcl->cars[idx]=DelRcd_Car(pcl->cars[idx], time, place);
    printf("\n");
    return pcl;
}


int DelLst(PCL pcl)
{
    PRN head;
    PRN p;
    for(int i=0;i<pcl->cartotal;i++)
    {
        head=pcl->cars[i].Car_rlist->rcd_head;
        p=head->link;
        while(p!=NULL)
        {
            free(head);
            head=p;
            p=head->link;
        }
        free(head);
    }
    free(pcl);
    return 0;//free顺序似乎又不影响
}

