#pragma once
#include <vector>
#include <string>

#include "dllmain.h"
#include <opencv2/core/mat.hpp>
#include <unordered_map>

/*参数表
* 根据需求简化得到的QVariant，可用同一个变量存储各种类型变量，并进行反射
* 支持int,double,string,Point2d,Mat及其对应的vector
* 不支持其它自定义变量，创建之后不能改变存储类型否则报错
* 主要用于存储，不建议直接用来计算。因其效率较低
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
private:
	bool _isinit = false;//初始化标志位
public:
	inline bool isinit()const { return _isinit; }
	union
	{
		int i;
		std::vector<int>*vi;
		double d;
		std::vector<double>*vd;
		std::string*s;
		std::vector<std::string>*vs;
	}data;

	//============构造函数和析构函数=============
	Algparam() {}//= delete;
	Algparam(const int in) { type = E_TYPE::INT_T; data.i = in; _isinit = true; }
	Algparam(const std::vector<int> &in) { type = E_TYPE::VINT_T; *data.vi = in; _isinit = true; }
	Algparam(const double in) { type = E_TYPE::DOUBLE_T; data.d = in; _isinit = true; }
	Algparam(const std::vector<double> &in) { type = E_TYPE::VDOUBLE_T; *data.vd = in; _isinit = true; }
	Algparam(const char *in) { type = E_TYPE::STRING_T; data.s = new std::string(in); _isinit = true; }
	Algparam(const std::string &in) { type = E_TYPE::STRING_T; data.s = new std::string(in); _isinit = true; }
	Algparam(const std::vector<std::string> &in) { type = E_TYPE::VSTRING_T; *data.vs = in; _isinit = true; }
	void copyfrom(const Algparam&src)//全部深复制，开销较大但安全
	{
		if (_isinit == true)
			release();
		//_isinit = false;
		type = src.type;
		switch (src.type)
		{
		case E_TYPE::INT_T: data.i = src.i(); break;
		case E_TYPE::VINT_T:data.vi = new std::vector<int>(src.vi()); break;
		case E_TYPE::DOUBLE_T:data.d = src.d(); break;
		case E_TYPE::VDOUBLE_T:data.vd = new std::vector<double>(src.vd());
		case E_TYPE::STRING_T:data.s = new std::string(src.s()); break;//注意这里需要new，因为s()返回引用
		case E_TYPE::VSTRING_T:data.vs = new std::vector<std::string>(src.vs());
		default:
			assert(1);
			throw "Not implement yet";
			break;
		}
		_isinit = true;
	}
	Algparam(const Algparam&src) { copyfrom(src); }
	//TODO:重写赋值运算符
	//当前暂时不需要。初始化阶段等同于构造函数。如Algparam a=1;会调用Algparam(const int in);
	//重新赋值时，如对原来存储int的Algparam a执行a="abc"，如果定义了相应的operator=则会调用相应函数
	//    如果未定义，则会先执行Algparam(const char* in)新建一个对象，然后调用Algparam(const Algparam&rhs)复制，最后析构原来int类型的对象
	//    虽然这样效率会低很多，但是目前暂时不需要更多优化以稳定和快速开发为优先，而且这样也避免了加入重赋值reassign的麻烦
	//    等到之后需要优化时再处理
	inline void _reassign_check(E_TYPE newtype)
	{
		assert(1);
		// 		if (_isinit != false)
		// 		{
		// 			_isinit = false;
		// 			if (newtype != type)
		// 				type = newtype;
		// 		}
	}
	Algparam& operator =(const Algparam&src) { copyfrom(src); return *this; }
	// 	Algparam& operator =(const int in) { assert(type == E_TYPE::INT_T); data.i = in; return*this; }
	// 	Algparam& operator =(const std::vector<int> &in) { assert(type == E_TYPE::VINT_T); *data.vi = in; return*this; }
	// 	Algparam& operator =(const double in) { assert(type == E_TYPE::DOUBLE_T); data.d = in; return*this; }
	// 	Algparam& operator =(const std::vector<double> &in) { assert(type == E_TYPE::VDOUBLE_T); *data.vd = in; return*this; }
	// 	Algparam& operator=(const char *in){ assert(type == E_TYPE::STRING_T); *data.s = in; return*this; }
	// 	Algparam& operator =(const std::string &in) { assert(type == E_TYPE::STRING_T); *data.s = in; return*this; }
	// 	Algparam& operator =(const std::vector<std::string> &in) { assert(type == E_TYPE::VSTRING_T); *data.vs = in; return*this; }

	void release()
	{
		_isinit = false;
		if (data.vi != nullptr)
		{
			switch (type)
			{
			case E_TYPE::INT_T:
				break;
			case Algparam::E_TYPE::VINT_T:
				delete data.vi;
				break;
			case  E_TYPE::DOUBLE_T:
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
				assert(1);
				throw "Not implement yet";
				break;
			}
		}
		data.vi = nullptr;
	}

	~Algparam()
	{
		//cout << tostr() << endl;
		release();
	}

	//================append函数，附加新的内容================
	Algparam&append(int in);
	//================operator[]，获取特定内容================
	int operator [](size_t);
	//================类型转换函数================
	inline int i()const { assert(type == E_TYPE::INT_T); return data.i; }
	inline std::vector<int>&vi()const { assert(type == E_TYPE::VINT_T);  return *data.vi; }

	inline double d()const { assert(type == E_TYPE::DOUBLE_T); return data.d; }
	inline std::vector<double>&vd() const { assert(type == E_TYPE::VDOUBLE_T); return *data.vd; }

	inline std::string& s()const { assert(type == E_TYPE::STRING_T); return *data.s; }
	inline std::vector<std::string>&vs() const { assert(type == E_TYPE::VSTRING_T); return *data.vs; }

	//TODO:检查复制时是浅复制还是深复制，特别是Mat
	operator std::string();

	//================输出函数，输出类型名、内容================
	std::string tostr() { return "Algparam"; }
	const char*typestr(E_TYPE type);// { return names[type]; }
									//	const static std::unordered_map<E_TYPE, const char *>_names;

};
// const std::unordered_map<Algparam::E_TYPE, const char *> Algparam::_names
// {
// 	std::unordered_map<Algparam::E_TYPE, const char *>::value_type(Algparam::E_TYPE::INT_T,"int") ,
// 	std::unordered_map<Algparam::E_TYPE, const char *>::value_type(Algparam::E_TYPE::DOUBLE_T,"double"),
// };