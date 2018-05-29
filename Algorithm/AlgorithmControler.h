// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ALGORITHM_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ALGORITHM_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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

