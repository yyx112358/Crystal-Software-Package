#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_CrystalSoftwarePackage.h"

#include "Warpper.h"

class CrystalSoftwarePackage : public QMainWindow
{
	Q_OBJECT

public:
	CrystalSoftwarePackage(QWidget *parent = Q_NULLPTR);
	~CrystalSoftwarePackage();

signals:
	void sig();


public slots:
	void LoadFiles();
	void RunAlg();
	void PauseAlg(bool ispause);
	void DisplayState(State_E);

private:
	Ui::CrystalSoftwarePackageClass ui;
	std::vector<Warpper*>algs{};

	int _GetSenderId(QObject*sender)
	{
		for (auto i = 0; i < algs.size(); i++)
			if (algs[i] == sender)return i;
		return -1;
	}

};
