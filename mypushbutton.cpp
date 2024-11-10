#include "mypushbutton.h"
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normally,QString pressImg)
{
    this->normalPath=normally;
    this->pressPath=pressImg;

    //创建QPixmap对象
    QPixmap pix;
    bool ret=pix.load(this->normalPath);
    if(!ret){
        QString str=QString("图片加载失败，失败的路径是：%1!").arg(this->normalPath);
    }

    //设置按钮固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:Opx;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");

    //设置动画间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");

    //设置动画间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //按下的路径不为空，说明要切换图片
    if(this->pressPath!=""){
        //创建QPixmap对象
        QPixmap pix;
        bool ret=pix.load(this->pressPath);
        if(!ret){
            QString str=QString("图片加载失败，失败的路径是：%1!").arg(this->pressPath);
        }

        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:Opx;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他的交给父类进行处理
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //按下的路径不为空，说明要还原正常显示的图片
    if(this->pressPath!=""){
        //创建QPixmap对象
        QPixmap pix;
        bool ret=pix.load(this->normalPath);
        if(!ret){
            QString str=QString("图片加载失败，失败的路径是：%1!").arg(this->pressPath);
        }

        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:Opx;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他的交给父类进行处理
    QPushButton::mouseReleaseEvent(e);
}
