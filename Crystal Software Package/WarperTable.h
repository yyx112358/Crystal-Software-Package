#pragma once
#include "Warpper.h"
#include "..\Algorithm\AlgorithmTable.h"

class Warper_Simpletest
	:public Warpper,public Alg_Simpletest
{
public:
	Warper_Simpletest():Alg_Simpletest(this){}
	virtual ~Warper_Simpletest(){}
};
