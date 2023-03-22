#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImage, QString pressImage)
{
    this->normalImagePath = normalImage;
    this->pressImagePath = pressImage;

    QPixmap pix;
    bool ret = pix.load(normalImage); //默认显示normalImage图片
    if(!ret)
    {
        qDebug() << "图片加载失败";
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

}

//弹跳动画
void MyPushButton::zoom(int a, int b)
{
    //创建动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    //设置动画间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(), this->y()+a, this->width(), this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(), this->y()+b, this->width(), this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();

}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImagePath != "") // 传入的按下图片不为空 说明需要有按下状态 切换成按下的图片
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImagePath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
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
    }

    //其他的交给父类
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImagePath != "")// 传入的按下图片不为空 说明需要有按下状态 释放后切换成初始的图片
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImagePath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
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
    }

    //其他的交给父类
    return QPushButton::mouseReleaseEvent(e);
}

