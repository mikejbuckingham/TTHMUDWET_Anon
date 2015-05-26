/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *newPushButton;
    QPushButton *openFolderPushButton;
    QPushButton *setStringsButton;
    QPushButton *anonPushButton;
    QPushButton *savePushButton;
    QPushButton *openFilePushButton;
    QPushButton *closeFilePushbutton;
    QLabel *currentFileConst;
    QLabel *currentFileValue;
    QLabel *label_4;
    QLabel *isDataAnonValue;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioFolder;
    QRadioButton *radioZip;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QMenu *menu_About;
    QMenu *menuMusic_Tool;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(451, 338);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QStringLiteral("action_About"));
        actionOpen_Folder = new QAction(MainWindow);
        actionOpen_Folder->setObjectName(QStringLiteral("actionOpen_Folder"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(172, 22, 146, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(173, 50, 50, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(173, 79, 68, 21));
        nameAnonUI = new QLabel(centralWidget);
        nameAnonUI->setObjectName(QStringLiteral("nameAnonUI"));
        nameAnonUI->setGeometry(QRect(229, 50, 161, 21));
        dateAnonUI = new QLabel(centralWidget);
        dateAnonUI->setObjectName(QStringLiteral("dateAnonUI"));
        dateAnonUI->setGeometry(QRect(247, 79, 141, 21));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 102, 243));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        newPushButton = new QPushButton(layoutWidget);
        newPushButton->setObjectName(QStringLiteral("newPushButton"));

        verticalLayout->addWidget(newPushButton);

        openFolderPushButton = new QPushButton(layoutWidget);
        openFolderPushButton->setObjectName(QStringLiteral("openFolderPushButton"));

        verticalLayout->addWidget(openFolderPushButton);

        setStringsButton = new QPushButton(layoutWidget);
        setStringsButton->setObjectName(QStringLiteral("setStringsButton"));

        verticalLayout->addWidget(setStringsButton);

        anonPushButton = new QPushButton(layoutWidget);
        anonPushButton->setObjectName(QStringLiteral("anonPushButton"));

        verticalLayout->addWidget(anonPushButton);

        savePushButton = new QPushButton(layoutWidget);
        savePushButton->setObjectName(QStringLiteral("savePushButton"));

        verticalLayout->addWidget(savePushButton);

        openFilePushButton = new QPushButton(layoutWidget);
        openFilePushButton->setObjectName(QStringLiteral("openFilePushButton"));

        verticalLayout->addWidget(openFilePushButton);

        closeFilePushbutton = new QPushButton(layoutWidget);
        closeFilePushbutton->setObjectName(QStringLiteral("closeFilePushbutton"));

        verticalLayout->addWidget(closeFilePushbutton);


        verticalLayout_2->addLayout(verticalLayout);

        currentFileConst = new QLabel(centralWidget);
        currentFileConst->setObjectName(QStringLiteral("currentFileConst"));
        currentFileConst->setGeometry(QRect(151, 191, 84, 21));
        currentFileValue = new QLabel(centralWidget);
        currentFileValue->setObjectName(QStringLiteral("currentFileValue"));
        currentFileValue->setGeometry(QRect(150, 210, 291, 51));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(140, 130, 141, 21));
        isDataAnonValue = new QLabel(centralWidget);
        isDataAnonValue->setObjectName(QStringLiteral("isDataAnonValue"));
        isDataAnonValue->setGeometry(QRect(300, 130, 65, 21));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(130, 160, 238, 31));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radioFolder = new QRadioButton(widget);
        radioFolder->setObjectName(QStringLiteral("radioFolder"));

        horizontalLayout->addWidget(radioFolder);

        radioZip = new QRadioButton(widget);
        radioZip->setObjectName(QStringLiteral("radioZip"));

        horizontalLayout->addWidget(radioZip);


        horizontalLayout_2->addLayout(horizontalLayout);

        progressBar = new QProgressBar(widget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        horizontalLayout_2->addWidget(progressBar);

        MainWindow->setCentralWidget(centralWidget);
        label->raise();
        label_2->raise();
        label_3->raise();
        nameAnonUI->raise();
        dateAnonUI->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        radioFolder->raise();
        progressBar->raise();
        currentFileConst->raise();
        currentFileValue->raise();
        label_4->raise();
        isDataAnonValue->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 451, 27));
        menu_About = new QMenu(menuBar);
        menu_About->setObjectName(QStringLiteral("menu_About"));
        menuMusic_Tool = new QMenu(menuBar);
        menuMusic_Tool->setObjectName(QStringLiteral("menuMusic_Tool"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_Open->setText(QApplication::translate("MainWindow", "Open File", 0));
        action_About->setText(QApplication::translate("MainWindow", "&About", 0));
        actionOpen_Folder->setText(QApplication::translate("MainWindow", "Open Folder", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        label->setText(QApplication::translate("MainWindow", "Anonymisation Strings", 0));
        label_2->setText(QApplication::translate("MainWindow", "Name : ", 0));
        label_3->setText(QApplication::translate("MainWindow", "Birthdate :", 0));
        nameAnonUI->setText(QApplication::translate("MainWindow", "NONE", 0));
        dateAnonUI->setText(QApplication::translate("MainWindow", "NONE", 0));
        newPushButton->setText(QApplication::translate("MainWindow", "New", 0));
        openFolderPushButton->setText(QApplication::translate("MainWindow", "Open Folder", 0));
        setStringsButton->setText(QApplication::translate("MainWindow", "Set strings", 0));
        anonPushButton->setText(QApplication::translate("MainWindow", "Anonymise", 0));
        savePushButton->setText(QApplication::translate("MainWindow", "Save", 0));
        openFilePushButton->setText(QApplication::translate("MainWindow", "Open File", 0));
        closeFilePushbutton->setText(QApplication::translate("MainWindow", "Close File", 0));
        currentFileConst->setText(QApplication::translate("MainWindow", "Current File :", 0));
        currentFileValue->setText(QApplication::translate("MainWindow", "NONE", 0));
        label_4->setText(QApplication::translate("MainWindow", "Is data anonymised?", 0));
        isDataAnonValue->setText(QApplication::translate("MainWindow", "No", 0));
        radioFolder->setText(QApplication::translate("MainWindow", "Folder", 0));
        radioZip->setText(QApplication::translate("MainWindow", "Zip", 0));
        menu_About->setTitle(QApplication::translate("MainWindow", "&Help", 0));
        menuMusic_Tool->setTitle(QApplication::translate("MainWindow", "&File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
