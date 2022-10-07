#include "DlgPlaying.h"
#include "ui_DlgPlaying.h"

#include <QImage>
#include <QFileDialog>          //文件
#include <QLabel>               //标签
#include <QMessageBox>          //信息框
#include <QMouseEvent>          //鼠标点击事件
#include <windows.h>            //sleep

const int g_iRank = 3;

DlgPlaying::DlgPlaying(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgPlaying)
    , _strPos(":/img/tup.jpg")
    , _bStart(false)
    , _iStep(0)
{
    ui->setupUi(this);

    init();

    connect(this, SIGNAL(sig_restart()), this, SLOT(on_btnRestart_clicked()));
    connect(this, SIGNAL(sig_back()), this, SLOT(on_btnBack_clicked()));
}

DlgPlaying::~DlgPlaying()
{
    delete ui;
}

//开始游戏
void DlgPlaying::start()
{
    _bStart = 1;      //标记为开始游戏
    _iStep = 0;
    ui->lcdStep->display("0");
    DlgPlaying::upset();
    DlgPlaying::showpicture();
}

void DlgPlaying::mousePressEvent(QMouseEvent *event)
{
    //鼠标点击事件（https://www.cnblogs.com/aiguona/p/9999507.html）
    // 如果是鼠标左键按下
    if(event->button() == Qt::LeftButton)
    {
        if(!_bStart)
        {
            QMessageBox::information(NULL, "提示", "请先点击开始游戏按钮");
            return ;
        }

        if (ui->label_1->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            //0 0
            move(0, 0);
        }
        else if (ui->label_2->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            //1 0
            move(1, 0);
        }
        else if (ui->label_3->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            //2 0
            move(2, 0);
        }
        else if (ui->label_4->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            //0 1
            move(0, 1);
        }
        else if (ui->label_5->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            // 1 1
            move(1, 1);
        }
        else if (ui->label_6->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            // 2 1
            move(2, 1);
        }
        else if (ui->label_7->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            // 0 2
            move(0, 2);
        }
        else if (ui->label_8->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            // 1 2
            move(1, 2);
        }
        else if (ui->label_9->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            // 2 2
            move(2, 2);
        }

        showpicture();
        _iStep++;
        ui->lcdStep->display(QString::number(_iStep));

        if (bSuccessful())
        {
            QApplication::setQuitOnLastWindowClosed(false);
            QMessageBox:: StandardButton result = QMessageBox::information(NULL, " ", "游戏胜利!", QMessageBox::Yes|QMessageBox::No);
            if (result == QMessageBox::Yes)
            {
                emit sig_restart();

            }
            else
            {
                emit sig_back();

            }
        }
    }
}

//初始化
void DlgPlaying::init()
{
    ui->lcdStep->setMode(QLCDNumber::Dec);
    // 设置显示外观
    ui->lcdStep->setSegmentStyle(QLCDNumber::Flat);
    // 设置样式
    ui->lcdStep->setStyleSheet("border: 1px solid green; color: green; background: silver;");
    ui->lcdStep->display("0");


    //初始化拼图
    int num = 1;
    for (int i = 0; i < g_iRank; i++) {
        for (int j = 0; j < g_iRank; j++) {
            _iarrMap[i][j] = num;
            num++;
        }
    }

    _iarrMap[2][2] = 0;
    _iarrBlankCoord[0] = 2, _iarrBlankCoord[1] = 2;

    // Qt显示图片（https://blog.csdn.net/linuxweiyh/article/details/76683479）
    //ui->d_label->setScaledContents(true);

    QPixmap *pixmap = new QPixmap(_strPos);
    pixmap->scaled(ui->labPic->size(), Qt::KeepAspectRatio);
    ui->labPic->setScaledContents(true);
    ui->labPic->setPixmap(*pixmap);

    // 插入空白图片
    QPixmap *pixBlank = new QPixmap(":/img/blank.png");
    pixBlank->scaled(ui->label_9->size(), Qt::KeepAspectRatio);
    _img0 = pixBlank->copy(0, 0, pixBlank->width(), pixBlank->height());


    //ui->label_12->setScaledContents(true);
    QPixmap *pixmap1 = new QPixmap(_strPos);
    pixmap1->scaled(ui->labPic->size()*2, Qt::KeepAspectRatio);

    //切割图片
    _img1 = pixmap1->copy(0,                    0,                      pixmap1->width()/3, pixmap1->height()/3);
    _img2 = pixmap1->copy(pixmap1->width()/3,   0,                      pixmap1->width()/3, pixmap1->height()/3);
    _img3 = pixmap1->copy(pixmap1->width()/3*2, 0,                      pixmap1->width()/3, pixmap1->height()/3);
    _img4 = pixmap1->copy(0,                    pixmap1->height()/3,    pixmap1->width()/3, pixmap1->height()/3);
    _img5 = pixmap1->copy(pixmap1->width()/3,   pixmap1->height()/3,    pixmap1->width()/3, pixmap1->height()/3);
    _img6 = pixmap1->copy(pixmap1->width()/3*2, pixmap1->height()/3,    pixmap1->width()/3, pixmap1->height()/3);
    _img7 = pixmap1->copy(0,                    pixmap1->height()/3*2,  pixmap1->width()/3, pixmap1->height()/3);
    _img8 = pixmap1->copy(pixmap1->width()/3,   pixmap1->height()/3*2,  pixmap1->width()/3, pixmap1->height()/3);

    ui->label_1->setScaledContents(true);
    ui->label_2->setScaledContents(true);
    ui->label_3->setScaledContents(true);
    ui->label_4->setScaledContents(true);
    ui->label_5->setScaledContents(true);
    ui->label_6->setScaledContents(true);
    ui->label_7->setScaledContents(true);
    ui->label_8->setScaledContents(true);
    ui->label_9->setScaledContents(true);

    ui->label_1->setText("1");
    ui->label_2->setText("2");
    ui->label_3->setText("3");
    ui->label_4->setText("4");
    ui->label_5->setText("5");
    ui->label_6->setText("6");
    ui->label_7->setText("7");
    ui->label_8->setText("8");
    ui->label_9->setText("9");


    ui->label_1->setPixmap(_img1);
    ui->label_2->setPixmap(_img2);
    ui->label_3->setPixmap(_img3);
    ui->label_4->setPixmap(_img4);
    ui->label_5->setPixmap(_img5);
    ui->label_6->setPixmap(_img6);
    ui->label_7->setPixmap(_img7);
    ui->label_8->setPixmap(_img8);
    ui->label_9->setPixmap(_img0);
}


