#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtDebug>
#include<QFile>
#include<QMessageBox>
#include<vector>
Node *head = NULL,*tail = NULL,*p=NULL;
int day= 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"1";

    for(int i =0;i<=99;i++)
    {
        int a[80]={0};
        Node *s = new Node(0,false,a);
        if(head == NULL || i == 0)
        {
        head = s;
        p = s;
        }
        else
        {
         p->N = s;
         p = s;
        }
        if(tail == NULL || i == 99)
        {
        tail = s;
        p = s;
        }
    }
    MainWindow::new_game(head);
}

MainWindow::~MainWindow()
{

        delete ui;
}
Node::Node(int number,bool type,int *data)//构造函数
{
    data = NULL;
this->number = number;
this ->type = type;
   for(int i=0;i<=14;i++)
   {
      ;// this->data[i][0] = data[i];
   }
}
void MainWindow::new_game(Node *head)
{
    p = head;
    //350hua
    for(int i = 0;i<70;i++)
    {
        for(int K=0;K<10;K++)
        {
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*10000+i);
            p->data[K][0]=qrand()%2+1;

            //p->data[K][1] = 200;
            p->data[K][2] = 1;
        }
        p=p->N;
    }
    //350bai
    for(int i = 70;i<100;i++)
    {
        p->type = true;
        for(int K=0;K<10;K++)
        {
           //qDebug()<<"1";
            p->data[K][0] = 3;
           // p->data[K][1] = 200;
            p->data[K][2] = 1;
            //qDebug()<<p->data[K][0];
        }
        p=p->N;
    }
    //300hei
    p=head;
    for(int i = 0;i<100;i++)
    {

        for(int K=0;K<10;K++)
        {


                    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*100+i);
                    p->data[K][1]=qrand()%300+200;
                    //if(i>=70)

                    qDebug()<<p->data[K][0];
                    }


        p=p->N;

        }


    MainWindow::savefile_zhuangtai("a");

}


