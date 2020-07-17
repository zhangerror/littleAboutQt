#include "calculator.h"
#include "ui_calculator.h"

calculator::calculator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calculator)
{
    ui->setupUi(this);

    this->setFixedSize(520, 743);
    this->setWindowTitle("简易计算器");
    this->setStyleSheet("QDialog{border-image: url(:/image/calculator.jpg);}"
                        "QPushButton{background-color: rgba(201, 220 , 69, 100);"
                                                    "font-family:'黑体';"
                                                    "border:none;"
                                                    "font-size:40px;"
                                                    "}"
                        "border-radius:5px}");
    //创建垂直布局
    this->vbox = new QVBoxLayout(this);
    //创建单行输入框对象
    this->lineEdit = new QLineEdit();
    //设置一下单行输入框的属性
    this->lineEdit->setMinimumHeight(60);
    //设置单行输入框显示方向  (右边显示)
    this->lineEdit->setAlignment(Qt::AlignRight);
    this->lineEdit->setStyleSheet("font-size:30px;");

    //把标签插入到垂直布局里面
    this->vbox->addWidget(lineEdit);


    //创建栅栏布局
    this->grid = new QGridLayout();
    //创建按钮对象
    this->buttons = new QPushButton[16];
    //创建一个字符串
    QString sty = "789/456*123-=0.+";
    //把按钮加入到栅栏布局里面
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
           //设置按钮大小
            buttons[i*4+j].setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            grid->addWidget(buttons+i*4+j,i,j);

            //设置按钮数字键
            buttons[i*4+j].setText(sty.at(i*4+j));
            //创建每一个按钮信号和槽
            connect(buttons+i*4+j,&QPushButton::clicked,this,&calculator::back);

        }

    }
    //把栅栏布局插入到垂直布局
    this->vbox->addLayout(grid);
    //创建返回按钮
    this->button = new QPushButton("返回上界面");
    //把返回按钮插入到垂直布局
    this->vbox->addWidget(button);
    this->button->setStyleSheet("font-size:20px;");

    connect(button,&QPushButton::clicked,this,&calculator::a);
}

calculator::~calculator()
{
    delete ui;
    delete vbox;
    delete []this->buttons;
    delete grid;
    delete lineEdit;
    delete button;
}

void calculator::back() {
    //获取信号的发送者
    QPushButton *bt = static_cast<QPushButton *>(sender());
    //获取按钮信息
    QString ch = bt->text();
    //对获取的数据进行判断
    if(QString("0123456789.").indexOf(ch) >= 0)
    {
        qDebug()<<"输入的数字是："<<ch;
        InputNum(ch);
    }
    else if(QString("+-/*").indexOf(ch) >=0)
    {
        qDebug()<<"输入的符号是："<<ch;
        InputType(ch);
    }
    else
    {
        qDebug()<<"输入的数字是："<<ch;
        OntPut();
    }
}

void calculator::a()
{
    emit sendSignal();
    this->hide();
}

//对数字进行处理
void calculator::InputNum(QString ch)
{
    //标志位
    if(calc == 0)
    {
      //  设置字符追加  (第一次输入的数)
       fristnum.append(ch);
     //打印一下数据
        qDebug()<<fristnum;
        //显示一下输入的字符串
       lineEdit->setText(fristnum);


    }
    else
    {
        //（第二次输入的数）
        secondnum.append(ch);
        qDebug()<<secondnum;
         //显示一下输入的字符串
         lineEdit->setText(secondnum);

    }
}
//对符号的处理
void calculator::InputType(QString ch)
{
    //队符号进行判断
    switch (ch.at(0).toLatin1())
    {
    case '+':  calc=1; break;
    case '-':  calc=2; break;
    case '*':  calc=3; break;
    case '/':  calc=4; break;

    default:break;
    }
}
//等于号操作
void calculator::OntPut()
{
    QString srt;
    //先对calc进行判断
    switch (calc)
    {
    case 1 : srt=QString(fristnum+"+"+secondnum+"="+QString::number(fristnum.toDouble()+secondnum.toDouble())); break;
    case 2 : srt=QString(fristnum+"-"+secondnum+"="+QString::number(fristnum.toDouble()-secondnum.toDouble())); break;
    case 3 : srt=QString(fristnum+"*"+secondnum+"="+QString::number(fristnum.toDouble()*secondnum.toDouble())); break;
    case 4 :
        if(secondnum.toDouble() == 0) {
            srt = QString("非法输入：除数不能为零!");
            calc = 0;
            fristnum.clear();
            secondnum.clear();
        }
        else {
            srt=QString(fristnum+"/"+secondnum+"="+QString::number(fristnum.toDouble()/secondnum.toDouble()));
        }
        break;
    default:break;
    }

    qDebug()<<srt;
    //显示在单行输入框
    lineEdit->setText(srt);
    //把calc变回0
    calc = 0;
    //清空保存的上一次数据的字符串
    fristnum.clear();
    secondnum.clear();
}