void DlgPlaying::move(int x, int y)
{
    int& ix = _iarrBlankCoord[0];
    int& iy = _iarrBlankCoord[1];

    if( ix == x )
    {
        if( qAbs(iy - y ) == 1 )
        {
            qSwap(_iarrMap[iy][ix], _iarrMap[y][x]);
            ix = x;
            iy = y;
        }
    }
    else if( iy == y )
    {
        if( qAbs(ix - x ) == 1 )
        {
            qSwap(_iarrMap[iy][ix], _iarrMap[y][x]);
            ix = x;
            iy = y;
        }
    }
}

void DlgPlaying::move_f(int i)
{
    int& x = _iarrBlankCoord[0];
    int& y = _iarrBlankCoord[1];

    if (i == 1) {                   //上(0在下，和上面的换)
        if (y != 0) {
            std::swap(_iarrMap[y][x], _iarrMap[y-1][x]);
            y--;
        }

    }
    else if (i == 2) {             //下（0在上，和下面的换）
        if (y != g_iRank - 1) {
            std::swap(_iarrMap[y][x], _iarrMap[y+1][x]);
            y++;
        }

    }
    else if (i == 3) {             //左
        if (x != 0) {
            std::swap(_iarrMap[y][x], _iarrMap[y][x-1]);
            x--;
        }
    }
    else if (i == 4) {             //右
        if (x != g_iRank - 1) {
            std::swap(_iarrMap[y][x], _iarrMap[y][x+1]);
            x++;
        }
    }
}

void DlgPlaying::upset()
{
    //打乱300次
    for (int i = 0; i < 300; i++) {
        //Sleep(1000);
        move_f(rand() % 4 + 1);
        //showpicture();
    }
}

void DlgPlaying::showpicture()
{
    //QString tmp_label = QString("QLabel_%1").arg(k);
    //QString tmp_img = QString("img%1").arg(k);
    //QLabel *p = QLabel::findChild("label_3");
    //QLabel* p =  QWidget::findChild<QLabel*>("QLabel_3");
    //QPixmap *imgd = QWidget::findChild<QPixmap*>("img6");

    int k = 1;

    for(int j = 0 ; j < g_iRank ; j++ ) {
        for(int i = 0 ; i < g_iRank ; i++ ) {

            QString tmp_label = QString("label_%1").arg(k);
            //tmp_img = QString("img%1").arg(map[j][i]);
            //根据控件名得到控件指针
            QLabel *p = QWidget::findChild<QLabel*>(tmp_label);

            if(_iarrMap[j][i] == 0) {
                p->setPixmap(_img0);
            } else if (_iarrMap[j][i] == 1) {
                p->setPixmap(_img1);
            } else if (_iarrMap[j][i] == 2) {
                p->setPixmap(_img2);
            } else if (_iarrMap[j][i] == 3) {
                p->setPixmap(_img3);
            } else if (_iarrMap[j][i] == 4) {
                p->setPixmap(_img4);
            } else if (_iarrMap[j][i] == 5) {
                p->setPixmap(_img5);
            } else if (_iarrMap[j][i] == 6) {
                p->setPixmap(_img6);
            } else if (_iarrMap[j][i] == 7) {
                p->setPixmap(_img7);
            } else if (_iarrMap[j][i] == 8) {
                p->setPixmap(_img8);
            }

            k++;
        }
    }
}

bool DlgPlaying::bSuccessful()
{
    int num = 1;

    for(int j = 0 ; j < g_iRank ; j++ ) {
        for(int i = 0 ; i < g_iRank ; i++ ) {

            if (g_iRank-1 == i && g_iRank - 1 == j)
                break;

            if (_iarrMap[j][i] != num)
                return false;
            num++;
        }
    }

    return _iarrMap[g_iRank-1][g_iRank-1] == 0;
}

void DlgPlaying::on_btnBack_clicked()
{
    this->hide();
    this->parentWidget()->show();
}

void DlgPlaying::on_btnRestart_clicked()
{
//    init();
//    this->show();
    start();
}

