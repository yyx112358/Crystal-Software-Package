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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CrystalSoftwarePackageClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_run;
    QLabel *label;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_load;
    QPushButton *pushButton_pause;
    QProgressBar *progressBar;
    QLabel *label_2;
    QTextBrowser *textBrowser_2;
    QPushButton *pushButton_load_2;
    QPushButton *pushButton_pause_2;
    QPushButton *pushButton_run_2;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_3;
    QSlider *horizontalSlider_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CrystalSoftwarePackageClass)
    {
        if (CrystalSoftwarePackageClass->objectName().isEmpty())
            CrystalSoftwarePackageClass->setObjectName(QStringLiteral("CrystalSoftwarePackageClass"));
        CrystalSoftwarePackageClass->resize(1683, 721);
        centralWidget = new QWidget(CrystalSoftwarePackageClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_run = new QPushButton(centralWidget);
        pushButton_run->setObjectName(QStringLiteral("pushButton_run"));
        pushButton_run->setGeometry(QRect(10, 70, 91, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 10, 641, 531));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(0, 180, 191, 361));
        pushButton_load = new QPushButton(centralWidget);
        pushButton_load->setObjectName(QStringLiteral("pushButton_load"));
        pushButton_load->setGeometry(QRect(10, 30, 93, 28));
        pushButton_pause = new QPushButton(centralWidget);
        pushButton_pause->setObjectName(QStringLiteral("pushButton_pause"));
        pushButton_pause->setGeometry(QRect(10, 120, 93, 28));
        pushButton_pause->setCheckable(true);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(490, 590, 731, 21));
        progressBar->setValue(0);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(830, 10, 641, 531));
        textBrowser_2 = new QTextBrowser(centralWidget);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(1480, 150, 191, 361));
        pushButton_load_2 = new QPushButton(centralWidget);
        pushButton_load_2->setObjectName(QStringLiteral("pushButton_load_2"));
        pushButton_load_2->setGeometry(QRect(1540, 20, 93, 28));
        pushButton_pause_2 = new QPushButton(centralWidget);
        pushButton_pause_2->setObjectName(QStringLiteral("pushButton_pause_2"));
        pushButton_pause_2->setGeometry(QRect(1540, 110, 93, 28));
        pushButton_pause_2->setCheckable(true);
        pushButton_run_2 = new QPushButton(centralWidget);
        pushButton_run_2->setObjectName(QStringLiteral("pushButton_run_2"));
        pushButton_run_2->setGeometry(QRect(1540, 60, 91, 31));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 550, 391, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(centralWidget);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(20, 600, 391, 22));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_3 = new QSlider(centralWidget);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(1260, 550, 391, 22));
        horizontalSlider_3->setMaximum(255);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        horizontalSlider_4 = new QSlider(centralWidget);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setGeometry(QRect(1260, 590, 391, 22));
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        CrystalSoftwarePackageClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CrystalSoftwarePackageClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1683, 26));
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
        pushButton_load->setText(QApplication::translate("CrystalSoftwarePackageClass", "\350\275\275\345\205\245", Q_NULLPTR));
        pushButton_pause->setText(QApplication::translate("CrystalSoftwarePackageClass", "\346\232\202\345\201\234", Q_NULLPTR));
        label_2->setText(QApplication::translate("CrystalSoftwarePackageClass", "TextLabel", Q_NULLPTR));
        pushButton_load_2->setText(QApplication::translate("CrystalSoftwarePackageClass", "\350\275\275\345\205\245", Q_NULLPTR));
        pushButton_pause_2->setText(QApplication::translate("CrystalSoftwarePackageClass", "\346\232\202\345\201\234", Q_NULLPTR));
        pushButton_run_2->setText(QApplication::translate("CrystalSoftwarePackageClass", "\350\277\220\350\241\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CrystalSoftwarePackageClass: public Ui_CrystalSoftwarePackageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRYSTALSOFTWAREPACKAGE_H
