#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelscene(QWidget *parent = nullptr);


    //绘图事件
    void paintEvent(QPaintEvent*);

    //维护第三个场景的指针
    playScene *pScene;
signals:
    //点击返回按钮的自定义信号
    void ChooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
