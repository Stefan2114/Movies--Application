#include "AdminWindow.h"
#include "qmessagebox.h"
using namespace std;


AdminWindow::AdminWindow(Service& serv, QWidget *parent)
	: QWidget(parent),serv(serv)
{
	ui.setupUi(this);
	backButton = ui.backButton;
	setSlots();
	populateList();
}

AdminWindow::~AdminWindow()
{}

void AdminWindow::setSlots()
{
	QWidget::connect(ui.moviesList, &QListWidget::itemClicked, this, &AdminWindow::itemClickedHandler);

	QWidget::connect(ui.titleLineEdit, &QLineEdit::textChanged, this, &AdminWindow::clearSelectionHandler);
	QWidget::connect(ui.genreLineEdit, &QLineEdit::textChanged, this, &AdminWindow::clearSelectionHandler);
	QWidget::connect(ui.yearLineEdit, &QLineEdit::textChanged, this, &AdminWindow::clearSelectionHandler);
	QWidget::connect(ui.nrLikesLineEdit, &QLineEdit::textChanged, this, &AdminWindow::clearSelectionHandler);
	QWidget::connect(ui.trailerLineEdit, &QLineEdit::textChanged, this, &AdminWindow::clearSelectionHandler);

	QWidget::connect(ui.addButton, &QPushButton::clicked, this, &AdminWindow::addButtonHandler);
	QWidget::connect(ui.deleteButton, &QPushButton::clicked, this, &AdminWindow::deleteButtonHandler);
	QWidget::connect(ui.updateButton, &QPushButton::clicked, this, &AdminWindow::updateButtonHandler);
	QWidget::connect(ui.undoButton, &QPushButton::clicked, this, &AdminWindow::undoButtonHandler);
	QWidget::connect(ui.redoButton, &QPushButton::clicked, this, &AdminWindow::redoButtonHandler);

	
}

void AdminWindow::populateList()
{
	ui.moviesList->clear();
	vector<Movie> movies = serv.getMovies();
	for (Movie& m : movies)
		ui.moviesList->addItem(QString::fromStdString(m.toString()));
}

void AdminWindow::addButtonHandler()
{
	string title, genre, year, nrLikes, trailer;
	title = ui.titleLineEdit->text().toStdString();
	genre = ui.genreLineEdit->text().toStdString();
	year = ui.yearLineEdit->text().toStdString();
	nrLikes = ui.nrLikesLineEdit->text().toStdString();
	trailer = ui.trailerLineEdit->text().toStdString();

	try { 
		serv.addMovieAdmin(title, genre, stoi(year), stoi(nrLikes), trailer); 
		populateList(); 
	}
	catch (const DuplicateMovieException& e) { QMessageBox::warning(this, "Error", QString::fromStdString(e.what())); }
	catch (const exception& e) { QMessageBox::warning(this, "Error", QString::fromStdString(e.what())); }

}

void AdminWindow::deleteButtonHandler()
{
	string title, year;
	title = ui.titleLineEdit->text().toStdString();
	year = ui.yearLineEdit->text().toStdString();

	try { 
		serv.removeMovieAdmin(title, stoi(year));
		populateList();
	}
	catch (const InexistenMovieException& e) { QMessageBox::warning(this, "Error", QString::fromStdString(e.what())); }
	catch (const exception& e) { QMessageBox::warning(this, "Error", QString::fromStdString(e.what())); }

}

void AdminWindow::updateButtonHandler()
{
	string title, genre, year, nrLikes, trailer;
	title = ui.titleLineEdit->text().toStdString();
	genre = ui.genreLineEdit->text().toStdString();
	year = ui.yearLineEdit->text().toStdString();
	nrLikes = ui.nrLikesLineEdit->text().toStdString();
	trailer = ui.trailerLineEdit->text().toStdString();

	try { 
		serv.updateMovie(title, genre, stoi(year), stoi(nrLikes), trailer);
		populateList();
	}
	catch (const InexistenMovieException& e) { QMessageBox::warning(this, "Error", QString::fromStdString(e.what())); }
	catch (const exception& e) { QMessageBox::warning(this, "Error", QString::fromStdString(e.what())); }

}

void AdminWindow::undoButtonHandler()
{
	try {
		serv.undo();
		populateList();
	}
	catch (const exception& e) { QMessageBox::warning(this, "Error", QString::fromStdString(e.what())); }
}

void AdminWindow::redoButtonHandler()
{
	try {
		serv.redo();
		populateList();
	}
	catch (const exception& e) { QMessageBox::warning(this, "Error", QString::fromStdString(e.what())); }
}

void AdminWindow::itemClickedHandler()
{
	int row = ui.moviesList->currentRow();
	vector<Movie> movies = serv.getMovies();
	Movie m = movies[row];

	ui.titleLineEdit->setText(QString::fromStdString(m.getTitle()));
	ui.genreLineEdit->setText(QString::fromStdString(m.getGenre()));
	ui.yearLineEdit->setText(QString::number(m.getYear()));
	ui.nrLikesLineEdit->setText(QString::number(m.getNrLikes()));
	ui.trailerLineEdit->setText(QString::fromStdString(m.getTrailerLink()));
}

void AdminWindow::clearSelectionHandler()
{
	ui.moviesList->clearSelection();
}
