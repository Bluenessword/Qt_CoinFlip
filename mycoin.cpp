#include "mycoin.h"
#include <QDebug>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString btnImage)
{
    QPixmap pix;
    bool ret = pix.load(btnImage);
    if(!ret)
    {
        QString str = QString("图片%1加载失败").arg(btnImage);
        qDebug() << str;
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(), pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));

    //初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //正面翻反面
    connect(timer1, &QTimer::timeout, this, [=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
        //判断如果翻完了 将min重置为1
        if(this->min > this->max)
        {
            this->min = 1;
            this->isAnimation = false;
            timer1->stop();
        }
    });

    //反面翻正面
    connect(timer2, &QTimer::timeout, this, [=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
        //判断如果翻完了 将min重置为1
        if(this->min > this->max)
        {
            this->max = 8;
            this->isAnimation = false;
            timer2->stop();
        }
    });

}

//改变正反面
void MyCoin::changeFlag()
{
    if(this->isAnimation || this->isWin)
        return;
    if(this->flag)
    {
        timer1->start(30);
        this->isAnimation = true;//开始做动画
        this->flag = false;
    }
    else
    {
        timer2->start(30);
        this->isAnimation = true;//开始做动画
        this->flag = true;
    }
}
