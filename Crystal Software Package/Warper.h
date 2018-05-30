#pragma once
#include "qthread.h"
#include "..\Algorithm\AlgorithmControler.h"
#include <QStringList>

class Warper :
	public QThread,public AlgorithmControler,public Interface_GUI
{
	Q_OBJECT

public:
	Warper() :AlgorithmControler(this) { /*aout << "====Algorithm Init [OK]====";*/ }
	virtual ~Warper(){}

	virtual void run() override;

	virtual bool Pause(bool ispause) override{return AlgorithmControler::Pause(ispause);}

signals:
	void sig_ShowImg(QPixmap);
	void sig_ShowText(QString);
	void sig_ReportProgress(int progress);
	bool sig_ReportError(std::string msg);
	bool sig_SaveData();

private:
	virtual bool ShowImg(const cv::InputArray img) override;
	virtual bool ShowText(std::string text) override;
	virtual bool ReportProgress(int progress) override;
	virtual bool ReportError(std::string msg) override;
	virtual bool SaveData(const cv::InputArray data) override;

	virtual bool IsBusy() const override;
	//virtual bool Interface_GUI::IsInit()const override { return true; }
	virtual bool wait(int msec = 0) const override;

	QStringList filenames;

};

