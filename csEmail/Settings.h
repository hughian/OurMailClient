#ifndef SETTINGS_H
#define SETTINGS_H
#include "qt.h"

class SettingsDlg:public QDialog
{
    Q_OBJECT
public:
    SettingsDlg(QWidget *parent =0);
    friend class QMainWin;
private:
    QLineEdit *mUsrEdit;
    QLineEdit *mAdrEdit;
    QLineEdit *mPopEdit;
    QLineEdit *mRptEdit;
    QLineEdit *mMtpEdit;
    QLineEdit *mSptEdit;
    QLineEdit *mActEdit;
    QLineEdit *mPswEdit;
    QPushButton *mConfirm;
    QPushButton *mCancel;
    bool readFile (void);
    bool writeFile(void);
signals:
    void send(QString &);
private slots:
    void on_mConfirm_clicked();
    void on_mCancel_clicked ();
};

#endif // SETTINGS_H
