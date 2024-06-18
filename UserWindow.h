#pragma once

#include <QWidget>
#include "ui_UserWindow.h"
#include "Service.h"

class UserWindow : public QWidget
{
	Q_OBJECT

public:
	UserWindow(Service& serv, QWidget *parent = nullptr);
	~UserWindow();
	QPushButton* backButton;
	

private:
	Ui::UserWindowClass ui;
	Service& serv;
	void setSlots();
	void populateWatchList();

private slots:

	void playWatchListButtonHandler();
	void playSearchButtonHandler();
	void deleteButtonHandler();
	void saveButtonHandler();
	void displayButtonHandler();
	void searchHandler();
	void addButtonHandler();

};
