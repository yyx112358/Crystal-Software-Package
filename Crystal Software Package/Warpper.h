#pragma once
#include "qthread.h"
#include "..\Algorithm\AlgorithmTable.h"
#include <QStringList>


/*class Warpper
 *	多线程接口
 *
*/
class Warpper :
	public QThread,public Interface_GUI
{
	Q_OBJECT

public:
	Warpper(CreateAlgFunc pfunc) 
	{ 
		Init(pfunc); 
	}
	virtual ~Warpper() 
	{
		Release(); 
	}
//对AlgorithmControler的包装
	void Init(CreateAlgFunc pfunc)
	{ 
		qRegisterMetaType<State_E>("State_E");
		_alg = pfunc(this); 
	}
	virtual bool Release() 
	{ 
		if (_alg != nullptr) 
		{
			bool b = _alg->Release();
			_alg = nullptr;
			return b;
		}
		return true;
	}
	virtual bool Reset() { return _alg->Reset(); }

	virtual bool LoadSrc(cv::InputArray src) { return _alg->LoadSrc(src); }
	virtual bool LoadSetting() { return _alg->LoadSetting(); }
	virtual bool LoadParam(ParamMap_t&params) { return _alg->LoadParam(params); }

	virtual bool ReadRst(cv::OutputArray rst) { return _alg->ReadRst(rst); }
	virtual bool ReadParam(ParamMap_t&params) const { return _alg->ReadParam(params); }
	virtual State_E ReadState()const { return _alg->ReadState(); }

	virtual void run() override { _alg->Run(); }
	virtual bool Pause(bool ispause) { return _alg->Pause(ispause); }
	virtual bool Stop() { return _alg->Stop(); }

	virtual bool IsInit() const { return _alg->IsInit(); }
	virtual bool IsRun() { return _alg->IsRun(); }
	virtual bool IsWrite() { return _alg->IsWrite(); }
signals:
	void sig_ShowImg(QPixmap);
	void sig_ShowText(QString);
	void sig_ReportState(State_E);
	void sig_ReportProgress(int);
	bool sig_ReportError(std::string);
	bool sig_SaveData();

private:
	virtual bool ShowImg(const cv::InputArray img) override;
	virtual bool ShowText(std::string text) override;
	virtual bool ReportState(State_E progress) override;
	virtual bool ReportProgress(int progress)override;
	virtual bool ReportError(std::string msg) override;
	virtual bool SaveData(const cv::InputArray data) override;

	virtual bool IsBusy() const override;
	//virtual bool Interface_GUI::IsInit()const override { return true; }
	virtual bool wait(int msec = 0) const override;

	QStringList _filenames;
	//queue<string>_workflow;
	AlgorithmControler*_alg=nullptr;
};

