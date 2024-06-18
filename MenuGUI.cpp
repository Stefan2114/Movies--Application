#include "MenuGUI.h"

MenuGUI::MenuGUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	adminButton = ui.adminButton;
	userButton = ui.userButton;
}

MenuGUI::~MenuGUI()
{}
