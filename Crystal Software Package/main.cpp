#include "stdafx.h"
#include "CrystalSoftwarePackage.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CrystalSoftwarePackage w;
	w.show();

	try
	{
		return a.exec();
	}
	catch (const std::exception&e)
	{
		qDebug() << e.what();
	}
	return -1;
}
