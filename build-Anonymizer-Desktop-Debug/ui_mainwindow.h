/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_About;
    QAction *actionOpen_Folder;
    QAction *actionClose;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *nameAnonUI;
    QLabel *dateAnonUI;
    QPushButton *setStringsButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioFolder;
    QRadioButton *radioZip;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *newPushButton;
    QPushButton *openFolderPushButton;
    QPushButton *openFilePushButton;
    QPushButton *closeFilePushbutton;
    QPushButton *anonPushButton;
    QPushButton *savePushButton;
    QMenuBar *menuBar;
    QMenu *menu_About;
    QMenu *menuMusic_Tool;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        actionOpen_Folder = new QAction(MainWindow);
        actionOpen_Folder->setObjectName(QString::fromUtf8("actionOpen_Folder"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(172, 22, 146, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(173, 50, 50, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(173, 79, 68, 21));
        nameAnonUI = new QLabel(centralWidget);
        nameAnonUI->setObjectName(QString::fromUtf8("nameAnonUI"));
        nameAnonUI->setGeometry(QRect(229, 50, 161, 21));
        dateAnonUI = new QLabel(centralWidget);
        dateAnonUI->setObjectName(QString::fromUtf8("dateAnonUI"));
        dateAnonUI->setGeometry(QRect(247, 79, 141, 21));
        setStringsButton = new QPushButton(centralWidget);
        setStringsButton->setObjectName(QString::fromUtf8("setStringsButton"));
        setStringsButton->setGeometry(QRect(280, 110, 92, 29));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(130, 200, 131, 28));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radioFolder = new QRadioButton(widget);
        radioFolder->setObjectName(QString::fromUtf8("radioFolder"));

        horizontalLayout->addWidget(radioFolder);

        radioZip = new QRadioButton(widget);
        radioZip->setObjectName(QString::fromUtf8("radioZip"));

        horizontalLayout->addWidget(radioZip);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(20, 20, 102, 208));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        newPushButton = new QPushButton(widget1);
        newPushButton->setObjectName(QString::fromUtf8("newPushButton"));

        verticalLayout->addWidget(newPushButton);

        openFolderPushButton = new QPushButton(widget1);
        openFolderPushButton->setObjectName(QString::fromUtf8("openFolderPushButton"));

        verticalLayout->addWidget(openFolderPushButton);

        openFilePushButton = new QPushButton(widget1);
        openFilePushButton->setObjectName(QString::fromUtf8("openFilePushButton"));

        verticalLayout->addWidget(openFilePushButton);

        closeFilePushbutton = new QPushButton(widget1);
        closeFilePushbutton->setObjectName(QString::fromUtf8("closeFilePushbutton"));

        verticalLayout->addWidget(closeFilePushbutton);

        anonPushButton = new QPushButton(widget1);
        anonPushButton->setObjectName(QString::fromUtf8("anonPushButton"));

        verticalLayout->addWidget(anonPushButton);


        verticalLayout_2->addLayout(verticalLayout);

        savePushButton = new QPushButton(widget1);
        savePushButton->setObjectName(QString::fromUtf8("savePushButton"));

        verticalLayout_2->addWidget(savePushButton);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 27));
        menu_About = new QMenu(menuBar);
        menu_About->setObjectName(QString::fromUtf8("menu_About"));
        menuMusic_Tool = new QMenu(menuBar);
        menuMusic_Tool->setObjectName(QString::fromUtf8("menuMusic_Tool"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMusic_Tool->menuAction());
        menuBar->addAction(menu_About->menuAction());
        menu_About->addAction(action_About);
        menuMusic_Tool->addAction(action_Open);
        menuMusic_Tool->addAction(actionOpen_Folder);
        menuMusic_Tool->addAction(actionClose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "Open File", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("MainWindow", "&About", 0, QApplication::UnicodeUTF8));
        actionOpen_Folder->setText(QApplication::translate("MainWindow", "Open Folder", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Anonymisation Strings", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Name : ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Birthdate :", 0, QApplication::UnicodeUTF8));
        nameAnonUI->setText(QApplication::translate("MainWindow", "NONE", 0, QApplication::UnicodeUTF8));
        dateAnonUI->setText(QApplication::translate("MainWindow", "NONE", 0, QApplication::UnicodeUTF8));
        setStringsButton->setText(QApplication::translate("MainWindow", "Set strings", 0, QApplication::UnicodeUTF8));
        radioFolder->setText(QApplication::translate("MainWindow", "Folder", 0, QApplication::UnicodeUTF8));
        radioZip->setText(QApplication::translate("MainWindow", "Zip", 0, QApplication::UnicodeUTF8));
        newPushButton->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        openFolderPushButton->setText(QApplication::translate("MainWindow", "Open Folder", 0, QApplication::UnicodeUTF8));
        openFilePushButton->setText(QApplication::translate("MainWindow", "Open File", 0, QApplication::UnicodeUTF8));
        closeFilePushbutton->setText(QApplication::translate("MainWindow", "Close File", 0, QApplication::UnicodeUTF8));
        anonPushButton->setText(QApplication::translate("MainWindow", "Anonymise", 0, QApplication::UnicodeUTF8));
        savePushButton->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        menu_About->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menuMusic_Tool->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
