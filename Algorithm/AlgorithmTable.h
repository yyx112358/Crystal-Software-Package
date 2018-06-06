#pragma once
#include "Alg_Simpletest.h"

typedef AlgorithmControler*(*CreateAlgFunc)(Interface_GUI*gui);

//ALGORITHM_API AlgorithmControler*Create_AlgorithmControler(Interface_GUI*gui);
ALGORITHM_API AlgorithmControler*Create_Alg_Simpletest(Interface_GUI*gui);
ALGORITHM_API AlgorithmControler*Create_Alg_Complextest(Interface_GUI*gui);