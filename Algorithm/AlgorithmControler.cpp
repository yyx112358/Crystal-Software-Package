// Algorithm.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"

#include "AlgorithmControler.h"
#include <opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

std::mutex _write_mutex, _run_mutex, _init_mutex;
#define TRYRUN AlgLock_t lockrun(_run_mutex);
#define TRYWRITE AlgLock_t lockwrite(_write_mutex);

Interface_Alg* Create_Interface_Alg(const Interface_GUI*gui)
{
	return new AlgorithmControler(gui);
}

bool AlgorithmControler::Init(const Interface_GUI*gui)
{
	if (IsInit() == true)
		Release();
	
	_gui = const_cast<Interface_GUI*>(gui);
	_gui->ShowText("====Algorithum Init [OK]====");
	//_init_mutex.lock();
	_is_init = true;
	return true;
}

bool AlgorithmControler::Release()
{
	TRYRUN;
	TRYWRITE;
	_is_init = false;
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

bool AlgorithmControler::LoadSrc_Async(cv::InputArray src)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::LoadSetting()
{
	throw std::logic_error("The method or operation is not implemented.");
}
bool AlgorithmControler::LoadSetting_Async()
{
	throw std::logic_error("The method or operation is not implemented.");
}
bool AlgorithmControler::LoadParam()
{
	throw std::logic_error("The method or operation is not implemented.");
}
bool AlgorithmControler::LoadParam_Async()
{
	throw std::logic_error("The method or operation is not implemented.");
}
bool AlgorithmControler::ReadRst(cv::OutputArray rst)
{
	throw std::logic_error("The method or operation is not implemented.");
}
bool AlgorithmControler::ReadRst_Async(cv::OutputArray rst)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::ReadParam()
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
		char str[20];
		sprintf_s<sizeof(str)>(str, "%d", i);
		_gui->ShowText(str);
		_gui->ShowImg(tmp);
		_gui->wait(40);
		//Sleep(40);
		tmp *= 1.02;
	}
	return true;
}

bool AlgorithmControler::RunOnce()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::Pause()
{
	throw std::logic_error("The method or operation is not implemented.");
}
bool AlgorithmControler::Resume()
{
	throw std::logic_error("The method or operation is not implemented.");
}
bool AlgorithmControler::Stop()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::Terminate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::Train()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::IsInit()const
{
	return _is_init;
}

bool AlgorithmControler::IsRun()const
{
	try
	{
		TRYRUN;
		return false;
	}
	catch (std::system_error e)
	{
		_gui->ShowText(e.what());
		return true;
	}
}







