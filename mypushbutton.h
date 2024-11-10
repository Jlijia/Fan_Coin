#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //参数1 正常显示图片路径 参数2 按下后切换图片路径
    MyPushButton(QString normally,QString pressImg="");

public:
    void zoom1();//向上
    void zoom2();//向下
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public:
    QString normalPath;
    QString pressPath;

signals:
};

#endif // MYPUSHBUTTON_H
