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
	//ע���������Ҫ���и��ƣ����򱾺����������ӦMat tmp�ᱻ�ͷţ�ʹ�����Ӧ������data���Ұָ��
	//����ָ�����ɵ�QImageҲ������и��ƣ����Ե��ػ�ʱ�����õ�QImage��Ӧ�ı�Mat tmp�ͷŵ�Ұָ����ɱ���
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

