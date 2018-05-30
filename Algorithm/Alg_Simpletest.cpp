#include "stdafx.h"
#include "Alg_Simpletest.h"

using namespace std;
using namespace cv;

bool Alg_Simpletest::Run()
{
	CHANGE_STATE(State_E::run_pre);
	LOCKRUN;
	//TODO
	Mat tmp = _srcimg.clone();
	CHANGE_STATE(State_E::run_ing);
	for (auto i = 0; i < 50; i++)
	{
		CHANGE_STATE(State_E::iter_pre);
		if (_is_stop == true)//����Ƿ�ֹͣ
		{
			CHANGE_STATE(State_E::stop_end);
			break;
		}
		if (_is_pause == true)
		{
			CHANGE_STATE(State_E::pause_ing);
			while (_is_pause == true)//��ͣʱ����
				_gui->wait(1);
			CHANGE_STATE(State_E::pause_end);
		}
		CHANGE_STATE(State_E::iter_ing);

		//TODO
		aout << i;
		_gui->ShowImg(tmp);
		//_gui->wait(40);
		//Sleep(40);
		int t = 0x1FFFFFF;
		while (t--);
		tmp *= 1.02;
		CHANGE_STATE(State_E::iter_end);
	}
	//TODO
	if (State_E::stop_end != _sta)
		CHANGE_STATE(State_E::run_end);
	_is_stop = false;
	_is_pause = false;

	return true;
}
