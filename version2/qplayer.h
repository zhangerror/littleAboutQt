#ifndef QPLAYER_H
#define QPLAYER_H

#include <QMainWindow>
#include  <QProcess>
#include <QFileDialog>

#include <QListWidget>
#include <QDebug>

namespace Ui {
class QPlayer;
}

class QPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit QPlayer(QWidget *parent = nullptr);
    ~QPlayer();
    void play_next(int num);

signals:
    void sendSignal();

private slots:
    void on_backPushButton_clicked();

    void on_openPushButton_clicked();

    void on_closePushButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    QProcess mprocess;
    Ui::QPlayer *ui;

};

#endif // QPLAYER_H
