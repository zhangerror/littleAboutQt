#include "http_json.h"
#include "ui_http_json.h"
#include <QDir>

http_JSON::http_JSON(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::http_JSON)
{
    ui->setupUi(this);

    ui->backPushButton->setText("Exit");

    //qurl--》（解析构造编码）
    m_url = "http://wthrcdn.etouch.cn/weather_mini?city=成都";
    m_text = "";
    //创建请求
    QNetworkRequest request(m_url);
    //发射
    m_manager.get(request);

    //创建信号与槽  （关联请求完毕之后（会触发finsihed）返回的数据）
    connect(&m_manager,&QNetworkAccessManager::finished,this,&http_JSON::Read_data);
    //:/image/JSON.png
    this->setStyleSheet("QMainWindow{border-image:url(:/image/JSON.png);}"
                        "QLineEdit{font-size:17px;}"
                        "QPushButton{background-color:rgb(201, 220 , 69, 150);"
                                       "font-size:20px;"
                                       "border-radius:5px}"
                        "QLabel{background-color: rgba(201, 220 , 69, 100);"
                                "font-family:'黑体';"
                                "border:none;"
                                "font-size:20px;"
                                "}");

    ui->selectPushButton->setText("查看");
    ui->selectPushButton->setStyleSheet("background-color: rgba(201, 220 , 69, 100)");
    ui->selectPushButton->setFixedSize(80, 40);
}

http_JSON::~http_JSON()
{
    delete ui;
}

void http_JSON::Read_data(QNetworkReply *app)
{
    //对数据进行读取
    QByteArray array = app->readAll();
    //判断是否为json数据
    QJsonParseError error;
    //对json数据进解析
    QJsonDocument doc  = QJsonDocument::fromJson(array,&error);

    if(error.error != QJsonParseError::NoError)
    {
        qDebug()<<"数据有误";
        return;
    }

    //一层一层解剖
    QJsonObject obj = doc.object();

    //t0
    QJsonObject data_obj = obj.value("data").toObject();
    QJsonObject yesterday_obj = data_obj.value("yesterday").toObject();
    ui->t0DateLabel->setText(yesterday_obj.value("date").toString());
    ui->t0TypeLabel->setText(yesterday_obj.value("type").toString());
    ui->t0HTempLabel->setText(yesterday_obj.value("high").toString());
    ui->t0LTempLabel->setText(yesterday_obj.value("low").toString());
    ui->t0WindDLabel->setText(yesterday_obj.value("fx").toString());
    ui->t0WindSLabel->setText(yesterday_obj.value("fl").toString().mid(9, 2));

    QJsonArray data_array = data_obj.value("forecast").toArray();
    QJsonObject today_obj = data_array.at(0).toObject();
    ui->todayDateLabel->setText(today_obj.value("date").toString());
    ui->todayTypeLabel->setText(today_obj.value("type").toString());
    ui->todayHTempLabel->setText(today_obj.value("high").toString());
    ui->todayLTempLabel->setText(today_obj.value("low").toString());
    ui->todayWindDLabel->setText(today_obj.value("fengxiang").toString());
    ui->todayWindSLabel->setText(today_obj.value("fengli").toString().mid(9, 2));

    QJsonObject t1_obj = data_array.at(1).toObject();
    ui->t1DateLabel->setText(t1_obj.value("date").toString());
    ui->t1TypeLabel->setText(t1_obj.value("type").toString());
    ui->t1HTempLabel->setText(t1_obj.value("high").toString());
    ui->t1LTempLabel->setText(t1_obj.value("low").toString());
    ui->t1WindDLabel->setText(t1_obj.value("fengxiang").toString());
    ui->t1WindSLabel->setText(t1_obj.value("fengli").toString().mid(9, 2));

    QJsonObject t2_obj = data_array.at(2).toObject();
    ui->t2DateLabel->setText(t2_obj.value("date").toString());
    ui->t2TypeLabel->setText(t2_obj.value("type").toString());
    ui->t2HTempLabel->setText(t2_obj.value("high").toString());
    ui->t2LTempLabel->setText(t2_obj.value("low").toString());
    ui->t2WindDLabel->setText(t2_obj.value("fengxiang").toString());
    ui->t2WindSLabel->setText(t2_obj.value("fengli").toString().mid(9, 2));

    QJsonObject t3_obj = data_array.at(3).toObject();
    ui->t3DateLabel->setText(t3_obj.value("date").toString());
    ui->t3TypeLabel->setText(t3_obj.value("type").toString());
    ui->t3HTempLabel->setText(t3_obj.value("high").toString());
    ui->t3LTempLabel->setText(t3_obj.value("low").toString());
    ui->t3WindDLabel->setText(t3_obj.value("fengxiang").toString());
    ui->t3WindSLabel->setText(t3_obj.value("fengli").toString().mid(9, 2));

    QJsonObject t4_obj = data_array.at(4).toObject();
    ui->t4DateLabel->setText(t4_obj.value("date").toString());
    ui->t4TypeLabel->setText(t4_obj.value("type").toString());
    ui->t4HTempLabel->setText(t4_obj.value("high").toString());
    ui->t4LTempLabel->setText(t4_obj.value("low").toString());
    ui->t4WindDLabel->setText(t4_obj.value("fengxiang").toString());
    ui->t4WindSLabel->setText(t4_obj.value("fengli").toString().mid(9, 2));

    qApp->processEvents();

    QDir::setCurrent(QString("/home/lpenguin/qt/xunfei/bin"));

    if(m_text == "") {
        qApp->processEvents();
        m_text = data_obj.value("ganmao").toString();
        QString cmd = "./tts_offline_sample " + m_text;
        system(cmd.toUtf8());
        system("aplay tts_sample.wav");
    }
}

void http_JSON::on_backPushButton_clicked()
{
    emit sendSignal();
    this->hide();
}

void http_JSON::on_selectPushButton_clicked()
{
    //qurl--》（解析构造编码）
    m_url = "http://wthrcdn.etouch.cn/weather_mini?city=";
    m_url += ui->cityLineEdit->text();
    //创建请求
    QNetworkRequest request(m_url);
    m_manager.get(request);
}
