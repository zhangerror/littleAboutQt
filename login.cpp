#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    this->setWindowTitle("登录");
    this->setFixedSize(650, 550);
    this->setStyleSheet("QMainWindow{border-image: url(:/image/login.jpg);}");

    ui->IDLineEdit->setGeometry(QRect(QPoint(140,250), QPoint(510, 290)));
    ui->IDLineEdit->setStyleSheet("background-color:rgb(255, 255 , 255, 200);"
                                   "font-size:20px;"
                                   "border-radius:5px");

    ui->passwdLineEdit->setGeometry(QRect(QPoint(140,300), QPoint(510, 340)));
    ui->passwdLineEdit->setStyleSheet("background-color:rgb(255, 255 , 255, 200);"
                                      "font-size:10px;"
                                      "border-radius:5px");
    ui->passwdLineEdit->setEchoMode(QLineEdit::Password);

    ui->loginPushButton->setGeometry(QRect(QPoint(140,380), QPoint(510, 420)));
    ui->loginPushButton->setStyleSheet("background-color:rgb(201, 220 , 69, 150);"
                                       "font-size:20px;"
                                       "border-radius:5px");
    ui->loginPushButton->setText("登录");
}

login::~login()
{
    delete ui;
}

void login::paintEvent(QPaintEvent *) {
    QPainter painter;
    painter.begin(this);
    painter.setPen(QPen(QColor(201, 220 , 69, 90)));
    painter.setBrush(QBrush(QColor(201, 220 , 69, 90)));
    painter.drawRect(0, 200, 650, 550);
    painter.end();
}

void login::on_loginPushButton_clicked()
{
    if(ui->IDLineEdit->text()=="zhang" && ui->passwdLineEdit->text()=="123456") {
        ui->IDLineEdit->setText("");
        ui->passwdLineEdit->setText("");
        mainForm* mainW = new mainForm(this);
        this->hide();
        mainW->show();
    }
    else {
        QMessageBox::information(this, "Error Message", QString("非法用户：帐号或密码错误!"));
        ui->passwdLineEdit->setText("");
    }
}
