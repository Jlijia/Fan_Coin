#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
class playScene : public QMainWindow
{
    Q_OBJECT
public:
    playScene(int index);//有参构造，参数代表当前关卡号

    int levelIndex;//成员属性 记录当前关卡号

    //绘图事件
    void paintEvent(QPaintEvent *);

    //二维数组数据 作用：初始化关卡
    int gameArray[4][4];

    //金币按钮数据
    MyCoin *coinBtn[4][4];

    //判断游戏胜利
    bool isWin=true;

signals:
    //点击返回按钮的自定义信号
    void ChooseSceneBack();
};

#endif // PLAYSCENE_H
