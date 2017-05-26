#ifndef WRITEMAILDLG_H
#define WRITEMAILDLG_H
#include "qt.h"
class WriteMailDlg:public QDialog
{
    Q_OBJECT
public:
    WriteMailDlg(QWidget *parent =0);
    void openDraft(MailData &md);
signals:
    void send2Draft(MailData &md);
    void send2Send(MailData &md);
private:
    QLineEdit   *mRecvEdit;
    QLineEdit   *mBccEdit;
    QLineEdit   *mCCEdit;
    QLineEdit   *mSubsEdit;
    QTextEdit   *mCtntEdit;
    QPushButton *mBcc;//√‹ÀÕ
    QPushButton *mCC;//≥≠ÀÕ
    QPushButton *mAttach;
    QPushButton *mPhoto;
    QPushButton *mSave;
    QPushButton *mSend;
    QPushButton *mQuit;
    MailData mMD;
    QGridLayout *mainLyt;
    deque<Contents> mCtnsDeque;
    QLabel *mRecvLabel;
    QLabel *mTipsLabel;
    QLabel *mSubsLabel;
    QLabel *mCtntLabel;
    QLabel *mBccLabel;
    QLabel *mCCLabel;
    QLabel *mAttachLabel;
    QString fileName;
    int ki,kj;
    int mi,mj;
    bool bbci,bcci,bj;
    bool battach;
    bool mDraftEdited,mDraftorMail; //mDraftorMail  true  -- edit draft
                                    //              false -- write mail
                                    //mDraftEdited  true  -- draft edited
                                    //              false -- dfaft unedited;
    void readEdits();
    void closeEvent(QCloseEvent *event);
    bool cmpContents();
private slots:
    void setLyt(int i=0, int j=0);
    void attachFile();
    void addPic();
    void addBcc();
    void addCC();
    void sendEmail();
    void saveDraft();
    bool checkEdit();
    void setFlag();
    void save();
    void replaceSave();
};

#endif // WRITEMAILDLG_H
