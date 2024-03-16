#ifndef DLGMENU_H
#define DLGMENU_H

#include <QDialog>

#include "DlgPlaying.h"

namespace Ui {
class dlgMenu;
}

class DlgMenu : public QDialog
{
    Q_OBJECT

public:
    explicit DlgMenu(QWidget *parent = nullptr);
    ~DlgMenu();

private:
    Ui::dlgMenu *ui;

   DlgPlaying *_dlgPlay;

    void init();

private slots:
    void on_btStart_clicked();
    void on_btnExit_clicked();
};

#endif // DLGMENU_H
