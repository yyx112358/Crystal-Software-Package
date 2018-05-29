// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ALGORITHM_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ALGORITHM_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#pragma once

#include "Interface.h"
#include <mutex>
class ALGORITHM_API cv::Mat;


class ALGORITHM_API AlgorithmControler 
	:public Interface_Alg
{
protected:
	typedef std::lock_guard<std::mutex>AlgLock_t;
	cv::Mat _srcimg, _dstimg;
	Interface_GUI*_gui;

private:
	

	bool _is_init = false;
	bool _is_run = false;
	bool _is_pause = false;
public:
	AlgorithmControler(const Interface_GUI*gui) { Init(gui); }
	virtual ~AlgorithmControler() { Release(); }

	virtual bool Init(const Interface_GUI*gui) override;
	virtual bool Release() override;

	virtual bool LoadSrc(cv::InputArray src) override;
	virtual bool LoadSetting() override;
	virtual bool LoadParam() override;

	virtual bool ReadRst(cv::OutputArray rst) override;
	virtual bool ReadParam() override;
	virtual bool ReadState()const override;

	virtual bool Run() override;
	virtual bool RunOnce() override;
	virtual bool Pause() override;
	virtual bool Stop() override;
	virtual bool Terminate() override;

	virtual bool Train() override;

	virtual bool IsInit() const override;
	virtual bool IsRun() const override;

	virtual bool LoadSrc_Async(cv::InputArray src) override;


	virtual bool LoadSetting_Async() override;


	virtual bool LoadParam_Async() override;


	virtual bool ReadRst_Async(cv::OutputArray rst) override;


	virtual bool Resume() override;

};

