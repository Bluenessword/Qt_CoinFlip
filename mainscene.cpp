#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QSound>//多媒体音效

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置主场景

    //设置固定大小
    setFixedSize(380, 588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币");
    //退出
    connect(ui->actionquit, &QAction::triggered, this, [=](){
        this->close();
    });

    //初始化开始按钮音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav", this);
    //startSound->setLoops(-1);//-1为无限循环

    //开始按钮
    MyPushButton *startbutton = new MyPushButton(":/res/MenuSceneStartButton.png");
    startbutton->setParent(this);
    startbutton->move((this->width() - startbutton->width()) * 0.5, this->height() * 0.7);

    //实例化关卡选择场景
    chooseScene = new ChooseLevelScene;

    connect(startbutton, &MyPushButton::clicked, this, [=](){
        qDebug() << "按钮按下了";
        //播放开始按钮音效
        startSound->play();
        //显示特效
        startbutton->zoom(0, 10);
        startbutton->zoom(10, 0);

        //这里QTimer的函数是异步进行的
        //延时切换场景
        QTimer::singleShot(200,this,[=](){
            //设置chooseScene的位置
            chooseScene->setGeometry(this->geometry());
            //进入关卡场景 并隐藏主界面
            this->hide();
            chooseScene->show();
        });
    });

    //监听选择关卡的返回按钮的信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=](){
        //延时切换场景
        QTimer::singleShot(200,this,[=](){
            this->setGeometry(chooseScene->geometry());
            //隐藏关卡选择场景 显示主界面
            chooseScene->hide();
            this->show();
        });
    });
}

MainScene::~MainScene()
{
    delete ui;
}

//绘制背景
void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    //画背景
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景图片
    pix.load(":/res/Title.png");
    //缩放
    pix = pix.scaled(pix.width() * 0.6, pix.height() * 0.6);
    painter.drawPixmap(10,30,pix);


}
