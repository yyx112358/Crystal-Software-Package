// Algorithm.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"

#include "AlgorithmControler.h"
#include <opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Interface_Alg* Create_Interface_Alg(const Interface_GUI*gui)
{
	return new AlgorithmControler(gui);
}

bool AlgorithmControler::Init(const Interface_GUI*gui)
{
	if (IsInit() == true)
		Release();
	_gui = const_cast<Interface_GUI*>(gui);

	//Reset();
	TRYRUN;
	TRYWRITE;
	_is_pause = false;
	_is_stop = false;
	_srcimg.release();
	_dstimg.release();
	_is_init = true;
	_gui->ShowText("====Algorithum Init [OK]====");
	return true;
}

bool AlgorithmControler::Reset()
{
// 	TRYRUN;
// 	TRYWRITE;
// 	_is_pause = false;
// 	_is_stop = false;
// 	_srcimg.release();
// 	_dstimg.release();
	return true;
}

bool AlgorithmControler::Release()
{
	TRYRUN;
	TRYWRITE;
	_is_init = false;
	Reset();
	_gui = nullptr;
	//_init_mutex.unlock();
	return true;
}
bool AlgorithmControler::LoadSrc(cv::InputArray src)
{
	TRYRUN;
	TRYWRITE;
	_srcimg = src.getMat().clone();
	_gui->ShowText("OK");

	return true;
}

bool AlgorithmControler::LoadSetting()
{
	TRYRUN;
	TRYWRITE;
	throw std::logic_error("The method or operation is not implemented.");
}
bool AlgorithmControler::LoadParam()
{
	TRYRUN;
	TRYWRITE;
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::ReadRst(cv::OutputArray rst)
{
	TRYRUN;
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::ReadParam()const
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::ReadState()const
{
	throw std::logic_error("The method or operation is not implemented.");
}

//#include <windows.h>
bool AlgorithmControler::Run()
{
	TRYRUN;
	Mat tmp = _srcimg.clone();
	for (auto i = 0; i < 50; i++)
	{
		if(_is_stop==true)//检查是否停止
			break;
		while (_is_pause == true)//暂停时阻塞
			_gui->wait(1);

		char str[20];
		sprintf_s<sizeof(str)>(str, "%d", i);
		_gui->ShowText(str);
		_gui->ShowImg(tmp);
		//_gui->wait(40);
		//Sleep(40);
		int t = 0xFFFFFF;
		while (t--);
		tmp *= 1.02;
	}
	_is_stop = false;
	_is_pause = false;
	return true;
}

bool AlgorithmControler::RunOnce()
{
	TRYRUN;
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::Pause()
{
	_is_pause = true;
	return true;
}
bool AlgorithmControler::Resume()
{
	_is_pause = false;
	return true;
}
bool AlgorithmControler::Stop()
{
	_is_stop = true;
	return true;
}

bool AlgorithmControler::IsInit()const
{
	return _is_init;
}

bool AlgorithmControler::IsRun()
{
	try
	{
		TRYRUN;
		return false;
	}
	catch (std::system_error e)
	{
#ifdef _DEBUG
		_gui->ShowText(e.what());
#endif // _DEBUG
		return true;
	}
}







