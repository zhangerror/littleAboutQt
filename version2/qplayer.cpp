#include "qplayer.h"
#include "ui_qplayer.h"
#include <QString>

QPlayer::QPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QPlayer)
{
    ui->setupUi(this);
    this->setStyleSheet("QMainWindow{border-image: url(:/image/JSON.png);}"
                        "QPushButton{background-color:rgb(201, 220 , 69, 90);"
                                           "font-size:15px;"
                                           "border-radius:5px}"
                        "QLabel{background-color:rgb(201, 220 , 69, 90);}"
                        "QListWidget{background-color:rgb(201, 220 , 69, 90);}");

    ui->playLabel->setText("");

    ui->backPushButton->setText("返回");

    ui->openPushButton->setText("打开");
    ui->closePushButton->setText("关闭");

    connect(&mprocess,SIGNAL(finished(int)),this,SLOT(play_next(int)));
}

QPlayer::~QPlayer()
{
    delete ui;
}

void QPlayer::on_backPushButton_clicked()
{
    emit sendSignal();
    this->hide();
}

void QPlayer::on_openPushButton_clicked()
{
    //通过文件对话框添加播放文件
    QStringList movies  = QFileDialog::getOpenFileNames(this,"选择视频","/home/gec/Desktop/");

    //把视频路径添加列表中
    ui->listWidget->addItems(movies);
}

void QPlayer::on_closePushButton_clicked()
{
    //杀死进程
    mprocess.kill();
    //确定死透
    mprocess.waitForFinished();
}

void QPlayer::play_next(int num) {
    qDebug()<<QString::number(num);
}

void QPlayer::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //检测到有进程在运行直接kill
    if(mprocess.state()  == QProcess::Running)
    {
        //杀死进程
        mprocess.kill();
        //确定死透
        mprocess.waitForFinished();

    }

    //在次获取视频路径
    QString moviesName = item->text();
    qDebug()<<moviesName;

    QStringList arguments;
    arguments<<"-slave"<<"-quiet"<<"-wid"<<QString::number(ui->playLabel->winId())<<moviesName;

    //启动进程
    mprocess.start("mplayer", arguments);
}
