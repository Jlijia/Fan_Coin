#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString img);

    int posX;
    int posY;
    bool flag;//正反的标志

    //改变标志，执行翻转效果
    void changeFlag();

    //正翻反定时器
    QTimer *timer1;
    //反翻正定时器
    QTimer *timer2;
    //最小图片
    int min=1;
    //最大图片；
    int max=8;
    //禁用标志
    bool isAnimation=false;
    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    //判断游戏胜利禁用按钮
    bool isWin=false;
signals:
};

#endif // MYCOIN_H
