#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QPushButton>

#include "calculator.h"
#include "custom.h"
#include "http_json.h"
#include "qplayer.h"
#include "mythread.h"

namespace Ui {
class mainForm;
}

class mainForm : public QDialog
{
    Q_OBJECT

public:
    explicit mainForm(QWidget *parent = nullptr);
    ~mainForm();

private slots:
    void on_backPushButton_clicked();

    void on_calculatorPushButton_clicked();
    void reshow();

    void on_customPushButton_clicked();

    void on_httpJSONPushButton_clicked();

    void on_playPushButton_clicked();

    void tStart();
    void tStop();
    void dealSignal();  //子线程信号触发的主线程中的槽函数
    void deadClose();   //对话框右上角的 叉号 关闭事件触发的槽函数

signals:
    void sendSignal();
    void startThread();//启动子线程的信号

private:
    Ui::mainForm *ui;

    myThread *m_myThreadGet;
    myThread *m_myThreadDeal;
    QThread *m_threadGet; //定义一个线程对象指针在构造函数中分配空间
    QThread *m_threadDeal;

};

#endif // MAINFORM_H
