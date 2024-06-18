#include "Service.h"
#include <algorithm>
#include <iostream>

using namespace std;



void Service::addMovieAdmin(const string& title, const string& genre, const int year, const int nrLikes, const string& trailerLink)
{
	this->validateMovie(title, genre, year, nrLikes, trailerLink);
	Movie movie(title, genre, year, nrLikes, trailerLink);
	this->adminRepo.add(movie);

	unique_ptr<Action> ptr = make_unique<ActionAdd>(movie, adminRepo);
	undoStack.push_back(move(ptr));
	redoStack.clear();
}


void Service::addMovieUser(Movie& movie)
{
	this->watchList->add(movie);
}

void Service::removeMovieAdmin(const string& title, const int year)
{
	this->validateTitle(title);
	this->validateYear(year);
	Movie movie(adminRepo.getMovie(title, year));
	this->adminRepo.remove(title, year);
	try {
		this->watchList->remove(title, year);
	}
	catch (const InexistenMovieException& ex) {}

	unique_ptr<Action> ptr = make_unique<ActionRemove>(movie, adminRepo);
	undoStack.push_back(move(ptr));
	redoStack.clear();

}

void Service::removeMovieUser(const std::string& title, const int year)
{
	this->watchList->remove(title, year);
}

void Service::updateMovie(const string& title, const string& genre, const int year, const int nrLikes, const string& trailerLink)
{
	this->validateMovie(title, genre, year, nrLikes, trailerLink);
	Movie movie1(adminRepo.getMovie(title, year));
	this->adminRepo.update(title, genre, year, nrLikes, trailerLink);
	try {
		this->watchList->update(title, genre, year, nrLikes, trailerLink);
	}
	catch (const InexistenMovieException& ex) {}

	Movie movie2{ title,genre,year,nrLikes,trailerLink };

	unique_ptr<Action> ptr = make_unique<ActionUpdate>(movie1, movie2, adminRepo);
	undoStack.push_back(move(ptr));
	redoStack.clear();
}

void Service::undo()
{
	if (undoStack.empty())
		throw exception("No more undos");
	unique_ptr<Action> ptr = move(undoStack.back());
	undoStack.pop_back();
	(*ptr).makeUndo();
	redoStack.push_back(move(ptr));
}

void Service::redo()
{
	if (redoStack.empty())
		throw exception("No more redos");
	unique_ptr<Action> ptr = move(redoStack.back());
	redoStack.pop_back();
	(*ptr).makeRedo();
	undoStack.push_back(move(ptr));
}



vector<Movie> Service::getMoviesByGender(const string& genre)
{
	vector<Movie> movies = this->adminRepo.getMovies();

	vector<Movie> copyVector;
	copy_if(movies.begin(), movies.end(), back_inserter(copyVector), [genre](const Movie& movie) {
		return movie.getGenre().find(genre) != string::npos;
		});

	return copyVector;
}



void Service::likeMovie(const string& title, const int year)
{
	this->validateTitle(title);
	this->validateYear(year);
	this->adminRepo.likeMovie(title, year);
}

void Service::generateMovies()
{

	Movie movie1("Inception", "Science Fiction/Thriller", 2010, 5000, "https://www.youtube.com/watch?v=YoHD9XEInc0");
	Movie movie2("The Shawshank Redemption", "Drama/Crime", 1994, 8200, "https://www.youtube.com/watch?v=6hB3S9bIaco");
	Movie movie3("Pulp Fiction", "Crime/Drama", 1994, 3500, "https://www.youtube.com/watch?v=s7EdQ4FqbhY");
	Movie movie4("The Dark Knight", "Action/Crime", 2008, 6700, "https://www.youtube.com/watch?v=EXeTwQWrcwY");
	Movie movie5("Forrest Gump", "Drama/Romance", 1994, 9100, "https://www.youtube.com/watch?v=bLvqoHBptjg");
	Movie movie6("The Lord of the Rings: The Fellowship of the Ring", "Fantasy/Adventure", 2001, 4800, "https://www.youtube.com/watch?v=V75dMMIW2B4");
	Movie movie7("Interstellar", "Science Fiction/Drama", 2014, 7300, "https://www.youtube.com/watch?v=zSWdZVtXT7E");
	Movie movie8("The Matrix", "Science Fiction/Action", 1999, 8900, "https://www.youtube.com/watch?v=m8e-FF8MsqU");
	Movie movie9("Gladiator", "Action/Drama", 2000, 5200, "https://www.youtube.com/watch?v=owK1qxDselE");
	Movie movie10("Inglourious Basterds", "War/Drama", 2009, 6400, "https://www.youtube.com/watch?v=6AtLlVNsuAc");
	this->adminRepo.add(movie1);
	this->adminRepo.add(movie2);
	this->adminRepo.add(movie3);
	this->adminRepo.add(movie4);
	this->adminRepo.add(movie5);
	this->adminRepo.add(movie6);
	this->adminRepo.add(movie7);
	this->adminRepo.add(movie8);
	this->adminRepo.add(movie9);
	this->adminRepo.add(movie10);
}



void Service::validateMovie(const string& title, const string& genre, const int year, const int nrLikes, const string& trailerLink)const
{
	string exceptions;
	try { this->validateTitle(title); }
	catch (const exception& e) { exceptions += e.what(); exceptions += "\n"; }

	try { this->validateGenre(genre); }
	catch (const exception& e) { exceptions += e.what(); exceptions += "\n"; }

	try { this->validateYear(year); }
	catch (const exception& e) { exceptions += e.what(); exceptions += "\n"; }

	try { this->validateNrLikes(nrLikes); }
	catch (const exception& e) { exceptions += e.what(); exceptions += "\n"; }

	try { this->validateTrailerLink(trailerLink); }
	catch (const exception& e) { exceptions += e.what(); exceptions += "\n"; }


	if (exceptions.length() > 0)
	{
		exceptions.pop_back();
		throw exception(exceptions.c_str());
	}

}

void Service::validateTitle(const string& title)const
{
	if (title.length() < 2)
		throw exception("The title is to short");
	if (title.length() > 60)
		throw exception("The title is too long");
}

void Service::validateGenre(const string& genre)const
{
	if (genre.length() < 2)
		throw exception("The genre is to short");
	if (genre.length() > 30)
		throw exception("The genre is too long");
}

void Service::validateYear(const int year)const
{
	if (year < 1 || year > 2024)
		throw exception("The year is not valid");
}

void Service::validateNrLikes(const int nrLikes)const
{
	if (nrLikes < 0)
		throw exception("The number of likes can not be negative");
}

void Service::validateTrailerLink(const string& trailerLink)const
{
	if (trailerLink.length() < 9)
		throw exception("The link is to short");
	if (trailerLink.length() > 50)
		throw exception("The link is too long");
	string prefixTrailerLink = trailerLink.substr(0, 8);
	if (prefixTrailerLink != "https://")
		throw exception("The link is invalid (it should start with \"https://\"");

}


void Service::saveWatchlist(const std::string& filename)
{
	if (this->watchList == nullptr)
		return;

	this->watchList->setFilename(filename);
	this->watchList->writeToFile();
}

void Service::openWatchlist() const
{
	if (this->watchList == nullptr)
		return;

	this->watchList->displayPlaylist();
}
