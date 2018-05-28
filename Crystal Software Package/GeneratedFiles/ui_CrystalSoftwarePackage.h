/********************************************************************************
** Form generated from reading UI file 'CrystalSoftwarePackage.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRYSTALSOFTWAREPACKAGE_H
#define UI_CRYSTALSOFTWAREPACKAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CrystalSoftwarePackageClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_run;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CrystalSoftwarePackageClass)
    {
        if (CrystalSoftwarePackageClass->objectName().isEmpty())
            CrystalSoftwarePackageClass->setObjectName(QStringLiteral("CrystalSoftwarePackageClass"));
        CrystalSoftwarePackageClass->resize(600, 400);
        centralWidget = new QWidget(CrystalSoftwarePackageClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_run = new QPushButton(centralWidget);
        pushButton_run->setObjectName(QStringLiteral("pushButton_run"));
        pushButton_run->setGeometry(QRect(20, 80, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 40, 391, 251));
        CrystalSoftwarePackageClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CrystalSoftwarePackageClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        CrystalSoftwarePackageClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CrystalSoftwarePackageClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CrystalSoftwarePackageClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CrystalSoftwarePackageClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CrystalSoftwarePackageClass->setStatusBar(statusBar);

        retranslateUi(CrystalSoftwarePackageClass);

        QMetaObject::connectSlotsByName(CrystalSoftwarePackageClass);
    } // setupUi

    void retranslateUi(QMainWindow *CrystalSoftwarePackageClass)
    {
        CrystalSoftwarePackageClass->setWindowTitle(QApplication::translate("CrystalSoftwarePackageClass", "CrystalSoftwarePackage", Q_NULLPTR));
        pushButton_run->setText(QApplication::translate("CrystalSoftwarePackageClass", "\350\277\220\350\241\214", Q_NULLPTR));
        label->setText(QApplication::translate("CrystalSoftwarePackageClass", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CrystalSoftwarePackageClass: public Ui_CrystalSoftwarePackageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRYSTALSOFTWAREPACKAGE_H
