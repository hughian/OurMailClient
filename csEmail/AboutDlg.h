#ifndef ABOUTDLG_H
#define ABOUTDLG_H
#include "qt.h"

class AboutDlg:public QDialog
{
    Q_OBJECT
public:
    AboutDlg(QWidget *parent = 0);
private:
    QPushButton *mConfirm;
private slots:
    void on_mConfirm_clicked(){accept();}
};

#endif // ABOUTDLG_H
