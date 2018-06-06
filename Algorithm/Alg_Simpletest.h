#pragma once
#include "AlgorithmControler.h"
class ALGORITHM_API Alg_Simpletest :
	public AlgorithmControler
{
public:
	Alg_Simpletest(Interface_GUI*gui):AlgorithmControler(gui){}
	virtual ~Alg_Simpletest() {}

	virtual bool Run() override;
};

