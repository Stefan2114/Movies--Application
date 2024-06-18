#pragma once

#include <QWidget>
#include "ui_MenuGUI.h"

class MenuGUI : public QWidget
{
	Q_OBJECT

public:
	MenuGUI(QWidget *parent = nullptr);
	~MenuGUI();
	QPushButton* adminButton;
	QPushButton* userButton;


private:
	Ui::MenuGUIClass ui;
};
