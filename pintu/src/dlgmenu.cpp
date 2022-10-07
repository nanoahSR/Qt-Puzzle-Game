#include "dlgmenu.h"
#include "ui_DlgMenu.h"

#include <QTimer>

DlgMenu::DlgMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgMenu),
    _dlgPlay(nullptr)
{
    ui->setupUi(this);

    init();


}

DlgMenu::~DlgMenu()
{
    delete ui;
}

void DlgMenu::init()
{
//    _dlgPlay = new DlgPlaying(this);
}

void DlgMenu::on_btStart_clicked()
{
    QTimer::singleShot(500, this, [=](){
        this->hide();
        if (_dlgPlay == nullptr)
        {
            _dlgPlay = new DlgPlaying(this);
            _dlgPlay->start();
        }
        _dlgPlay->show();
    });
}

void DlgMenu::on_btnExit_clicked()
{
    this->close();
}
