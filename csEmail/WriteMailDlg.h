#ifndef WRITEMAILDLG_H
#define WRITEMAILDLG_H
#include "qt.h"
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

#endif // WRITEMAILDLG_H
