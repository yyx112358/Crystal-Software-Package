#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CrystalSoftwarePackage.h"

class CrystalSoftwarePackage : public QMainWindow
{
	Q_OBJECT

public:
	CrystalSoftwarePackage(QWidget *parent = Q_NULLPTR);

private:
	Ui::CrystalSoftwarePackageClass ui;
};
