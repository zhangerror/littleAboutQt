#ifndef CUSTOM_H
#define CUSTOM_H

#include <QMainWindow>

#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QDebug>
#include <QString>
#include <QDialog>
#include <QPushButton>

namespace Ui {
class custom;
}

class custom : public QMainWindow
{
    Q_OBJECT

public:
    explicit custom(QWidget *parent = nullptr);
    ~custom();

signals:
    void sendSignal();

private slots:
    void back();
    void on_boxBt_clicked();

    void on_fileBt_clicked();

    void on_colorBt_clicked();

    void on_fontBt_clicked();

    void on_inputBt_clicked();

    void on_selfBt_clicked();

private:
    Ui::custom *ui;
};

#endif // CUSTOM_H
