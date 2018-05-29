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
class ALGORITHM_API cv::Mat;
class ALGORITHM_API std::mutex;

class ALGORITHM_API AlgorithmControler 
	:public Interface_Alg
{
protected:
	typedef std::lock_guard<std::mutex>alglock_t;
	cv::Mat _srcimg, _dstimg;
	Interface_GUI*_gui;

/*�̰߳�ȫע�⣺
 *	����Ҫ���κ��������в��ܱ����õĺ����ڿ�ͷ��Ӧ����TRYRUN��
 *	����Ҫ���κζ����Ա������ȫ�ֱ�����д�����֮ǰӦ����д������
 *		TRYWRITE��ȫ����������������ԭ���ϾͲ�����д��
 *		�Ե����������б�������ʹ��ԭ�Ӳ���std::atomic������������������Խ����й����������Ϊatomic
 *	TRYRUN��TRYWRITE��RAII�࣬�����˳�������֮ǰ�Զ�������
 *		�����̰߳�ȫ��ǰ���£�Ӧ������С���������䲻��������̬��ȫ���������TRYRUN��TRYWRITE
*/
	std::mutex _write_mutex, _run_mutex;
	#define TRYRUN alglock_t lockrun(_run_mutex);//�������С�
	#define TRYWRITE alglock_t lockwrite(_write_mutex);//����д��
//private:
	std::atomic_bool _is_init = false, _is_pause = false, _is_stop = false;
public:
	AlgorithmControler(const Interface_GUI*gui) { Init(gui); }
	virtual ~AlgorithmControler() { Release(); }

	virtual bool Init(const Interface_GUI*gui) override;
	virtual bool Release() override;

	virtual bool LoadSrc(cv::InputArray src) override;
	virtual bool LoadSetting() override;
	virtual bool LoadParam() override;

	virtual bool ReadRst(cv::OutputArray rst) override;
	virtual bool ReadParam() const override;
	virtual bool ReadState()const override;

	virtual bool Run() override;
	virtual bool RunOnce() override;
	virtual bool Pause() override;
	virtual bool Resume() override;
	virtual bool Stop() override;

	virtual bool IsInit() const override;
	virtual bool IsRun() override;


public:
	virtual bool Reset() override;

};

