#include "stdafx.h"
#include <memory>
#include <QTimer>
#include <QDebug>
#include <QMessagebox>
#include <QFileDialog>

#include "CrystalSoftwarePackage.h"
//#include "WarperTable.h"
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

	Warpper*warpper = new Warpper(Create_Alg_Simpletest);
	algs.push_back(warpper);
	connect(warpper, &Warpper::sig_ShowImg, ui.label, &QLabel::setPixmap);
	connect(warpper, &Warpper::sig_ShowText, ui.textBrowser, &QTextBrowser::append);
	connect(warpper, &Warpper::sig_ReportState, this,&CrystalSoftwarePackage::DisplayState);
	
	connect(ui.pushButton_pause, &QPushButton::clicked, warpper, &Warpper::Pause);
	connect(ui.pushButton_load, &QPushButton::clicked, this, &CrystalSoftwarePackage::LoadFiles);
	connect(ui.pushButton_run, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
	ui.pushButton_run->setEnabled(false);

	warpper = new Warpper(Create_Alg_Complextest);
	algs.push_back(warpper);
	connect(warpper, &Warpper::sig_ShowImg, ui.label_2, &QLabel::setPixmap);
	connect(warpper, &Warpper::sig_ShowText, ui.textBrowser_2, &QTextBrowser::append);
	connect(warpper, &Warpper::sig_ReportState, this, &CrystalSoftwarePackage::DisplayState);
	connect(ui.pushButton_pause_2, &QPushButton::clicked, warpper, &Warpper::Pause);

	connect(ui.pushButton_load_2, &QPushButton::clicked, this, &CrystalSoftwarePackage::LoadFiles);
	connect(ui.pushButton_run_2, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
	ui.pushButton_run_2->setEnabled(false);
	qDebug() << sizeof(Mat) 
		<< sizeof(std::vector<int>) 
		<< sizeof(std::vector<Mat>)
		<< sizeof(std::string)
		<< sizeof(std::map<int, string>)
		<< sizeof(std::map<string, Mat>); //96 32 32 40 24 24
}

CrystalSoftwarePackage::~CrystalSoftwarePackage()
{
	for (auto alg : algs)
		delete alg;
}

void CrystalSoftwarePackage::LoadFiles()
{
	QString filename = QFileDialog::getOpenFileName(this, tr(u8"打开文件"), ".\\resource", tr(u8"图片文件(*.jpg *.jpeg *.png *.bmp)"));
	QImage qimg(filename);
	if (false == filename.isEmpty())
		QImage qimg(filename);
	else
		return;
		//QImage qimg(u8".\\Crystal Software Package\\resource\\testpic.jpg");
	
	Warpper*warper = nullptr;
	if ((size_t)sender() == (size_t)ui.pushButton_load)
	{
		algs[0]->LoadSrc(Mat(qimg.height(), qimg.width(), CV_8UC4, qimg.bits()));
		ui.pushButton_run->setEnabled(true);
		ui.label->setPixmap(QPixmap::fromImage(qimg));
	}
	else if ((size_t)sender() == (size_t)ui.pushButton_load_2)
	{
		algs[1]->LoadSrc(Mat(qimg.height(), qimg.width(), CV_8UC4, qimg.bits()));
		ui.pushButton_run_2->setEnabled(true);
		ui.label_2->setPixmap(QPixmap::fromImage(qimg));
	}

	return;
}

void CrystalSoftwarePackage::RunAlg()
{
	Warpper*warper = nullptr;
	if ((size_t)sender() == (size_t)ui.pushButton_run)
		warper=algs[0];
	else if ((size_t)sender() == (size_t)ui.pushButton_run_2)
		warper = algs[1];
	if (warper->IsRun() == true)
	{
		qDebug() << "running...";
		warper->Stop();
		return;
	}
	//ui.pushButton_run->setText("暂停");
	//disconnect(ui.pushButton_run, &QPushButton::clicked, this, &CrystalSoftwarePackage::RunAlg);
	try {
		qDebug() << "start...";
		//alg->run();
		warper->start();
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
	if ((size_t)sender() == (size_t)algs[0])
		ui.textBrowser->append(State_Str[static_cast<int>(state)]);
	else if ((size_t)sender() == (size_t)algs[1])
		ui.textBrowser_2->append(State_Str[static_cast<int>(state)]);
}
