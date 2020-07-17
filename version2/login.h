#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QPainter>
#include <QMessageBox>
#include "mainform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

protected:
    void paintEvent(QPaintEvent* );

private slots:
    void reshow();
    void on_loginPushButton_clicked();

private:
    Ui::login *ui;
};
#endif // LOGIN_H
