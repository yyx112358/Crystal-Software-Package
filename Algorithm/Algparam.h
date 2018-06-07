#pragma once
#include <vector>
#include <string>

#include "dllmain.h"
#include <opencv2/core/mat.hpp>
#include <unordered_map>
#include <tuple>

/*������
* ��������򻯵õ���QVariant������ͬһ�������洢�������ͱ����������з���
* ֧��int,double,string,Point2d,Mat�����Ӧ��vector
* ��֧�������Զ������������֮���ܸı�洢���ͷ��򱨴�
* ��Ҫ���ڴ洢��������ֱ���������㡣����Ч�ʽϵ�
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
	};

	inline bool isinit()const { return _isinit; }
	inline E_TYPE type()const { return _type; }

	//============���캯������������=============
	Algparam():_isinit(false),_type(E_TYPE::VINT_T) { _data.vi = NULL; }//Ĭ���趨Ϊδ��ʼ����ָ���ָ��
	Algparam(const int in) { _type = E_TYPE::INT_T; _data.i = in; _isinit = true; }
	Algparam(const std::vector<int> &in) { _type = E_TYPE::VINT_T; *_data.vi = in; _isinit = true; }
	Algparam(const double in) { _type = E_TYPE::DOUBLE_T; _data.d = in; _isinit = true; }
	Algparam(const std::vector<double> &in) { _type = E_TYPE::VDOUBLE_T; *_data.vd = in; _isinit = true; }
	Algparam(const char *in) { _type = E_TYPE::STRING_T; _data.s = new std::string(in); _isinit = true; }
	Algparam(const std::string &in) { _type = E_TYPE::STRING_T; _data.s = new std::string(in); _isinit = true; }
	Algparam(const std::vector<std::string> &in) { _type = E_TYPE::VSTRING_T; *_data.vs = in; _isinit = true; }
	void copyfrom(const Algparam&src)//ȫ����ƣ������ϴ󵫰�ȫ
	{
		if (_isinit == true)
			release();
		//_isinit = false;
		_type = src._type;
		switch (src._type)
		{
		case E_TYPE::INT_T: _data.i = src.i(); break;
		case E_TYPE::VINT_T:_data.vi = new std::vector<int>(src.vi()); break;
		case E_TYPE::DOUBLE_T:_data.d = src.d(); break;
		case E_TYPE::VDOUBLE_T:_data.vd = new std::vector<double>(src.vd());
		case E_TYPE::STRING_T:_data.s = new std::string(src.s()); break;//ע��������Ҫnew����Ϊs()��������
		case E_TYPE::VSTRING_T:_data.vs = new std::vector<std::string>(src.vs());
		default:
			assert(1);
			throw "Algparam:Unknown Type Copy";
			break;
		}
		_isinit = true;
	}
	Algparam(const Algparam&src) { copyfrom(src); }
	//TODO:��д��ֵ�����
	//��ǰ��ʱ����Ҫ����ʼ���׶ε�ͬ�ڹ��캯������Algparam a=1;�����Algparam(const int in);
	//���¸�ֵʱ�����ԭ���洢int��Algparam aִ��a="abc"�������������Ӧ��operator=��������Ӧ����
	//    ���δ���壬�����ִ��Algparam(const char* in)�½�һ������Ȼ�����Algparam(const Algparam&rhs)���ƣ��������ԭ��int���͵Ķ���
	//    ��Ȼ����Ч�ʻ�ͺܶ࣬����Ŀǰ��ʱ����Ҫ�����Ż����ȶ��Ϳ��ٿ���Ϊ���ȣ���������Ҳ�����˼����ظ�ֵreassign���鷳
	//    �ȵ�֮����Ҫ�Ż�ʱ�ٴ���
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
		if (_data.vi != nullptr)
		{
			switch (_type)
			{
			case E_TYPE::INT_T:
				break;
			case Algparam::E_TYPE::VINT_T:
				delete _data.vi;
				break;
			case  E_TYPE::DOUBLE_T:
				break;
			case Algparam::E_TYPE::VDOUBLE_T:
				delete _data.vd;
				break;
			case Algparam::E_TYPE::STRING_T:
				delete _data.s;
				break;
			case Algparam::E_TYPE::VSTRING_T:
				delete _data.vs;
				break;
			default:
				assert(1);
				throw "Algparam:Unknown Type Released";
				break;
			}
		}
		_data.vi = nullptr;
	}

	~Algparam()
	{
		//cout << tostr() << endl;
		release();
	}

	//================append�����������µ�����================
	Algparam&append(int in);
	//================operator[]����ȡ�ض�����================
	int operator [](size_t);
	//================����ת������================
	inline int i()const { assert(_type == E_TYPE::INT_T || _type == E_TYPE::DOUBLE_T); if (_type == E_TYPE::INT_T)return _data.i; else return _data.d; }
	inline std::vector<int>&vi()const { assert(_type == E_TYPE::VINT_T);  return *_data.vi; }

	inline double d()const { assert(_type == E_TYPE::INT_T || _type == E_TYPE::DOUBLE_T);if(_type == E_TYPE::DOUBLE_T)return _data.d;else return _data.i; }
	inline std::vector<double>&vd() const { assert(_type == E_TYPE::VDOUBLE_T); return *_data.vd; }

	inline std::string& s()const { assert(_type == E_TYPE::STRING_T); return *_data.s; }
	inline std::vector<std::string>&vs() const { assert(_type == E_TYPE::VSTRING_T); return *_data.vs; }

	//================������������������������================
	std::string tostr() { return "Algparam"; }
	const char*typestr(E_TYPE type);// { return names[type]; }
									
	private:
		bool _isinit = false;//��ʼ����־λ
		E_TYPE _type;
		union
		{
			int i;
			std::vector<int>*vi;
			double d;
			std::vector<double>*vd;
			std::string*s;
			std::vector<std::string>*vs;
		}_data;
	//	const static std::unordered_map<E_TYPE, const char *>_names;
};
// const std::unordered_map<Algparam::E_TYPE, const char *> Algparam::_names
// {
// 	std::unordered_map<Algparam::E_TYPE, const char *>::value_type(Algparam::E_TYPE::INT_T,"int") ,
// 	std::unordered_map<Algparam::E_TYPE, const char *>::value_type(Algparam::E_TYPE::DOUBLE_T,"double"),
// };