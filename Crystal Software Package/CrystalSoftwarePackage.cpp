#include "stdafx.h"
#include "CrystalSoftwarePackage.h"
#include <QMetaType>
#include <QTimer>
#include <memory>

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\Algorithm.lib")
#include <QDebug>
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
	qRegisterMetaType<Mat>("Mat");

	alg = Create_Interface_Alg(this);
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
		alg->Run();
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

bool CrystalSoftwarePackage::ShowImg(const cv::InputArray img)
{
	Mat tmp = img.getMat();
	CV_Assert(tmp.type() == CV_8UC4);
//注意这里必须要进行复制，否则本函数结束后对应Mat tmp会被释放，使得其对应数据区data变成野指针
//而从指针生成的QImage也不会进行复制，所以当重绘时候会调用到QImage对应的被Mat tmp释放的野指针造成崩溃
	QPixmap qpix = QPixmap::fromImage(QImage(tmp.data, tmp.cols, tmp.rows, QImage::Format_ARGB32))
		.copy(0, 0, tmp.cols, tmp.rows);
	emit sig_ShowImg(qpix);
	return true;
}

bool CrystalSoftwarePackage::ShowText(std::string text)
{
	qDebug() << text.c_str();
	emit sig_ShowText(QString(text.c_str()));
	return true;
}


bool CrystalSoftwarePackage::ReportProgress(int progress)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CrystalSoftwarePackage::SaveData(const cv::InputArray data)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CrystalSoftwarePackage::IsInit() const
{
	return true;
}

bool CrystalSoftwarePackage::IsBusy() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CrystalSoftwarePackage::wait(int msec) const
{
	QEventLoop eventloop;
	QTimer::singleShot(msec, &eventloop, SLOT(quit())); //wait
	eventloop.exec();

	return true;
}

bool CrystalSoftwarePackage::ReportError(std::string msg)
{
	throw std::logic_error("The method or operation is not implemented.");
}
