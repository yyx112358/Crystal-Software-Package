#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_CrystalSoftwarePackage.h"

#include "Warper.h"

class CrystalSoftwarePackage : public QMainWindow
{
	Q_OBJECT

public:
	CrystalSoftwarePackage(QWidget *parent = Q_NULLPTR);
	~CrystalSoftwarePackage();

signals:


public slots:
	void LoadFiles();
	void RunAlg();
	void PauseAlg(bool ispause);
private:
	Ui::CrystalSoftwarePackageClass ui;
	Warper*alg = nullptr;


};
