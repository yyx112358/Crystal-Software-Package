#include "stdafx.h"
#include <QMetaType>
#include <QTimer>
#include <memory>
#include <QDebug>

#include "CrystalSoftwarePackage.h"
#include "Warper.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\Algorithm.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\Algorithm.lib")
#endif

using namespace cv;
using namespace std;

CrystalSoftwarePackage::CrystalSoftwarePackage(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(this, &CrystalSoftwarePackage::sig_ShowText, ui.textBrowser, &QTextBrowser::append);
	connect(this, &CrystalSoftwarePackage::sig_ShowImg, ui.label, &QLabel::setPixmap);
	connect(ui.pushButton_load, &QPushButton::clicked, this, &CrystalSoftwarePackage::LoadFiles);
	connect(ui.pushButton_run, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
		
	ui.pushButton_run->setEnabled(false);
	//qRegisterMetaType<Mat>("Mat");

	alg = new Warper;
	connect(alg, &Warper::sig_ShowImg, ui.label, &QLabel::setPixmap);
}

CrystalSoftwarePackage::~CrystalSoftwarePackage()
{
	delete alg;
	
}

void CrystalSoftwarePackage::LoadFiles()
{
	qDebug() << __FUNCTION__;
	QImage qimg("..\\Crystal Software Package\\resource\\testpic.jpg");
	alg->LoadSrc(Mat(qimg.height(),qimg.width(),CV_8UC4,qimg.bits()));
	ui.pushButton_run->setEnabled(true);
}

void CrystalSoftwarePackage::RunAlg()
{
	//ui.pushButton_run->setText("暂停");
	//disconnect(ui.pushButton_run, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
	try {
		qDebug() << "start...";
		//alg->run();
		alg->start();
		qDebug() << "over...";
	}
	catch (std::system_error e)
	{
		qDebug() << e.what();
	}
	//connect(ui.pushButton_run, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
}

void CrystalSoftwarePackage::PauseAlg(bool ispause)
{

}
