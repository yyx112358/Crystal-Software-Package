#include "stdafx.h"
#include "Warpper.h"
#include <opencv.hpp>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QEventLoop>
#include <QMetaType>

using namespace cv;

Warpper::Warpper() :AlgorithmControler(this)
{
	qRegisterMetaType<State_E>("State_E");
	/*aout << "====Algorithm Init [OK]====";*/
}

void Warpper::run()
{
	AlgorithmControler::Run();
// 	cv::Mat img = _srcimg.clone();
// 	for (auto i = 0; i < 50; i++)
// 	{
// 		if (_is_stop == true)//����Ƿ�ֹͣ
// 			break;
// 		while (_is_pause == true)//��ͣʱ����
// 			_gui->wait(1);
// 
// 		char str[20];
// 		sprintf_s<sizeof(str)>(str, "%d", i);
// 		_gui->ShowText(str);
// 		
// 		_gui->ShowImg(tmp);
// 		//_gui->wait(40);
// 		//Sleep(40);
// 		int t = 0xFFFFFF;
// 		while (t--);
// 		tmp *= 1.02;
// 	}
// 	_is_stop = false;
// 	_is_pause = false;
}


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

