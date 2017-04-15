#include "qmainwin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QFile style("../csEmail/style.qss");
//    if(!style.open(QIODevice::ReadOnly))
//    {
//        qDebug("open app.qss no!");
//        //return -1;
//    }
//    a.setStyleSheet(style.readAll());
//    style.close();
    QMainWin w;
    w.show();

    return a.exec();
}


bool readSetFile(QWidget*parent, QString str[])
{
    QFile file("../csEmail/data/settings.txt");
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(parent,QStringLiteral("警告"),QStringLiteral("无法打开文件settings.txt"),QMessageBox::Yes);
        return false;
    }
    QDataStream stream(&file);
    int i=0;
    while(i<8){
        stream >> str[i++];
    }
    file.close();
    return true;
}
