#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include "calculator.h"
#include "custom.h"
#include "http_json.h"

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

private:
    Ui::mainForm *ui;

    QPushButton *vbutton[6];
};

#endif // MAINFORM_H
