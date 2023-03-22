#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);

    //传入金币或者银币路径
    MyCoin(QString btnImage);

    //金币的位置属性
    int posx;
    int posy;
    bool flag; //1为正 0为反

    //改变金币状态
    void changeFlag();
    QTimer *timer1;//正面翻方面
    QTimer *timer2;//方面翻正面
    int min = 1;
    int max = 8;
    //执行动画的标志
    bool isAnimation = false;
    //游戏胜利
    bool isWin = false;

signals:

public slots:
};

#endif // MYCOIN_H
