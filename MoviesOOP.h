#pragma once

#include <QtWidgets/QWidget>
#include "ui_MoviesOOP.h"
#include "Service.h"
#include <qstackedlayout.h>
#include "MenuGUI.h"
#include "AdminWindow.h"
#include "UserWindow.h"

class MoviesOOP : public QWidget
{
    Q_OBJECT

public:
    MoviesOOP(Service& serv, QWidget *parent = nullptr);
    ~MoviesOOP();

private:
    Ui::MoviesOOPClass ui;
    QStackedLayout* layouts;
    MenuGUI* loginWindow;
    AdminWindow* admin;
    UserWindow* user;
    void setSlots();

private slots:
    void adminButtonHandler();
    void userButtonHandler();
    void backButtonHandler();
};
