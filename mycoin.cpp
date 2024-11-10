#include "mycoin.h"
#include <QPixmap>
#include <QDebug>

MyCoin::MyCoin(QString img)
{
    QPixmap pix;
    bool ret=pix.load(img);
    if(!ret){
        QString str=QString("图片加载失败，失败的路径是%1!").arg(img);
        qDebug()<<str;
        return;
    }
    /*
     *不规则图标的设置
    */
    //设置按钮固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:Opx;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

    //创建定时器
    this->timer1=new QTimer(this);
    this->timer2=new QTimer(this);

    //监听金币翻银币的定时器
    connect(this->timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str1=QString(":/images/res/Coin000%1.png").arg(this->min++);
        bool ret=pix.load(str1);
        if(!ret){
            QString str1=QString("图片加载失败，失败的路径是%1!").arg(str1);
            qDebug()<<str1;
            return;
        }
        /*
     *不规则图标的设置
    */

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:Opx;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min>this->max){
            this->min=1;
            this->timer1->stop();
            this->isAnimation=false;
        }
    });

    //监听银币翻金币
    connect(this->timer2,&QTimer::timeout,[=](){
        QPixmap pix1;
        QString str2=QString(":/images/res/Coin000%1.png").arg(this->max--);
        bool ret1=pix1.load(str2);
        if(!ret1){
            QString str2=QString("图片加载失败，失败的路径是%1!").arg(str2);
            qDebug()<<str2;
            return;
        }

        /*
     *不规则图标的设置
    */

        this->setFixedSize(pix1.width(),pix1.height());
        this->setStyleSheet("QPushButton{border:Opx;}");
        this->setIcon(pix1);
        this->setIconSize(QSize(pix1.width(),pix1.height()));

        if(this->max<this->min){
            this->max=8;
            this->timer2->stop();
            this->isAnimation=false;
        }
    });
}

void MyCoin::changeFlag()
{
    if(this->flag){
        this->timer1->start(30);
        this->flag=false;
    }
    else{
        this->timer2->start(30);
        this->flag=true;
    }
    this->isAnimation=true;
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation|| this->isWin ){
        return;
    }
    else{
        QPushButton::mousePressEvent(e);
    }
}
