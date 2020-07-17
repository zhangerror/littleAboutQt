#include "mythread.h"

myThread::myThread(QObject *parent) : QObject(parent)
{
    isStop=false;
}

void myThread::getInstructions() {
    system("echo  star  >  /home/lpenguin/qt/xunfei_he/pipeg");
}

void myThread::dealInstructions() {
    while(isStop==false) {
        //打开管道文件   open
        int fd = ::open("/home/lpenguin/qt/xunfei_he/pipe",O_RDWR);
        //读取数据
        char buf[4096]={0};
        ::read(fd,buf,4096);

        msg = buf;

        QRegExp rx("[\u4e00-\u9fa5]");
        QStringList list;
        int pos = 0;
        while ((pos = rx.indexIn(msg, pos)) != -1) {
           list << rx.cap(0);
           pos += rx.matchedLength();
        }
        qDebug() << list;
        msg = "";
        for(int i=0;i<list.size()/2; ++i) {
            msg += list[i];
        }

        //关闭
        ::close(fd);

        if(true==isStop) {
            break;
        }

        emit mySignal();
        qDebug()<<"deal 子线程号:"<<QThread::currentThread();
    }
}

void myThread::setFlag(bool flag){
    isStop=flag;
}
