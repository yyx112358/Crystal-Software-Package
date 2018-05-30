#include "stdafx.h"
#include <memory>
#include <QTimer>
#include <QDebug>
#include <QMessagebox>
#include <QFileDialog>

#include "CrystalSoftwarePackage.h"
#include "WarperTable.h"
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

	Warpper*warpper = new Warper_Simpletest;
	algs.push_back(warpper);
	connect(warpper, &Warpper::sig_ShowImg, ui.label, &QLabel::setPixmap);
	connect(warpper, &Warpper::sig_ShowText, ui.textBrowser, &QTextBrowser::append);
	connect(warpper, &Warpper::sig_ReportState, this,&CrystalSoftwarePackage::DisplayState);
	
	connect(ui.pushButton_pause, &QPushButton::clicked, warpper, &Warpper::Pause);
	connect(ui.pushButton_load, &QPushButton::clicked, this, &CrystalSoftwarePackage::LoadFiles);
	connect(ui.pushButton_run, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
	ui.pushButton_run->setEnabled(false);

	warpper = new Warpper;
	algs.push_back(warpper);
	connect(warpper, &Warpper::sig_ShowImg, ui.label_2, &QLabel::setPixmap);
	connect(warpper, &Warpper::sig_ShowText, ui.textBrowser_2, &QTextBrowser::append);
	connect(warpper, &Warpper::sig_ReportState, this, &CrystalSoftwarePackage::DisplayState2);
	connect(ui.pushButton_pause_2, &QPushButton::clicked, warpper, &Warpper::Pause);

	connect(ui.pushButton_load_2, &QPushButton::clicked, this, &CrystalSoftwarePackage::LoadFiles2);
	connect(ui.pushButton_run_2, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg2);
	ui.pushButton_run_2->setEnabled(false);
}

CrystalSoftwarePackage::~CrystalSoftwarePackage()
{
	for (auto alg : algs)
		delete alg;
}

void CrystalSoftwarePackage::LoadFiles()
{
	QString filename = QFileDialog::getOpenFileName(this, tr(u8"打开文件"), ".", tr(u8"图片文件(*.jpg *.jpeg *.png *.bmp)"));
	if( false==filename.isEmpty())
	{
		QImage qimg(filename);
		qDebug() << __FUNCTION__ << '[' << algs[0]->LoadSrc(Mat(qimg.height(), qimg.width(), CV_8UC4, qimg.bits())) << ']';
		ui.pushButton_run->setEnabled(true);
		ui.label->setPixmap(QPixmap::fromImage(qimg));
	}
	else
	{
#ifdef _DEBUG
		QImage qimg(u8"..\\Crystal Software Package\\resource\\testpic.jpg");
		qDebug() << __FUNCTION__ << '[' << algs[0]->LoadSrc(Mat(qimg.height(), qimg.width(), CV_8UC4, qimg.bits())) << ']';
		ui.pushButton_run->setEnabled(true);
		ui.label->setPixmap(QPixmap::fromImage(qimg));
#endif // _DEBUG
	}
	return;
}

void CrystalSoftwarePackage::RunAlg()
{
	if (algs[0]->IsRun() == true) 
	{
		qDebug() << "running...";
		algs[0]->Stop();
		return;
	}
	//ui.pushButton_run->setText("暂停");
	//disconnect(ui.pushButton_run, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
	try {
		ui.pushButton_run->setText(u8"停止");
		qDebug() << "start...";
		//alg->run();
		algs[0]->start();
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

void CrystalSoftwarePackage::DisplayState(State_E state)
{
	ui.textBrowser->append(State_Str[static_cast<int>(state)]);
}


void CrystalSoftwarePackage::LoadFiles2()
{
	QString filename = QFileDialog::getOpenFileName(this, tr(u8"打开文件"), ".", tr(u8"图片文件(*.jpg *.jpeg *.png *.bmp)"));
	if (false == filename.isEmpty())
	{
		QImage qimg(filename);
		qDebug() << __FUNCTION__ << '[' << algs[1]->LoadSrc(Mat(qimg.height(), qimg.width(), CV_8UC4, qimg.bits())) << ']';
		ui.pushButton_run_2->setEnabled(true);
		ui.label_2->setPixmap(QPixmap::fromImage(qimg));
	}
	else
	{
#ifdef _DEBUG
		QImage qimg(u8"..\\Crystal Software Package\\resource\\testpic.jpg");
		qDebug() << __FUNCTION__ << '[' << algs[1]->LoadSrc(Mat(qimg.height(), qimg.width(), CV_8UC4, qimg.bits())) << ']';
		ui.pushButton_run_2->setEnabled(true);
		ui.label_2->setPixmap(QPixmap::fromImage(qimg));
#endif // _DEBUG
	}
	return;
}

void CrystalSoftwarePackage::RunAlg2()
{
	if (algs[1]->IsRun() == true)
	{
		qDebug() << "running...";
		algs[1]->Stop();
		return;
	}
	//ui.pushButton_run->setText("暂停");
	//disconnect(ui.pushButton_run, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
	try {
		ui.pushButton_run_2->setText(u8"停止");
		qDebug() << "start...";
		//alg->run();
		algs[1]->start();
		qDebug() << "over...";
	}
	catch (std::system_error e)
	{
		qDebug() << e.what();
	}
	//connect(ui.pushButton_run, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
}

void CrystalSoftwarePackage::PauseAlg2(bool ispause)
{

}

void CrystalSoftwarePackage::DisplayState2(State_E state)
{
	ui.textBrowser_2->append(State_Str[static_cast<int>(state)]);
}