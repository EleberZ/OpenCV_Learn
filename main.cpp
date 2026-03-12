// OpenCV_Learn.cpp: 定义应用程序的入口点。
//

#include "OpenCV_Learn.h"
#include <QApplication>
#include <QTranslator>
#include <QSettings>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setStyle("Fusion");
    QTranslator appTrans;
    QSettings set("Zhang", "Language");
    int type = set.value("type").toInt();
    if( type==1 )
    {
        if( appTrans.load("TMC_CN.qm") )
            QCoreApplication::installTranslator(&appTrans);
    }
    else if( type==2 )
    {
        if( appTrans.load("TMC_TS.qm") )
            QCoreApplication::installTranslator(&appTrans);
    }
    OpenCV w;
    w.show();
    int rtn = a.exec();
    return rtn;
}
