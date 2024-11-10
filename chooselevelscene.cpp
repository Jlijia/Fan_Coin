#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <playscene.h>
#include <QSoundEffect>
ChooseLevelscene::ChooseLevelscene(QWidget *parent)
    : QMainWindow{parent}
{
    //设置音效
    QSoundEffect * ChooseSound = new QSoundEffect(this);
    ChooseSound->setSource(QUrl::fromLocalFile(":/images/res/TapButtonSound.wav"));

    QSoundEffect *BackSound=new QSoundEffect(this);
    BackSound->setSource((QUrl::fromLocalFile(":/images/res/BackButtonSound.wav")));

    //设置固定的尺寸
    this->setFixedSize(320,588);

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //设置图标
    this->setWindowIcon(QIcon(":/images/res/Coin0001.png"));

    //创建菜单栏
    QMenuBar *bar=menuBar();
    this->setMenuBar(bar);
    //创建菜单
    QMenu *startMenu=bar->addMenu("开始");
    //创建菜单项
    QAction *quitAction=startMenu->addAction("退出");
    //监听退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //设置返回按钮
    MyPushButton *backBtn=new MyPushButton(":/images/res/BackButton.png",":/images/res/BackButtonSelected.png");

    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&MyPushButton::clicked,[=](){
        //延时发送信号
        QTimer::singleShot(500,this,[=](){
            BackSound->play();
            //发送点击返回的信号
            emit ChooseSceneBack();
        });

    });

    pScene=NULL;

    //创建20个具体的关卡按钮
    for(int i=0;i<20;i++){
        MyPushButton *menuBtn=new MyPushButton(":/images/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,130+(i/4)*70);
        connect(menuBtn,&MyPushButton::clicked,[=](){
            ChooseSound->play();
            this->pScene=new playScene(i+1);
            this->pScene->setGeometry(this->geometry());
            this->pScene->show();
            this->hide();

            //在哪里创建就在哪里监听
            connect(this->pScene,&playScene::ChooseSceneBack,[=](){
                this->setGeometry(this->pScene->geometry());
                this->show();
                this->pScene->hide();

                //删除指针，即翻金币场景
                delete this->pScene;
                this->pScene=NULL;
            });
        });

        //显示上面的数字
        QLabel *label=new QLabel;
        label->setParent(this);
        label->move(25+(i%4)*70,130+(i/4)*70);
        //设置尺寸
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        //设置文本
        label->setText(QString::number(i+1));
        //设置对齐方式
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置鼠标穿透的属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelscene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix;

    pix.load(":/images/res/OtherSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/images/res/Title.png");

    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix);

}
