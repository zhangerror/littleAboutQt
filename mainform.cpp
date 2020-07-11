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

    ui->backPushButton->setGeometry(QRect(QPoint(140,500), QPoint(510, 540)));
    ui->backPushButton->setStyleSheet("background-color:rgb(201, 220 , 69, 150);"
                                      "font-size:20px;"
                                      "border-radius:5px");
    ui->backPushButton->setText("退出登录");
}

mainForm::~mainForm()
{
    delete ui;
}

void mainForm::on_backPushButton_clicked()
{
    this->parentWidget()->show();
    delete this;
}

void mainForm::on_calculatorPushButton_clicked()
{
    calculator* new_cal = new calculator();
    connect(new_cal, SIGNAL(sendSignal()), this, SLOT(reshow()));
    this->hide();
    new_cal->show();
}

void mainForm::reshow() {
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
