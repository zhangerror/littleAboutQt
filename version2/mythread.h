#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QThread>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>
#include <QRegExp>
#include <QDir>

class myThread : public QObject
{
    Q_OBJECT
public:
    explicit myThread(QObject *parent = nullptr);
    void setFlag(bool flag=true);//设置线程中标志,用于停止线程

public slots:
    void getInstructions();//线程处理函数, 也就是实际开启的线程
    void dealInstructions();

signals:
    void mySignal(); //定义一个信号,在该子线程中每秒发射一次该信号

private:
    bool isStop;//线程工作标志

public:
    QString msg;
};

#endif // MYTHREAD_H
