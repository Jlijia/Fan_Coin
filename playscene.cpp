#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QTimer>
#include <QLabel>
#include <mycoin.h>
#include <dataconfig.h>
#include <QPropertyAnimation>
#include <QSoundEffect>
playScene::playScene(int index)
{
    //音效准备
    QSoundEffect *BackSound=new QSoundEffect(this);
    BackSound->setSource(QUrl::fromLocalFile(":/images/res/BackButtonSound.wav"));

    QSoundEffect *FlipSound=new QSoundEffect(this);
    FlipSound->setSource(QUrl::fromLocalFile(":/images/res/ConFlipSound.wav"));

    QSoundEffect *WinSound=new QSoundEffect(this);
    WinSound->setSource(QUrl::fromLocalFile(":/images/res/LevelWinSound.wav"));

    this->levelIndex=index;
    qDebug()<<"您选择的是第"<<this->levelIndex<<"关";

    //设置窗口的尺寸
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("翻金币场景");
    //设置图标
    this->setWindowIcon(QIcon(":/images/res/Coin0001.png"));
    //创建菜单栏
    QMenuBar *bar=menuBar();
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
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
            //发送点击返回的信号
            BackSound->play();
            emit this->ChooseSceneBack();
        });

    });

    //显示当前的关卡号
    QLabel *label=new QLabel;
    label->setParent(this);
    QString str=QString("Level:%1").arg(this->levelIndex);
    label->setText(str);
    QFont font("华文新魏",20);
    font.setPointSize(20);
    font.setBold(true);
    label->setFont(font);
    //设置标签大小与位置
    label->setGeometry(QRect(30,this->height()-50,this->width(),50));
    //设置鼠标穿透的属性
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
    //设置胜利图片
    QLabel *winlabel=new QLabel;
    winlabel->setParent(this);
    QPixmap pix;
    pix.load(":/images/res/LevelCompletedDialogBg.png");
    winlabel->setPixmap(pix);
    winlabel->setGeometry(0,0,pix.width(),pix.height());
    winlabel->move(this->width()*0.5-pix.width()*0.5,-pix.height());

    //初始化关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }



    //创建金币背景图片
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QLabel *label=new QLabel;
            QPixmap pix;
            pix.load(":/images/res/BoardNode.png");
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*pix.width(),200+j*pix.height());


            //创建金币
            QString str;
            if(this->gameArray[i][j]==1){
                str=":/images/res/Coin0001.png";
            }
            else{
                str=":/images/res/Coin0008.png";
            }
            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*pix.width(),204+j*pix.height());
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];

            this->coinBtn[i][j]=coin;



            //点击金币 调用信号
            connect(coin,&MyCoin::clicked,[=](){
                FlipSound->play();
                //禁用其他金币按钮
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                        this->coinBtn[i][j]->isWin=true;
                    }
                }

                coin->changeFlag();
                gameArray[i][j]=gameArray[i][j]==0?1:0;

                //延时翻转金币
                QTimer::singleShot(300,this,[=](){
                    //开始翻转周围的硬币
                    //检测右侧硬币的翻转
                    FlipSound->play();
                    if(coin->posX+1<=3){
                        this->coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY]=gameArray[coin->posX+1][coin->posY]==0?1:0;
                    }
                    if(coin->posX-1>=0){
                        this->coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY]=gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }
                    if(coin->posY-1>=0){
                        this->coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1]=gameArray[coin->posX][coin->posY-1]==0?1:0;
                    }
                    if(coin->posY+1<=3){
                        this->coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1]=gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }


                    //金币翻转之后检测是否胜利
                    this->isWin=true;
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            if(this->coinBtn[i][j]->flag==false){
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin){
                        qDebug()<<"游戏胜利";
                        for(int i=0;i<4;i++){
                            for(int j=0;j<4;j++){
                                this->coinBtn[i][j]->isWin=true;

                                }
                            }
                            //将胜利的图片向下
                            QPropertyAnimation *animation=new QPropertyAnimation(winlabel,"geometry");
                            animation->setDuration(100);
                            animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                            animation->setEndValue(QRect(winlabel->x(),winlabel->y()+114,winlabel->width(),winlabel->height()));
                            animation->setEasingCurve(QEasingCurve::OutBounce);
                            animation->start(QAbstractAnimation::DeleteWhenStopped);
                            WinSound->play();
                        }
                    else{
                        for(int i=0;i<4;i++){
                            for(int j=0;j<4;j++){
                                this->coinBtn[i][j]->isWin=false;
                            }
                        }
                    }
                });
            });
        }
    }




}

void playScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //绘制背景
    QPixmap pix;
    pix.load(":/images/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //绘制标题
    pix.load(":/images/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
