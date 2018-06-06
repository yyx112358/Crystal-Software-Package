#pragma once
#include "Interface.h"
#include <sstream>
/*	�Զ��������
*	�÷�������cout����Ҫ������AlgorithmControler��Init()�����е���
*/
class ALGORITHM_API AlgOutstream
{
public:
	AlgOutstream(const Interface_GUI*gui) { _gui = const_cast<Interface_GUI*>(gui); }
	AlgOutstream(Interface_GUI*gui) :_gui(gui) {}
	friend AlgOutstream& operator << (AlgOutstream&aos, std::string&str) { aos._gui->ShowText(str); return aos; }
	friend AlgOutstream& operator << (AlgOutstream&aos, const char *in) { aos._gui->ShowText(in); return aos; }
	template<typename Tp>
	friend AlgOutstream& operator << (AlgOutstream&aos, Tp in) { aos.ss.str(""); aos.ss << in; aos._gui->ShowText(aos.ss.str()); return aos; }
private:
	Interface_GUI*_gui = nullptr;
	std::ostringstream ss;
};