#include "stdafx.h"
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

	alg = Create_Interface_Alg(this);
	alg->LoadSrc(Mat());
}

CrystalSoftwarePackage::~CrystalSoftwarePackage()
{
	delete alg;
}

bool CrystalSoftwarePackage::ShowImg(const cv::InputArray img)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CrystalSoftwarePackage::TextOut(std::string text)
{
	ui.label->setText("OK");
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
