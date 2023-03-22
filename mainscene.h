#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <chooselevelscene.h>

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();

    //重写painterEvent事件  绘制背景图片
    void paintEvent(QPaintEvent *event);

    ChooseLevelScene *chooseScene = NULL;

private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
