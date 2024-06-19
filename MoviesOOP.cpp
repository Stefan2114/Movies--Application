#include "MoviesOOP.h"

MoviesOOP::MoviesOOP(Service& serv,QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    layouts = new QStackedLayout;

    loginWindow = new MenuGUI{};
    admin = new AdminWindow{ serv };
    user = new UserWindow{ serv };

    layouts->addWidget(loginWindow);
    layouts->addWidget(admin);
    layouts->addWidget(user);
    this->setLayout(layouts);

    this->setWindowTitle("Mode Menu");

    setSlots();

}

MoviesOOP::~MoviesOOP()
{}

void MoviesOOP::setSlots()
{
    QWidget::connect(loginWindow->adminButton, &QPushButton::clicked, this, &MoviesOOP::adminButtonHandler);
    QWidget::connect(loginWindow->userButton, &QPushButton::clicked, this, &MoviesOOP::userButtonHandler);
    QWidget::connect(admin->backButton, &QPushButton::clicked, this, &MoviesOOP::backButtonHandler);
    QWidget::connect(user->backButton, &QPushButton::clicked, this, &MoviesOOP::backButtonHandler);

}

void MoviesOOP::adminButtonHandler()
{
    this->setWindowTitle("Admin");
    layouts->setCurrentIndex(1);
}

void MoviesOOP::userButtonHandler()
{
    this->setWindowTitle("User");
    layouts->setCurrentIndex(2);
}

void MoviesOOP::backButtonHandler()
{
    this->setWindowTitle("Mode Menu");
    layouts->setCurrentIndex(0);
}
