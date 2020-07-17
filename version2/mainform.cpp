#include "mainform.h"
#include "ui_mainform.h"

mainForm::mainForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainForm)
{
    ui->setupUi(this);

    this->setWindowTitle("功能选择");
    this->setFixedSize(650, 550);
    this->setStyleSheet("QDialog{border-image: url(:/image/mainForm.jpg);}"
                        "QPushButton{background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, "
                                                    "stop:0 rgba(150, 155 , 60, 206), stop:0.35 rgba(150, 155 , 60, 80), "
                                                    "stop:0.4 rgba(150, 155 , 60, 80), stop:0.425 rgba(150, 155 , 60, 156), "
                                                    "stop:0.44 rgba(150, 155 , 60, 80), stop:1 rgba(150, 155 , 60, 0));"
                                                    "font-family:'黑体';"
                                                    "border:none;"
                                                    "}"
                        "font-size:20px;"
                        "border-radius:5px}");

    ui->calculatorPushButton->setGeometry(QRect(QPoint(0,47), QPoint(250, 297)));
    ui->calculatorPushButton->setText("简易计算器");

    ui->customPushButton->setGeometry(QRect(QPoint(400,205), QPoint(650, 455)));
    ui->customPushButton->setText("对话框");

    ui->httpJSONPushButton->setGeometry(QRect(QPoint(0,223), QPoint(250, 473)));
    ui->httpJSONPushButton->setText("天气");

    ui->playPushButton->setGeometry(QRect(QPoint(400,-107), QPoint(650, 157)));
    ui->playPushButton->setText("播放视频");

    ui->backPushButton->setGeometry(QRect(QPoint(140,500), QPoint(510, 540)));
    ui->backPushButton->setStyleSheet("background-color:rgb(201, 220 , 69, 150);"
                                      "font-size:20px;"
                                      "border-radius:5px");
    ui->backPushButton->setText("退出登录");

    //动态分配空间, 不能指定父对象
    m_threadGet = new QThread(this);//创建子线程
    m_threadDeal = new QThread(this);
    m_myThreadGet = new myThread;//指定父对象后下面不可以在加入子线程中,下面的子线程相当于其父对象
    m_myThreadDeal = new myThread;
    m_myThreadGet->moveToThread(m_threadGet);//把自定义的线程加入到子线程中
    m_myThreadDeal->moveToThread(m_threadDeal);

    connect(m_myThreadDeal,&myThread::mySignal,this,&mainForm::dealSignal);
    connect(this, &mainForm::startThread, m_myThreadGet, &myThread::getInstructions);
    connect(this,&mainForm::startThread,m_myThreadDeal,&myThread::dealInstructions);
    connect(this,&mainForm::destroyed,this,&mainForm::deadClose);
    tStart();
}

mainForm::~mainForm()
{
    deadClose();
    delete ui;
}

void mainForm::on_backPushButton_clicked()
{
    emit sendSignal();
    this->close();
}

void mainForm::on_calculatorPushButton_clicked()
{
    calculator* new_cal = new calculator();
    connect(new_cal, SIGNAL(sendSignal()), this, SLOT(reshow()));
    this->close();
    new_cal->show();
}

void mainForm::reshow() {
    m_myThreadGet->getInstructions();
    this->show();
}

void mainForm::on_customPushButton_clicked()
{
    custom* new_cus = new custom();
    connect(new_cus, SIGNAL(sendSignal()), this, SLOT(reshow()));
    this->hide();
    new_cus->show();
}

void mainForm::on_httpJSONPushButton_clicked()
{
    http_JSON* new_http = new http_JSON();
    connect(new_http, SIGNAL(sendSignal()), this, SLOT(reshow()));
    this->hide();
    new_http->show();
}

void mainForm::on_playPushButton_clicked()
{
    QPlayer* new_play = new QPlayer();
    connect(new_play, SIGNAL(sendSignal()), this, SLOT(reshow()));
    this->hide();
    new_play->show();
}

void mainForm::deadClose() {
    tStop();
    delete m_threadGet;
    delete m_myThreadGet;
    delete m_threadDeal;
    delete m_myThreadDeal;
}

//子线程信号触发的主线程中的槽函数
void mainForm::dealSignal() {
    qDebug()<<"dealMsg : "<<m_myThreadDeal->msg;

    if(m_myThreadDeal->msg == "简易计算器") {
        qDebug()<<"简易计算器";
        on_calculatorPushButton_clicked();
    }
    else if(m_myThreadDeal->msg == "天气"){
        qDebug()<<"天气";
        on_httpJSONPushButton_clicked();
    }
    else if(m_myThreadDeal->msg == "播放视频"){
        qDebug()<<"播放视频";
        on_playPushButton_clicked();
    }
    else if(m_myThreadDeal->msg == "对话框"){
        qDebug()<<"对话框";
        on_customPushButton_clicked();
    }
    else if(m_myThreadDeal->msg == "聊天"){
        qDebug()<<"聊天";

        on_backPushButton_clicked();
    }
    else if(m_myThreadDeal->msg == "退出登录"){
        qDebug()<<"退出登录";
        on_backPushButton_clicked();
    }
    else {
        qDebug()<<"nothing";
    }
}

void mainForm::tStart() {
    m_threadGet->start();
    m_threadDeal->start();

    m_myThreadGet->setFlag(false);
    m_myThreadDeal->setFlag(false);

    emit startThread();
}

void mainForm::tStop() {
    m_myThreadGet->setFlag(true);
    m_threadGet->terminate();

    m_myThreadDeal->setFlag(true);
    m_threadDeal->terminate();
}
