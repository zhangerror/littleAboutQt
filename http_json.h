#ifndef HTTP_JSON_H
#define HTTP_JSON_H

#include <QMainWindow>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QString>
#include <QByteArray>//数组
#include <QJsonDocument> //文件
#include <QJsonObject>   //对象
#include <QJsonArray>   //数组
#include <QJsonValue>   //值
#include <QJsonParseError>//判断是否为JSON格式

namespace Ui {
class http_JSON;
}

class http_JSON : public QMainWindow
{
    Q_OBJECT

public:
    explicit http_JSON(QWidget *parent = nullptr);
    ~http_JSON();

signals:
    void sendSignal();

private slots:
    //创建一个接收服务器返回的数据
    void Read_data(QNetworkReply *app);

    void on_backPushButton_clicked();

    void on_selectPushButton_clicked();

private:
    Ui::http_JSON *ui;
    //创建管理类对象
    QNetworkAccessManager m_manager;
    QString m_url;
};

#endif // HTTP_JSON_H
