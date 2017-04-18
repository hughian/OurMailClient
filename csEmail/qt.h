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
bool readSetFile(QWidget *msgParent, QString str[]);
bool readBoxFile(QString filename, QList<QStringList> &Qqsl);
bool writeBoxFile(QString filename,QList<QStringList> &Qqsl);
#endif // QT_H
