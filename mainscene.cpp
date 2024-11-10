#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QSoundEffect>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //准备音效
    QSoundEffect * startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/images/res/TapButtonSound.wav"));

    //点击退出菜单栏，实现退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //设置固定的尺寸
    this->setFixedSize(320,588);

    //设置标题
    this->setWindowTitle("翻金币主场景");

    //设置图标
    this->setWindowIcon(QIcon(":/images/res/Coin0001.png"));

    //创建第二个选关场景
    this->chooseScene=new ChooseLevelscene;

    //设置开始按钮
    MyPushButton *startBtn=new MyPushButton(":/images/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    connect(startBtn,&MyPushButton::clicked,[=](){
        // qDebug()<<"进入选关场景";
        startBtn->zoom1();
        startBtn->zoom2();
        startSound->play();

        QTimer::singleShot(500,this,[=](){
            this->chooseScene->setGeometry(this->geometry());
            this->chooseScene->show();//选关场景显示
            this->hide();//自身隐藏
        });
    });

    connect(this->chooseScene,&ChooseLevelscene::ChooseSceneBack,[=](){
        this->setGeometry(this->chooseScene->geometry());
        this->show();
        this->chooseScene->hide();
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家对象
    QPainter painter(this);

    //创建QPIXmap对象
    QPixmap pix;

    pix.load(":/images/res/PlayLevelSceneBg.png");

    //绘制背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题资源
    pix.load(":/images/res/Title.png");

    //缩放图片
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);

    painter.drawPixmap(10,30,pix);

}