void MainWindow::grow(Node *head)
{
    *p = *head;
    //grow shuiji
    for(int i = 0;i<100;i++)
    {
        for(int K=0;K<10;K++)
        {
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*10000+i);
            int test =qrand()%13;
            //注意：十倍
         p->data[K][1]+=test;
         p->data[K][2]++;
        }
        p=p->N;
    }
    day++;
}
QString MainWindow::goout(Node *head)//chu lan
{
    int sum = 0,hua=0,bai = 0,hei = 0;;
    int numpig = 0;
    *p = *head;
    //grow shuiji
    for(int i = 0;i<100;i++)
    {
        for(int K=0;K<10;K++)
        {
            if(p->data[K][1]>=750||p->data[K][2]>360)//一个月30天
            {
                numpig ++;
                if(p->data[K][0]==1)
                    sum += 7*p->data[K][1]/10;
                if(p->data[K][0]==2)
                    sum += 6*p->data[K][1]/10;
                if(p->data[K][0]==3)
                    sum += 15*p->data[K][1]/10;
                if(p->type == false)
                {
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*10000+i);
                p->data[K][0]=qrand()%2+1;
                if(p->data[K][0] == 1)
                    hua++;
                if(p->data[K][0] == 2)
                    bai++;
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*100+i);
                p->data[K][1]=qrand()%300+200;
                p->data[K][2]=1;
                }
                else
                {
                    hei++;
                    p->data[K][0]=3;
                    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*100+i);
                    p->data[K][1]=qrand()%300+200;
                    p->data[K][2]=1;
                }
            }
        }

        p=p->N;
    }
    MainWindow::savefile_chulan(QString::number(sum)+"|"+QString::number(numpig)+"|"+QString::number(hua)+"|"+QString::number(bai)+"|"+QString::number(hei));
    MainWindow::savefile_zhuangtai("a");
    return QString::number(sum) + "|" +QString::number(numpig);//返回，一会用正则表达式搞一波
}
QString MainWindow::findpig(int findmode)
{
    p = head;
    if(findmode == 1)//查猪圈
    {
        int a = 0,sum_bai =0,sum_hua=0,sum_hei=0;
          ;      //一会记得从UI传入数据
        for(int i = 0;i< a-1;i++)
        {
            p=p->N;
        }
        for(int i =0;i<10;i++)
        {
        if(p->data[i][0] == 1)
        {
            sum_hua ++;
        }
        if(p->data[i][0] == 2)
        {
            sum_bai ++;
        }
        if(p->data[i][0] == 3)
        {
            sum_hei ++;
        }
        }
        return QString::number(sum_hua+sum_bai+sum_hei) + "|" +QString::number(sum_hua)+ "|" +QString::number(sum_bai)+ "|" +QString::number(sum_hei);//返回，一会用正则表达式搞一波
    }
    if(findmode == 2)//查猪
    {
        int numjuan = 0,weigt =0,type=0,day=0,numpig = 0;
          ;      //一会记得从UI传入数据
        for(int i = 0;i< numjuan-1;i++)
        {
            p=p->N;
        }
        type = p->data[numpig][0];
        weigt = p->data[numpig][1];
        day = p->data[numpig][2];
        return QString::number(type) + "|" +QString::number(weigt) + "|" +QString::number(day);
    }
    if(findmode == 3)//统计
    {
        //体重分为不足50，50·100，100·150，大于150
        //时间分为不足100天，100·200，200·300，300·400
        //种类就三种呗
        int weigh[4]={0},day[4]={0},type[5]={0};
        for(int i = 0;i< 100;i++)
        {
            p=p->N;
            for(int k=0;k<10;k++)
            {
                type[p->data[k][0]]++;
                weigh[std::min(p->data[k][1]/500,3)]++;
                day[std::min(p->data[k][2]/100,3)]++;
            }
        }
        QString t = QString::number(type[1]) + "|" +QString::number(type[2]) + "|" +QString::number(type[3]);
        QString w = QString::number(weigh[0]) + "|" +QString::number(weigh[1]) + "|" +QString::number(weigh[2])+ "|" +QString::number(weigh[3]);
        QString d = QString::number(day[0]) + "|" +QString::number(day[1]) + "|" +QString::number(day[2])+ "|" +QString::number(day[3]);
        return t+","+w+","+d;//注意是逗号隔开的，和其他不一样，70达到
    }
    if(findmode == 4)//文件查找
    {
        int num;
        num = 0;;//传输的次数,要带请选择
        std::vector<QString> a;
          QFile file("search.mt");
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                while (!file.atEnd())
                {
                    QByteArray line = file.readLine();
                    QString str(line);
                    a.push_back(str);
                    //qDebug() << str;
                }
                file.close();
            }
            if(a.size()<=20)
            {
                return a[num - 1];
            }
            else
            {
                return a[a.size() - 20 + num - 1];
            }

    }
    return "ERROR";
}
void MainWindow::savefile_zhuangtai(QString a)
{
    a="1";
    p=head;
    QFile file("pigdata.mt");
    if(! file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::critical(this,"严重错误","文件打开失败，信息未写入，请与开发者联系","确认");
        return;
    }
    for(int i = 0;i<100;i++)
    {
        for(int k = 0;k<10;k++)
        {

            QTextStream out(&file);
            out<<p->data[k][0]<<"|"<<p->data[k][1]<<"|"<<p->data[k][2]<<"|"<<i<<endl;

        }
    p=p->N;
    }
    file.close();
    return;

}
void MainWindow::savefile_chulan(QString a)
{


    QFile file("search.mt");
    if(! file.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"严重错误","文件打开失败，信息未写入，请与开发者联系","确认");
        return;
    }


            QTextStream out(&file);
            out<<day<<"|"<<a;


    file.close();
    return;

}

void MainWindow::on_btn_save_and_close_clicked()
{
    MainWindow::savefile_zhuangtai("QString a");
    exit(0);
}
