#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(380, 588);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");
    //创建菜单栏
    QMenuBar *bar = new QMenuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");
    //创建退出菜单项
    QAction *quitAction = startMenu->addAction("退出");
    //退出
    connect(quitAction,&QAction::triggered, this, [=](){
       this->close();
    });

    //按钮音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav", this);
    QSound *backSound = new QSound(":/res/BackButtonSound.wav", this);

    //返回按钮
    MyPushButton *backbutton = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backbutton->setParent(this);
    backbutton->move(this->width() - backbutton->width(), this->height() - backbutton->height());

    connect(backbutton, &MyPushButton::clicked, this, [=](){
        //播放返回按钮音效
        backSound->play();
        qDebug() << "按下了返回键";
        //告诉主场景 我返回了 主场景需监听chooseLevelScene的返回按钮
        emit this->chooseSceneBack();
    });

    //创建选择关卡的按钮
    for(int i = 0;i < 20; i++)
    {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(60 + i % 4 * 70, 160 + i / 4 * 70);

        //监听每个按钮的点击事件
        connect(menuBtn, &MyPushButton::clicked, this, [=](){
            //播放选择按钮音效
            chooseSound->play();
           QString str = QString("你选择的是第 %1 关").arg(i+1);
           qDebug() << str;
           //进入游戏场景
           this->hide();
           play = new PlayScene(i+1);
           //设置play场景位置
           play->setGeometry(this->geometry());
           play->show();

           connect(play, &PlayScene::playSceneback, this, [=](){
               //延时切换场景
               QTimer::singleShot(200,this,[=](){
                   this->setGeometry(play->geometry());
                   //进入关卡选择场景 并删除游戏界面
                   this->show();
                   delete play;
                   play = NULL;
               });
           });

        });

        QLabel *label = new QLabel(menuBtn);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setFont(QFont("Microsoft YaHei", 15, 60));
        label->setText(QString::number(i + 1));
        label->setAlignment(Qt::AlignCenter);

        //若label不设置父类为btn 则label会把btn挡住按钮无法摁下
        //设置让鼠标穿透 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }


}

//绘制背景图片
void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width())*0.5 -25, 30, pix.width()*1.2, pix.height()*1.2, pix);

}
