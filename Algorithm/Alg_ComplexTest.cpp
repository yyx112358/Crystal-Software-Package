#include "stdafx.h"
#include "Alg_ComplexTest.h"
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

bool Alg_ComplexTest::Run()
{
	ChangeState(State_E::run_pre);
	LOCKRUN;
	//TODO
	Mat tmp = _srcimg.clone();
	ChangeState(State_E::run_ing);

	for (auto i = 0; i < 1; i++)
	{
		ChangeState(State_E::iter_pre);
		if (_is_stop == true)//¼ì²éÊÇ·ñÍ£Ö¹
		{
			ChangeState(State_E::stop_end);
			break;
		}
		if (_is_pause == true)
		{
			ChangeState(State_E::pause_ing);
			while (_is_pause == true)//ÔÝÍ£Ê±×èÈû
				_gui->wait(1);
			ChangeState(State_E::pause_end);
		}
		ChangeState(State_E::iter_ing);

		//TODO
		double th = _params["threshold"].d();
		threshold(tmp, tmp, th, 255, cv::THRESH_BINARY);
		_gui->ShowImg(tmp);

		ChangeState(State_E::iter_end);
	}
	//TODO
	if (State_E::stop_end != _sta)
		ChangeState(State_E::run_end);
	_is_stop = false;
	_is_pause = false;

	return true;
}

bool Alg_ComplexTest::Init(const Interface_GUI*gui)
{
	AlgorithmControler::Init(gui);
	//if (_params.find("threshold") != _params.cend())
	//	_params["threshold"] = 50;
	return true;
}
