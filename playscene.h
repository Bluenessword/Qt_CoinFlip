#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <mycoin.h>
#include <QLabel>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);

    int levelIndex;//记录所选关卡

    //重写paintEvent事件
    void paintEvent(QPaintEvent *event);

    int gameArray[4][4]; //记录每个关卡的金币数据
    MyCoin *coinBtn[4][4];
    //胜利标志
    bool isWin;
    //胜利图片弹跳特效
    void zoom(QLabel *winLabel);
    //保证动画只显示一次
    int over = 1;

signals:
    void playSceneback();//返回按钮触发事件

public slots:
};

#endif // PLAYSCENE_H
