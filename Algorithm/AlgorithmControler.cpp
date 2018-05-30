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
	//CHANGE_STATE(State_E::init_pre);
	if (IsInit() == true)
		Release();
	_gui = const_cast<Interface_GUI*>(gui);

	//Reset();
	LOCKRUN;
	LOCKWRITE;
	_is_pause = false;
	_is_stop = false;
	_srcimg.release();
	_dstimg.release();
	_is_init = true;
	return true;
}

bool AlgorithmControler::Reset()
{
	CHANGE_STATE(State_E::reset_pre);
	LOCKRUN;
	LOCKWRITE;
	CHANGE_STATE(State_E::reset_ing);
	_is_pause = false;
	_is_stop = false;
	_srcimg.release();
	_dstimg.release();
	CHANGE_STATE(State_E::reset_end);
	return true;
}

bool AlgorithmControler::Release()
{
	CHANGE_STATE(State_E::release_pre);
	Stop();
	while (IsRun() == true || IsWrite() == true);
	CHANGE_STATE(State_E::release_ing);
	_is_init = false;
	Reset();
	CHANGE_STATE(State_E::release_end);
	_gui = nullptr;
	//_init_mutex.unlock();
	return true;
}
bool AlgorithmControler::LoadSrc(cv::InputArray src)
{
	CHANGE_STATE(State_E::load_pre);
	if (IsWrite() == true)
		return false;
	LOCKWRITE;
	CHANGE_STATE(State_E::load_ing);
	_srcimg = src.getMat().clone();
	_gui->ShowText("OK");
	CHANGE_STATE(State_E::load_end);
	return true;
}

bool AlgorithmControler::LoadSetting()
{
	if (IsWrite() == true)
		return false;
	LOCKRUN;
	LOCKWRITE;
	throw std::logic_error("The method or operation is not implemented.");
}
bool AlgorithmControler::LoadParam()
{
	if (IsWrite() == true)
		return false;
	LOCKRUN;
	LOCKWRITE;
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::ReadRst(cv::OutputArray rst)
{
	LOCKRUN;
	throw std::logic_error("The method or operation is not implemented.");
	return !IsRun();//正在运行时返回false，说明当前结果不一定有效
}

bool AlgorithmControler::ReadParam()const
{
	throw std::logic_error("The method or operation is not implemented.");
}

State_E AlgorithmControler::ReadState()const
{
	return _sta;
}

//#include <windows.h>
bool AlgorithmControler::Run()
{
	CHANGE_STATE(State_E::run_pre);
	LOCKRUN;
	Mat tmp = _srcimg.clone();
	CHANGE_STATE(State_E::run_ing);
	for (auto i = 0; i < 50; i++)
	{
		CHANGE_STATE(State_E::iter_pre);
		if(_is_stop==true)//检查是否停止
		{
			CHANGE_STATE(State_E::stop_end);
			break;
		}
		if (_is_pause == true)
		{
			CHANGE_STATE(State_E::pause_ing);
			while (_is_pause == true)//暂停时阻塞
				_gui->wait(1);
			CHANGE_STATE(State_E::pause_end);
		}
		CHANGE_STATE(State_E::iter_ing);

// 		char str[20];
// 		sprintf_s<sizeof(str)>(str, "%d", i);
// 		_gui->ShowText(str);
		aout << i;
		_gui->ShowImg(tmp);
		//_gui->wait(40);
		//Sleep(40);
		int t = 0x1FFFFFF;
		while (t--);
		tmp *= 1.02;
		CHANGE_STATE(State_E::iter_end);
	}
	if(State_E::stop_end!=_sta)
		CHANGE_STATE(State_E::run_end);
	_is_stop = false;
	_is_pause = false;
	
	return true;
}

bool AlgorithmControler::Pause(bool ispause)
{
	CHANGE_STATE(State_E::pause_pre);
	_is_pause = ispause;
	return true;
}
bool AlgorithmControler::Stop()
{
	CHANGE_STATE(State_E::stop_pre);
	_is_stop = true;
	_is_pause = false;
	CHANGE_STATE(State_E::stop_ing);
	return true;
}

bool AlgorithmControler::IsInit()const
{
	return _is_init;
}

bool AlgorithmControler::IsRun()
{
	bool b = _run_mutex.try_lock();
	if (true == b)
	{
		_run_mutex.unlock();
		return false;
	}
	else
	{
		return true;
	}
//单线程下用这个
// 	try
// 	{
// 		LOCKRUN;
// 		return false;
// 	}
// 	catch (std::system_error e)
// 	{
// #ifdef _DEBUG
// 		_gui->ShowText(e.what());
// #endif // _DEBUG
// 		return true;
// 	}
}

bool AlgorithmControler::IsWrite()
{
	bool b = _write_mutex.try_lock();
	if (true == b)
	{
		_write_mutex.unlock();
		return false;
	}
	else
	{
		return true;
	}
//单线程下用这个
// 	try
// 	{
// 		LOCKWRITE;
// 		return false;
// 	}
// 	catch (std::system_error e)
// 	{
// #ifdef _DEBUG
// 		_gui->ShowText(e.what());
// #endif // _DEBUG
// 		return true;
// 	}
}






