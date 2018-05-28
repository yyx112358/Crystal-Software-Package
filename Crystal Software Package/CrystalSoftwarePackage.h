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
	virtual bool TextOut(std::string text) override;
	virtual bool ReportProgress(int progress) override;
	virtual bool SaveData(const cv::InputArray data) override;

	virtual bool IsInit() const override;
	virtual bool IsBusy() const override;
	virtual bool ReportError(std::string msg) override;

private:
	Ui::CrystalSoftwarePackageClass ui;
	Interface_Alg*alg = nullptr;
};
