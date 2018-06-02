#pragma once
#include <vector>
#include <string>

#include "dllmain.h"
#include <opencv2/core/mat.hpp>
#include <unordered_map>

//using namespace cv;
/*参数表
* 根据需求简化得到的QVariant，可用同一个变量存储各种类型变量，并进行反射
* 支持int,double,string,Point2d,Mat及其对应的vector
* 不支持其它自定义变量，创建之后不能改变存储类型否则报错
* 主要用于存储，不建议直接用来计算
*/
class Algparam
{
public:
	enum class E_TYPE :unsigned char
	{
		INT_T = 'i',
		VINT_T = 'i' + 0x80,
		DOUBLE_T = 'd',
		VDOUBLE_T = 'd' + 0x80,
		STRING_T = 's',
		VSTRING_T = 's' + 0x80,
	}type;
	union
	{
		int i;
		std::vector<int>*vi;
		double d;
		std::vector<double>*vd;
		std::string*s;
		std::vector<std::string>*vs;
	}data;


	//TODO:判定初始化和共享问题
	//初始化函数
	Algparam(int in) { type = E_TYPE::INT_T; data.i = in; }
	Algparam(std::vector<int> &in) { type = E_TYPE::VINT_T; *data.vi = in; }
	Algparam(double in) { type = E_TYPE::DOUBLE_T; data.d = in; }
	Algparam(std::vector<double> &in) { type = E_TYPE::VDOUBLE_T; *data.vd = in; }
	Algparam(std::string &in) { type = E_TYPE::STRING_T; data.s = new std::string(in); }
	Algparam(std::vector<std::string> &in) { type = E_TYPE::VSTRING_T; *data.vs = in; }
	//复制构造函数
	Algparam(Algparam&rhs);//全部深复制，开销较大但安全
	Algparam operator =(Algparam&);
	Algparam& operator =(int in) { assert(type == E_TYPE::INT_T); data.i = in; return*this; }
	Algparam& operator =(std::vector<int> &in) { assert(type == E_TYPE::VINT_T); *data.vi = in; return*this; }
	Algparam& operator =(double in) { assert(type == E_TYPE::DOUBLE_T); data.d = in; return*this; }
	Algparam& operator =(std::vector<double> &in) { assert(type == E_TYPE::VDOUBLE_T); *data.vd = in; return*this; }
	Algparam& operator =(std::string &in) { assert(type == E_TYPE::STRING_T); *data.s = in; return*this; }
	Algparam& operator =(std::vector<std::string> &in) { assert(type == E_TYPE::VSTRING_T); *data.vs = in; return*this; }

	void release()
	{
		if (data.vi != nullptr)
		{
			switch (type)
			{
			case Algparam::E_TYPE::VINT_T:
				delete data.vi;
				break;
			case Algparam::E_TYPE::VDOUBLE_T:
				delete data.vd;
				break;
			case Algparam::E_TYPE::STRING_T:
				delete data.s;
				break;
			case Algparam::E_TYPE::VSTRING_T:
				delete data.vs;
				break;
			default:
				break;
			}
		}
		data.vi = nullptr;
	}

	~Algparam()
	{
		release();
	}

	Algparam&add(int in);

	//类型转换函数
	inline int i() { assert(type == E_TYPE::INT_T); return data.i; }
	//inline operator int() { return i(); }
	inline std::vector<int>&vi() { return *data.vi; }

	inline double d() { assert(type == E_TYPE::DOUBLE_T); return data.d; }
	//operator double() { return d(); }
	inline std::string& s() { return *data.s; }

	inline std::vector<double>&vd() { return *data.vd; }
	inline std::vector<std::string>&vs() { return *data.vs; }

	//TODO:检查复制时是浅复制还是深复制，特别是Mat
	operator std::string();

	int operator [](size_t);

	std::string tostr();
	const char*typestr(E_TYPE type);// { return names[type]; }
	const static std::unordered_map<E_TYPE, const char *>names;

private:
	Algparam() = delete;
};
const std::unordered_map<Algparam::E_TYPE, const char *> Algparam::names
{
	std::unordered_map<Algparam::E_TYPE, const char *>::value_type(Algparam::E_TYPE::INT_T,"int") ,
	std::unordered_map<Algparam::E_TYPE, const char *>::value_type(Algparam::E_TYPE::DOUBLE_T,"double"),

};