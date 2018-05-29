#pragma once
#include "qthread.h"
#include "..\Algorithm\AlgorithmControler.h"

class AlgorithmControler_Thread :
	public QThread,protected AlgorithmControler
{
	Q_OBJECT

public:
	AlgorithmControler_Thread(Interface_GUI*gui):AlgorithmControler(gui){}
	virtual ~AlgorithmControler_Thread(){}

private:



};

