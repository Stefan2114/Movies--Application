#pragma once

#include <QWidget>
#include "ui_AdminWindow.h"
#include "Service.h"

class AdminWindow : public QWidget
{
	Q_OBJECT

public:
	AdminWindow(Service& serv, QWidget *parent = nullptr);
	~AdminWindow();
	QPushButton* backButton;

private:
	Ui::AdminWindowClass ui;
	Service& serv;
	void setSlots();
	void populateList();


private slots:
	void addButtonHandler();
	void deleteButtonHandler();
	void updateButtonHandler();
	void undoButtonHandler();
	void redoButtonHandler();
	void itemClickedHandler();
	void clearSelectionHandler();
};
