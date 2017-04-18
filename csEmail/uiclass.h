#ifndef UICLASS_H
#define UICLASS_H
#include "qt.h"
#include <QStyledItemDelegate>
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
    MailList(QWidget *parent = 0);
protected:
    QList<QStringList> mQqsl;
    QTableWidget *mTable;
	QMenu *mPopMenu;
    QAction *mDelete;
    QAction *mOpen;
    void setBox(QString &filename);
private:
    void initActions();
    //void contextMenuEvent(QContextMenuEvent *event);
};

class RecvList:public MailList{
	Q_OBJECT
public:
	RecvList(QWidget *parent = 0);
public slots:
	void setRecv();
};
class SendList:public MailList{
    Q_OBJECT
public:
    SendList(QWidget *parent = 0);
public slots:
	void setSend();
};

class DrftList:public MailList{
    Q_OBJECT
public:
    DrftList(QWidget *parent = 0);
private:
    QAction *mDeleAll;
public slots:
    void setDraft();
	void openDraft();
	void deleDraft();
private:
    void contextMenuEvent(QContextMenuEvent *event);
};
class DustList:public MailList{
	Q_OBJECT
public:
	DustList(QWidget *parent = 0);
public slots:
	void setDust();
};

class WriteMailDlg:public QDialog
{
    Q_OBJECT
public:
    WriteMailDlg(QWidget *parent =0);
    void openDraft(QStringList &qsl);
private:
    QLineEdit   *mRecvEdit;
    QLineEdit   *mSubsEdit;
    QTextEdit   *mCtntEdit;
    QPushButton *mSave;
    QPushButton *mSend;
    QPushButton *mQuit;
    QStringList mQsl;
    bool mDraftEdited,mDraftorMail; //mDraftorMail  true  -- edit draft
                                    //              false -- write mail
                                    //mDraftEdited  true  -- draft edited
                                    //              false -- dfaft unedited;
    void readEdits(MailData &);
    void closeEvent(QCloseEvent *event);
private slots:
    void sendEmail();
    void saveDraft();
    bool checkEdit();
    void change();
    void edit();
    void setFlag();
    void save();
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
    void on_mConfirm_clicked(){accept();}
};


class NoFocusDelegate : public QStyledItemDelegate
{
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

#endif // UICLASS_H
