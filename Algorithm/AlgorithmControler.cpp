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
	CV_Assert(gui->IsInit() == true);
	_gui = const_cast<Interface_GUI*>(gui);
	return true;
}

bool AlgorithmControler::Release()
{
	_gui = nullptr;
	return true;
}

bool AlgorithmControler::LoadSrc(cv::InputArray src)
{
	_srcimg = src.getMat();
	_gui->ShowText("OK");

	for(auto i=0;i<50;i++)
	{
		_gui->ShowImg(_srcimg);
		_srcimg += 1;
	}
	return true;
}

bool AlgorithmControler::LoadSetting()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::LoadParam()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::ReadRst(cv::OutputArray rst)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::ReadParam()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::ReadState()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::Run()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::RunOnce()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::Pause()
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
	throw std::logic_error("The method or operation is not implemented.");
}

bool AlgorithmControler::IsBusy()const
{
	throw std::logic_error("The method or operation is not implemented.");
}
