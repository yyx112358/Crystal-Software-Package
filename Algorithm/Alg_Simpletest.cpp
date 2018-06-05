#include "stdafx.h"
#include "Alg_Simpletest.h"

using namespace std;
using namespace cv;

bool Alg_Simpletest::Run()
{
	ChangeState(State_E::run_pre);
	LOCKRUN;
	//TODO
	Mat tmp = _srcimg.clone();
	ChangeState(State_E::run_ing);
	for (auto i = 0; i < 50; i++)
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
		aout << i;
		_gui->ShowImg(tmp);
		//_gui->wait(40);
		//Sleep(40);
		int t = 0x1FFFFFF;
		while (t--);
		tmp *= 1.02;
		ChangeState(State_E::iter_end);
	}
	//TODO
	if (State_E::stop_end != _sta)
		ChangeState(State_E::run_end);
	_is_stop = false;
	_is_pause = false;

	return true;
}
