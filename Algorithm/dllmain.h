#pragma once
#ifdef ALGORITHM_EXPORTS
#define ALGORITHM_API __declspec(dllexport)
#else
#define ALGORITHM_API __declspec(dllimport)
#endif