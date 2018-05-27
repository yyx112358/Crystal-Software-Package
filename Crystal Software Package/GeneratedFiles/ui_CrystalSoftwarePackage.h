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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CrystalSoftwarePackageClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CrystalSoftwarePackageClass)
    {
        if (CrystalSoftwarePackageClass->objectName().isEmpty())
            CrystalSoftwarePackageClass->setObjectName(QStringLiteral("CrystalSoftwarePackageClass"));
        CrystalSoftwarePackageClass->resize(600, 400);
        menuBar = new QMenuBar(CrystalSoftwarePackageClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CrystalSoftwarePackageClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CrystalSoftwarePackageClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CrystalSoftwarePackageClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CrystalSoftwarePackageClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CrystalSoftwarePackageClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CrystalSoftwarePackageClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CrystalSoftwarePackageClass->setStatusBar(statusBar);

        retranslateUi(CrystalSoftwarePackageClass);

        QMetaObject::connectSlotsByName(CrystalSoftwarePackageClass);
    } // setupUi

    void retranslateUi(QMainWindow *CrystalSoftwarePackageClass)
    {
        CrystalSoftwarePackageClass->setWindowTitle(QApplication::translate("CrystalSoftwarePackageClass", "CrystalSoftwarePackage", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CrystalSoftwarePackageClass: public Ui_CrystalSoftwarePackageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRYSTALSOFTWAREPACKAGE_H
