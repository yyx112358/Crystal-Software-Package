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

	algs.push_back(new Warpper);
	connect(algs[0], &Warpper::sig_ShowImg, ui.label, &QLabel::setPixmap);
	connect(algs[0], &Warpper::sig_ShowText, ui.textBrowser, &QTextBrowser::append);
	connect(algs[0], &Warpper::sig_ReportState, this,&CrystalSoftwarePackage::DisplayState);
	connect(ui.pushButton_pause, &QPushButton::clicked, algs[0], &Warpper::Pause);
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

