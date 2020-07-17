#include "custom.h"
#include "ui_custom.h"

custom::custom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::custom)
{
    ui->setupUi(this);

    this->setStyleSheet("QMainWindow{border-image: url(:/image/custom.jpg);}");

    ui->label->setText("");
    ui->selfBt->setText("清空");
}

custom::~custom()
{
    delete ui;
}

void custom::back() {
    emit sendSignal();
    this->hide();
    //delete this;
}

void custom::on_boxBt_clicked()
{
    //调用信息对话框类
                         //question   information
    int set = QMessageBox::question(this,"操作提示","确定退出？",QMessageBox::Yes,QMessageBox::No);
    if(set == QMessageBox::Yes)
    {
        back();
       qDebug()<<set;
    }
}

void custom::on_fileBt_clicked()
{
    //调用文本对话框类  (返回的字符串是打开的文件的路径)
    QString file =  QFileDialog::getOpenFileName(this,"选择源文件","/home/lpenguin/qt/file");
    qDebug()<<file;
    //返回的字符串显示在单行输入框
    ui->lineEdit->setText(file);
}

void custom::on_colorBt_clicked()
{
    //调用颜色对话框类
    QColor color =  QColorDialog::getColor();
    //获取字符串
    QString rgb = QString("background-color:%1").arg(color.name());
    qDebug()<<rgb;
    //让颜色对话框返回的颜色显示在label
    ui->label->setStyleSheet(rgb);
}

void custom::on_fontBt_clicked()
{
    bool ok=false;
    //调用字体对话框类
    QFont font =  QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->label->setFont(font);
    }
}

void custom::on_inputBt_clicked()
{
    //调用输入对话框类
    QString text = QInputDialog::getText(this,"输入你想插入的内容","请输入！"/*,QLineEdit::Password*/);

    qDebug()<<text;
    //将获取到的text显示label
    ui->label->setText(text);
}

void custom::on_selfBt_clicked()
{
    //自定义的步骤如下
    QDialog dialog;  //先创建框的对象
    dialog.setWindowTitle("清空");  //设置标题
    dialog.resize(200,100);                    //设置框的大小
    //添加组件 (先创建)
    QLabel warningLabel("确定清空？", &dialog);
    warningLabel.setGeometry(20, 20, 80, 20);
    QPushButton yesbt("Yes",&dialog);
    yesbt.setGeometry(30,60,60,30);
    QPushButton nobt("NO",&dialog);
    nobt.setGeometry(110,60,60,30);
    //创建信号与槽
    connect(&yesbt,&QPushButton::clicked,&dialog,&QDialog::accept);
    connect(&nobt,&QPushButton::clicked,&dialog,&QDialog::reject);
    //显示窗体
    int ret =  dialog.exec();
    if(ret == QDialog::Accepted)
    {
        ui->lineEdit->setText("");
        ui->label->setStyleSheet("background-color:rgba(255, 255, 255, 0)");
        ui->label->setText("");
        qDebug()<<"YES   YES";
    }
    if(ret == QDialog::Rejected)
    {
        qDebug()<<"NO   NO";
    }
}
