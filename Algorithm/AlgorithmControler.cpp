// Algorithm.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"

#include "AlgorithmControler.h"
#include <opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

bool AlgorithmControler::Init(const Interface_GUI*gui)
{
	//CHANGE_STATE(State_E::init_pre);
	if (gui == nullptr) 
	{
		CV_Assert(gui != nullptr);
		return false;
	}
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
	ChangeState(State_E::reset_pre);
	LOCKRUN;
	LOCKWRITE;
	ChangeState(State_E::reset_ing);
	_is_pause = false;
	_is_stop = false;
	_srcimg.release();
	_dstimg.release();
	ChangeState(State_E::reset_end);
	return true;
}

bool AlgorithmControler::Release()
{
	ChangeState(State_E::release_pre);
	Stop();
	while (IsRun() == true || IsWrite() == true);
	ChangeState(State_E::release_ing);
	_is_init = false;
	Reset();
	ChangeState(State_E::release_end);
	_gui = nullptr;
	//_init_mutex.unlock();
	return true;
}
bool AlgorithmControler::LoadSrc(cv::InputArray src)
{
	ChangeState(State_E::load_pre);
	if (IsWrite() == true)
		return false;
	LOCKWRITE;
	ChangeState(State_E::load_ing);
	_srcimg = src.getMat().clone();
	_gui->ShowText("OK");
	ChangeState(State_E::load_end);
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
bool AlgorithmControler::LoadParam(std::map<std::string, Algparam>&params)
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

bool AlgorithmControler::Pause(bool ispause)
{
	ChangeState(State_E::pause_pre);
	_is_pause = ispause;
	return true;
}
bool AlgorithmControler::Stop()
{
	ChangeState(State_E::stop_pre);
	_is_stop = true;
	_is_pause = false;
	ChangeState(State_E::stop_ing);
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






