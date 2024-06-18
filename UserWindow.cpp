#include "UserWindow.h"
#include "qmessagebox.h"
#include "qformlayout.h"
using namespace std;

UserWindow::UserWindow(Service& serv, QWidget *parent)
	: QWidget(parent),serv(serv)
{
	ui.setupUi(this);
	backButton = ui.backButton;
	setSlots();
}

UserWindow::~UserWindow()
{}

void UserWindow::setSlots()
{
	QWidget::connect(ui.playWatchListButton, &QPushButton::clicked, this, &UserWindow::playWatchListButtonHandler);
	QWidget::connect(ui.deleteButton, &QPushButton::clicked, this, &UserWindow::deleteButtonHandler);
	QWidget::connect(ui.saveButton, &QPushButton::clicked, this, &UserWindow::saveButtonHandler);
	QWidget::connect(ui.displayButton, &QPushButton::clicked, this, &UserWindow::displayButtonHandler);
	QWidget::connect(ui.searchLineEdit, &QLineEdit::textChanged, this, &UserWindow::searchHandler);
	QWidget::connect(ui.playSearchButton, &QPushButton::clicked, this, &UserWindow::playSearchButtonHandler);
	QWidget::connect(ui.addButton, &QPushButton::clicked, this, &UserWindow::addButtonHandler);

}

void UserWindow::populateWatchList()
{
	ui.watchList->clear();
	vector<Movie> movies = serv.getWatchList();
	for (Movie& m : movies)
		ui.watchList->addItem(QString::fromStdString(m.toString()));
}

void UserWindow::playWatchListButtonHandler()
{
	int row = ui.watchList->currentRow();
	if (row == -1)
		return;

	vector<Movie> movies = serv.getWatchList();
	Movie& m = movies[row];
	m.play();
}

void UserWindow::playSearchButtonHandler()
{
	int row = ui.searchList->currentRow();
	if (row == -1)
		return;

	string genre = ui.searchLineEdit->text().toStdString();
	vector<Movie> movies = serv.getMoviesByGender(genre);
	Movie& m = movies[row];
	m.play();
}

void UserWindow::deleteButtonHandler()
{
	int row = ui.watchList->currentRow();
	if (row == -1)
		return;

	vector<Movie> movies = serv.getWatchList();
	Movie& m = movies[row];
	serv.removeMovieUser(m.getTitle(), m.getYear());
	populateWatchList();
}

void UserWindow::saveButtonHandler()
{
	QDialog* dialog = new QDialog(this);
	QFormLayout* dialogLayout = new QFormLayout{};
	QLabel* fileNameLabel = new QLabel("File Name: ");
	QLineEdit* nameEdit = new QLineEdit{};
	dialogLayout->addRow(fileNameLabel, nameEdit);
	QPushButton* saveButton = new QPushButton("Save");
	dialogLayout->addRow(saveButton);
	dialog->setLayout(dialogLayout);
	dialog->setModal(true);

	// Connect the saveButton clicked signal to a slot
	connect(saveButton, &QPushButton::clicked, this, [=]() {
		QString filename = nameEdit->text();
		if (filename.isEmpty()) {
			QMessageBox::warning(dialog, "Error", "Please enter a valid file name.");
			return; // Don't close the dialog if the filename is empty
		}

		this->serv.saveWatchlist(filename.toStdString());
		dialog->close(); // Close the dialog after saving
		});

	// Show the dialog
	dialog->exec();
}

void UserWindow::displayButtonHandler()
{
	try { this->serv.openWatchlist(); }
	catch (const std::exception& e) { QMessageBox::warning(this, "Error", QString::fromStdString(e.what())); }
}

void UserWindow::searchHandler()
{
	string genre = ui.searchLineEdit->text().toStdString();
	vector<Movie> movies = serv.getMoviesByGender(genre);
	ui.searchList->clear();
	for (Movie& m : movies)
		ui.searchList->addItem(QString::fromStdString(m.toString()));
}

void UserWindow::addButtonHandler()
{
	int row = ui.searchList->currentRow();
	if (row == -1)
		return;

	string genre = ui.searchLineEdit->text().toStdString();
	vector<Movie> movies = serv.getMoviesByGender(genre);
	Movie& m = movies[row];
	try {
		serv.addMovieUser(m);
		populateWatchList();
	}
	catch (const DuplicateMovieException& e) { QMessageBox::warning(this, "Error", QString::fromStdString(e.what())); }
	
}
