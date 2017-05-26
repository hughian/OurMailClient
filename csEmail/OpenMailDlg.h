#ifndef OPENMAILDLG_H
#define OPENMAILDLG_H
#include "qt.h"
class OpenMailDlg : public QDialog
{
public:
    OpenMailDlg(MailData &md, QWidget *parent = 0);
private:
    QLabel *mFrom;
    QLabel *mSubs;
    QLabel *mCtns;
    QLineEdit *mFromEdit;
    QLineEdit *mSubsEdit;
    QTextEdit *mCtnsEdit;
    QGridLayout *mainLyt;
    QPushButton *mConfirm;
};

#endif // OPENMAILDLG_H
