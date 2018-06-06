#include "stdafx.h"
#include "AlgorithmTable.h"
#include "AlgorithmControler.h"
#include "Alg_ComplexTest.h"

// AlgorithmControler* Create_AlgorithmControler(Interface_GUI*gui)
// {
// 	return new AlgorithmControler(gui);
// }

AlgorithmControler* Create_Alg_Simpletest(Interface_GUI*gui)
{
	return new Alg_Simpletest(gui);
}

ALGORITHM_API AlgorithmControler* Create_Alg_Complextest(Interface_GUI*gui)
{
	return new Alg_ComplexTest(gui);
}
