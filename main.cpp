#include "MoviesOOP.h"
#include <QtWidgets/QApplication>
#include "Tests.h"
#include <iostream>
#include <string>
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qmessagebox.h>



int main(int argc, char* argv[])
{
	
	QApplication a(argc, argv);
	
	//testAll();

	FileWatchlist* watchList = nullptr;
	QMessageBox msgBox;
	msgBox.setText("File type");
	QAbstractButton* buttonCSV = msgBox.addButton("CSV", QMessageBox::YesRole);
	QAbstractButton* buttonHTML = msgBox.addButton("HTML", QMessageBox::NoRole);
	int ret = msgBox.exec();
	if (msgBox.clickedButton() == buttonCSV)
		watchList = new CSVWatchlist{};
	else if (msgBox.clickedButton() == buttonHTML)
		watchList = new HTMLWatchlist;
	else
		exit(0);
	
	std::string repoFile("movies.txt");
	AdminRepo adminRepository(repoFile);
	Service service{ adminRepository, watchList };
	MoviesOOP gui{ service };
	gui.show();
	
	return a.exec();
}



