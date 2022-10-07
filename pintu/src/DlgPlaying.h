#ifndef DLGPLAYING_H
#define DLGPLAYING_H

#include <QDialog>

namespace Ui {
class DlgPlaying;
}

class DlgPlaying : public QDialog
{
    Q_OBJECT

public:
    explicit DlgPlaying(QWidget *parent = nullptr);
    ~DlgPlaying();

    void start();

private:
    Ui::DlgPlaying *ui;

    QPixmap _img1, _img2, _img3, _img4, _img5, _img6, _img7, _img8, _img0;
    int _iarrMap[3][3];             //娉ㄦ剰鍓嶉潰鏄痽, 鍚庨潰鎵嶆槸x!
    int _iarrBlankCoord[2];     // 绌轰綅缃殑x, y鍧愭爣
    QString _strPos;            // 鍥剧墖浣嶇疆

    bool _bStart;               //鏍囪鏄惁寮€濮嬫父鎴
    int _iStep;
    void mousePressEvent(QMouseEvent *event);       //榧犳爣鐐瑰嚮浜嬩欢

    void init();           //鍒濆鍖
    void move(int x,int y);       //绉诲姩
    void move_f(int i);     //鏈夋柟鍚戠殑绉诲姩
    void upset();           //鎵撲贡
    void showpicture();     //鏄剧ず
    bool bSuccessful();

signals:
    void sig_restart();
    void sig_back();

private slots:
    void on_btnRestart_clicked();
    void on_btnBack_clicked();
};

#endif // DLGPLAYING_H
