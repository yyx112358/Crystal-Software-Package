#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_CrystalSoftwarePackage.h"

#include "..\Algorithm\Interface.h"

class CrystalSoftwarePackage : public QMainWindow,public Interface_GUI
{
	Q_OBJECT

public:
	CrystalSoftwarePackage(QWidget *parent = Q_NULLPTR);
	~CrystalSoftwarePackage();

	virtual bool ShowImg(const cv::InputArray img) override;
	virtual bool ShowText(std::string text) override;
	virtual bool ReportProgress(int progress) override;
	virtual bool ReportError(std::string msg) override;
	virtual bool SaveData(const cv::InputArray data) override;

	virtual bool IsInit() const override;
	virtual bool IsBusy() const override;

	signals:
	void sig_ShowImg(QPixmap img);
	void sig_ShowText(QString str);
	void sig_ReportProgress();
	void sig_SaveData();
	void sig_ReportError();

public slots:
	void LoadFiles();
private:
	Ui::CrystalSoftwarePackageClass ui;
	Interface_Alg*alg = nullptr;
};
