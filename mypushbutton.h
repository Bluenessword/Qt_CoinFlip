#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    //构造函数  参数一 正常显示的图片  参数二 按下现实的图片
    MyPushButton(QString normalImage, QString pressImage = "");
    //成员属性 保存用户传入的默认显示路径 以及按下后的显示图片路径
    QString normalImagePath;
    QString pressImagePath;

    void zoom(int a, int b);//弹跳特效

    //重写按下和释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
