#include "stdafx.h"
#include <memory>
#include <QTimer>
#include <QDebug>
#include <QMessagebox>
#include <QFileDialog>

#include "CrystalSoftwarePackage.h"
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

	connect(ui.pushButton_load, &QPushButton::clicked, this, &CrystalSoftwarePackage::LoadFiles);
	connect(ui.pushButton_run, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
		
	ui.pushButton_run->setEnabled(false);
	//qRegisterMetaType<Mat>("Mat");

	alg = new Warper;
	connect(alg, &Warper::sig_ShowImg, ui.label, &QLabel::setPixmap);
	connect(alg, &Warper::sig_ShowText, ui.textBrowser, &QTextBrowser::append);
	connect(ui.pushButton_pause, &QPushButton::clicked, alg, &Warper::Pause);
}

CrystalSoftwarePackage::~CrystalSoftwarePackage()
{
	delete alg;
}

void CrystalSoftwarePackage::LoadFiles()
{
	QString filename = QFileDialog::getOpenFileName(this, tr(u8"打开文件"), ".", tr(u8"图片文件(*.jpg *.jpeg *.png *.bmp)"));
	if( false==filename.isEmpty())
	{
		QImage qimg(filename);
		qDebug() << __FUNCTION__ << '[' << alg->LoadSrc(Mat(qimg.height(), qimg.width(), CV_8UC4, qimg.bits())) << ']';
		ui.pushButton_run->setEnabled(true);
		ui.label->setPixmap(QPixmap::fromImage(qimg));
	}
	else
	{
#ifdef _DEBUG
		QImage qimg(u8"..\\Crystal Software Package\\resource\\testpic.jpg");
		qDebug() << __FUNCTION__ << '[' << alg->LoadSrc(Mat(qimg.height(), qimg.width(), CV_8UC4, qimg.bits())) << ']';
		ui.pushButton_run->setEnabled(true);
		ui.label->setPixmap(QPixmap::fromImage(qimg));
#endif // _DEBUG
	}
	return;
}

void CrystalSoftwarePackage::RunAlg()
{
	if (alg->IsRun() == true) 
	{
		qDebug() << "running...";
		alg->Stop();
		return;
	}
	//ui.pushButton_run->setText("暂停");
	//disconnect(ui.pushButton_run, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
	try {
		ui.pushButton_run->setText(u8"停止");
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
