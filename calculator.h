#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QPushButton>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QLineEdit>  //单行输入框

namespace Ui {
class calculator;
}

class calculator : public QDialog
{
    Q_OBJECT

public:
    explicit calculator(QWidget *parent = nullptr);
    ~calculator();

signals:
    void sendSignal();

private slots:
    //创建一个槽函数
    void back();
    void a();

private:
    Ui::calculator *ui;

    QLineEdit *lineEdit;
    QVBoxLayout *vbox;
    QGridLayout *grid;
    QPushButton *buttons;
    QPushButton *button;

    //设置第一次和第二次数据的保存
    QString fristnum;
    QString secondnum;

    //创建一个判断函数
    void InputNum(QString ch);
    void InputType(QString ch);
    void OntPut();


    //创建一个标志位(作用是判断是第一次输入还是第二次输入)
    int calc = 0;
};

#endif // CALCULATOR_H
