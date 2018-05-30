#include "stdafx.h"
#include "Warpper.h"
#include <opencv.hpp>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QEventLoop>
#include <QMetaType>

using namespace cv;


bool Warpper::ShowImg(const cv::InputArray img)
{
	cv::Mat tmp = img.getMat();// .getMat();
	CV_Assert(tmp.type() == CV_8UC4);
	//注意这里必须要进行复制，否则本函数结束后对应Mat tmp会被释放，使得其对应数据区data变成野指针
	//而从指针生成的QImage也不会进行复制，所以当重绘时候会调用到QImage对应的被Mat tmp释放的野指针造成崩溃
	QPixmap qpix = QPixmap::fromImage(QImage(tmp.data, tmp.cols, tmp.rows, QImage::Format_ARGB32))
		.copy(0, 0, tmp.cols, tmp.rows);
	emit sig_ShowImg(qpix);
	return true;
}

bool Warpper::ShowText(std::string text)
{
	emit sig_ShowText(QString(text.c_str()));
	return true;
}

bool Warpper::ReportState(State_E state)
{
	emit sig_ReportState(state);
	//emit sig_ReportState(State_Str[static_cast<int>(state)]);
	return true;
}

bool Warpper::ReportProgress(int progress)
{
	emit sig_ReportProgress(progress);
	return true;
}

bool Warpper::ReportError(std::string msg)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Warpper::SaveData(const cv::InputArray data)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Warpper::IsBusy() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Warpper::wait(int msec /*= 0*/) const
{
// 	QEventLoop eventloop;
// 	QTimer::singleShot(msec, &eventloop, SLOT(quit())); //wait
// 	eventloop.exec();
	msleep(msec);
	return true;
}

