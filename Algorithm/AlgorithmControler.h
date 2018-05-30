// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ALGORITHM_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ALGORITHM_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#pragma once

#include "Interface.h"
#include <mutex>
#include <atomic>
#include <sstream>
class ALGORITHM_API cv::Mat;
class ALGORITHM_API std::mutex;
struct ALGORITHM_API atomic_bool;
class ALGORITHM_API ostringstream;
class ALGORITHM_API AlgOutstream;

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

class ALGORITHM_API AlgorithmControler 
	:public Interface_Alg 
{
private:
	typedef std::lock_guard<std::mutex>alglock_t;
	cv::Mat _srcimg, _dstimg;
	Interface_GUI*_gui;
	State_E _sta = State_E::init_pre;
#define CHANGE_STATE(sta) {_sta=sta;_gui->ReportState(sta);}

/*�̰߳�ȫע�⣺
 *	����Ҫ���κ��������в��ܱ����õĺ����ڿ�ͷ��Ӧ����LOCKRUN��
 *	����Ҫ���κζ����Ա������ȫ�ֱ�����д�����֮ǰӦ����д������
 *		LOCKWRITE��ȫ����������������ԭ���ϾͲ�����д��
 *		�Ե����������б�������ʹ��ԭ�Ӳ���std::atomic������������������Խ����й����������Ϊatomic
 *	LOCKRUN��LOCKWRITE��RAII�࣬�����˳�������֮ǰ�Զ�������
 *		�����̰߳�ȫ��ǰ���£�Ӧ������С���������䲻��������̬��ȫ���������LOCKRUN��LOCKWRITE
*/
	std::mutex _write_mutex, _run_mutex;
	#define LOCKRUN alglock_t lockrun(_run_mutex);//�������С�
	#define LOCKWRITE alglock_t lockwrite(_write_mutex);//����д��
//private:
	std::atomic_bool _is_init = false, _is_pause = false, _is_stop = false;
public:
	AlgorithmControler(const Interface_GUI*gui):aout(gui) { Init(gui); }
	virtual ~AlgorithmControler() { Release(); }

	virtual bool Init(const Interface_GUI*gui) override;
	virtual bool Release() override;
	virtual bool Reset() override;

	virtual bool LoadSrc(cv::InputArray src) override;
	virtual bool LoadSetting() override;
	virtual bool LoadParam() override;

	virtual bool ReadRst(cv::OutputArray rst) override;
	virtual bool ReadParam() const override;
	virtual State_E ReadState()const override;

	virtual bool Run() override;
	virtual bool Pause(bool ispause) override;
	virtual bool Stop() override;

	virtual bool IsInit() const override;
	virtual bool IsRun() override;
	virtual bool IsWrite() override;

	AlgOutstream aout;

};



