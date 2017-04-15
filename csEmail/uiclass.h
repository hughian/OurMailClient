#ifndef UICLASS_H
#define UICLASS_H
#include "qt.h"
enum {RECV,SEND,DRAFT,DUST};
class NavigationBar:public QWidget{
    Q_OBJECT
public:
    NavigationBar(QWidget *parent=0);
    ~NavigationBar();
private:
    QPushButton *mWriteMail;
    QPushButton *mSettings;
    QPushButton *mContacts;
    QPushButton *mRecvBox;
    QPushButton *mSendBox;
    QPushButton *mDraftBox;
    QPushButton *mDustBin;
};
class NaviBar:public QWidget{
    Q_OBJECT
public:
    NaviBar(QWidget *parent = 0);
    NaviBar(int,QWidget *parent = 0);
    friend class QMainWin;
private:
    QToolButton *mWriteMail;
    QToolButton *mContacts;
    QToolButton *mRecvBox;
    QToolButton *mSendBox;
    QToolButton *mDraftBox;
    QToolButton *mDustBin;
    QToolButton *mSettings;
    QToolButton *mAbout;
};

class ToolBtn:public QWidget{
    Q_OBJECT
public:
    ToolBtn(QString name,QString str,QWidget *parent = 0);
};

class MailList:public QWidget{
    Q_OBJECT
public:
    MailList(int type,QWidget *parent = 0);
private:
    QTableWidget *mTable;
};


class WriteMailDlg:public QDialog
{
    Q_OBJECT
public:
    WriteMailDlg(QWidget *parent =0);
private:
    QLineEdit   *mRecvEdit;
    QLineEdit   *mSubsEdit;
    QTextEdit   *mCtntEdit;
    QPushButton *mSave;
    QPushButton *mSend;
    QPushButton *mQuit;
};

//struct SetData{
//    QString usrName;
//    QString Address;
//    QString recvSer;
//    QString recvPort;
//    QString sendSer;
//    QString sendPort;
//    QString Account;
//    QString password;
//};
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
class AboutDlg:public QDialog
{
    Q_OBJECT
public:
    AboutDlg(QWidget *parent = 0);
private:
    QPushButton *mConfirm;
private slots:
    void on_mConfirm_clicked(){accept();};
};
#endif // UICLASS_H
