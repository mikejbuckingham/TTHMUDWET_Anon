#include "mainwindow.h"
#include <QApplication>
#include <QMetaType>

#include <medStyleSheetParser.h>

#include <QtGui>

#include <QFile>

#define QT_NO_STYLE_STYLESHEET 0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setStyle("plastique");

    QFile f(":/medInria.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        medStyleSheetParser aStyleSheetParser(ts.readAll());
        a.setStyleSheet(aStyleSheetParser.result());
    }


    w.show();

    return a.exec();
}
