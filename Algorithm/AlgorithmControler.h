// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ALGORITHM_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ALGORITHM_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#pragma once

#include "Interface.h"
class ALGORITHM_API cv::Mat;

class ALGORITHM_API AlgorithmControler 
	:public Interface_Alg
{
protected:
	cv::Mat _srcimg, _dstimg;
	Interface_GUI*_gui;
	
public:
	AlgorithmControler(const Interface_GUI*gui) { Init(gui); }
	virtual ~AlgorithmControler(){}

	virtual bool Init(const Interface_GUI*gui) override;
	virtual bool Release() override;

	virtual bool LoadSrc(cv::InputArray src) override;
	virtual bool LoadSetting() override;
	virtual bool LoadParam() override;

	virtual bool ReadRst(cv::OutputArray rst) override;
	virtual bool ReadParam() override;
	virtual bool ReadState() override;

	virtual bool Run() override;
	virtual bool RunOnce() override;
	virtual bool Pause() override;
	virtual bool Stop() override;
	virtual bool Terminate() override;

	virtual bool Train() override;

	virtual bool IsInit() const override;
	virtual bool IsBusy() const override;
};

