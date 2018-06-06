#pragma once
#include "AlgorithmControler.h"
class Alg_ComplexTest :
	public AlgorithmControler
{
public:
	Alg_ComplexTest(Interface_GUI*gui) :AlgorithmControler(gui) {}
	virtual ~Alg_ComplexTest() {}

	virtual bool Run() override;

	virtual bool Init(const Interface_GUI*gui) override;

};

