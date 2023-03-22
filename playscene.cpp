#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QLabel>
#include <mycoin.h>
#include <dataconfig.h>
#include <QTimer>
#include <QPropertyAnimation>
#include <QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入到了第%1关").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    //初始化场景
    //设置固定大小
    this->setFixedSize(380, 588);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("游戏场景");
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
    QSound *backSound = new QSound(":/res/BackButtonSound.wav", this);
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav", this);
    QSound *winSound = new QSound(":/res/LevelWinSound.wav", this);

    //返回按钮
    MyPushButton *backbutton = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backbutton->setParent(this);
    backbutton->move(this->width() - backbutton->width(), this->height() - backbutton->height());

    connect(backbutton, &MyPushButton::clicked, this, [=](){
        backSound->play();
        qDebug() << "翻金币的场景中，按下了返回键";
        //告诉关卡选择场景 我返回了 关卡场景需监听playScene的返回按钮
        emit this->playSceneback();
    });

    //显示当前关卡数
    QString level = QString("Level:%1").arg(this->levelIndex);
    QLabel *label = new QLabel(level, this);
    label->setGeometry(30, this->height()-50, 125, 50);
    label->setFont(QFont("微软雅黑", 19, 60));

    //初始化关卡的二维数组
    dataConfig config;
    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //初始化胜利图片
    QLabel *winLabel = new QLabel(this);
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->move((this->width() - tmpPix.width())*0.5, -tmpPix.height());

    //显示金币背景图
    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            //绘制金币背景图片
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel *label = new QLabel(this);
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->move(90 + i * pix.width(),200 + j * pix.height());

            //创建金币
            QString path;
            if(this->gameArray[i][j] == 1)
            {
                path = ":/res/Coin0001.png";
            }
            else
            {
                path = ":/res/Coin0008.png";
            }
            MyCoin *coin = new MyCoin(path);
            coin->setParent(label);
            coin->move(2, 4);
            //给金币赋属性
            coin->posx = i;
            coin->posy = j;
            coin->flag = this->gameArray[i][j];

            //将金币放入到金币的二维数组中 以便后期的维护
            coinBtn[i][j] = coin;

            //点击金币进行翻转
            connect(coin,&MyCoin::clicked,this,[=](){
                flipSound->play();
                coin->changeFlag();
                this->gameArray[i][j] = !(this->gameArray[i][j]);
                //延时翻转
                QTimer::singleShot(100,this,[=](){
                    //翻转周围金币
                    if(coin->posx + 1 < 4)//右侧金币翻转条件
                    {
                        coinBtn[coin->posx + 1][coin->posy]->changeFlag();
                        this->gameArray[coin->posx + 1][coin->posy] = !(this->gameArray[coin->posx + 1][coin->posy]);
                    }
                    if(coin->posx - 1 >= 0)//左侧金币翻转条件
                    {
                        coinBtn[coin->posx - 1][coin->posy]->changeFlag();
                        this->gameArray[coin->posx - 1][coin->posy] = !(this->gameArray[coin->posx - 1][coin->posy]);
                    }
                    if(coin->posy - 1 >= 0)//上侧金币翻转条件
                    {
                        coinBtn[coin->posx][coin->posy - 1]->changeFlag();
                        this->gameArray[coin->posx][coin->posy - 1] = !(this->gameArray[coin->posx][coin->posy - 1]);
                    }
                    if(coin->posy + 1 < 4)//下侧金币翻转条件
                    {
                        coinBtn[coin->posx][coin->posy + 1]->changeFlag();
                        this->gameArray[coin->posx][coin->posy + 1] = !(this->gameArray[coin->posx][coin->posy + 1]);
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i = 0;i < 4;i++)
                    {
                        for(int j = 0;j < 4;j++)
                        {
                            if(coinBtn[i][j]->flag == false)//只要有一个是反面 就算失败
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true)
                    {
                        //禁用所有金币动画
                        for(int i = 0;i < 4;i++)
                        {
                            for(int j = 0;j < 4;j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }
                        //保证动画只显示一次
                        if(this->over)
                        {
                            qDebug() << "游戏胜利";
                            this->zoom(winLabel);
                            winSound->play();
                            this->over -=1;
                        }
                    }
                });

            });
        }
    }


}

//绘制背景
void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.6, pix.height()*0.6);
    painter.drawPixmap(10, 30, pix);
}

void PlayScene::zoom(QLabel *winLabel)
{
    //将胜利的图片砸下来
    QPropertyAnimation *animation = new QPropertyAnimation(winLabel, "geometry");
    //设置时间间隔
    animation->setDuration(1000);
    //设置开始位置
    animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
    //设置结束位置
    animation->setEndValue(QRect(winLabel->x(), winLabel->y()+144, winLabel->width(), winLabel->height()));
    //设置缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //开始动画
    animation->start();
}
