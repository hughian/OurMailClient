#ifndef QT_H
#define QT_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QGroupBox>

#include <QTableWidget>

#include <QHeaderView>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QMessageBox>
#include <QIcon>
#include <QStackedWidget>
#include <QDateTime>
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
#include <QDebug>

#include "structdef.h"
enum {RECV,SEND,DRAFT,DUST};
enum{
    usrName,
    Address,
    recvSer,
    recvPort,
    sendSer,
    sendPort,
    Account,
    password,
    deleteOp,
};
bool readSetFile(QWidget *msgParent, QString str[], QList<QStringList> &qQsl);
bool writeSetFile(QWidget *msgParent,QString str[],QList<QStringList> &qQsl);
bool readBoxFile(QString filename, QList<MailData> &mdl);
bool writeBoxFile(QString filename, QList<MailData> &mdl);
bool appendBoxFile(QString filename,MailData &md);

void printmdl(QList<MailData> &mdl);
#endif // QT_H
