#include "stdafx.h"
#include "CrystalSoftwarePackage.h"
#include <QMetaType>

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

	connect(this, SIGNAL(sig_ShowText(QString)), ui.label, SLOT(setText(QString)));
	connect(ui.pushButton_run, SIGNAL(clicked()), this, SLOT(LoadFiles()));
	connect(this, SIGNAL(sig_ShowImg(QPixmap)), ui.label, SLOT(setPixmap(QPixmap)));

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
}

bool CrystalSoftwarePackage::ShowImg(const cv::InputArray img)
{
	Mat tmp = img.getMat();
	CV_Assert(tmp.type() == CV_8UC4);
	emit sig_ShowImg(QPixmap::fromImage(QImage(tmp.data, tmp.cols, tmp.rows, QImage::Format_ARGB32)));
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

bool CrystalSoftwarePackage::ReportError(std::string msg)
{
	throw std::logic_error("The method or operation is not implemented.");
}
