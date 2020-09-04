#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include<QString>
#include<algorithm>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Node
{
public:
    Node(int number,bool type,int *data);
    int number,data[15][3];
    //1 = hua 2 = write 3 =blake;
    bool type;
    //if type true,blake is in it pig juan
    Node *F,*N;
};
extern Node *head,*tail,*p;

extern int day;



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void new_game(Node *head);
    void grow(Node *head);
    QString goout(Node *head);
    QString findpig(int findmode);
    void savefile_zhuangtai(QString a);
    //void savefile_gouru(QString a);
    void savefile_chulan(QString a);
    
private slots:
    void on_btn_save_and_close_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
