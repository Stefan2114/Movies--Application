#include "Repository.h"
#include <fstream>
#include <Windows.h>
using namespace std;


void Repository::add(Movie& movie)
{
	try {
		this->getMovie(movie.getTitle(), movie.getYear());
		throw DuplicateMovieException();
	}
	catch (InexistenMovieException&) {}
	this->movies.push_back(movie);
}


void Repository::remove(const string& title, const int year)
{
	Movie& mv = this->getMovie(title, year);
	auto it = find(this->movies.begin(), this->movies.end(), mv);
	this->movies.erase(it);
}


void Repository::update(const string& title, const string& genre, const int year, const int nrLikes, const string& trailerLink)
{
	Movie& mv = this->getMovie(title, year);
	mv.setGenre(genre);
	mv.setNrLikes(nrLikes);
	mv.setTrailerLink(trailerLink);
}


vector<Movie> Repository::getMovies() const
{
	return this->movies;
}


Movie& Repository::getMovie(const string& title, const int year)
{
	for(auto it = this->movies.begin(); it != this->movies.end() ; ++it)
	{
		if ((*it).getTitle() == title && (*it).getYear() == year)
			return (*it); // Return the position to the found movie
	}

	throw InexistenMovieException();
}

AdminRepo::AdminRepo(std::string& fileName): fileName(fileName)
{
	this->readFromFile();
}


void AdminRepo::add(Movie& movie)
{
	Repository::add(movie);
	this->writeToFile();
}

void AdminRepo::remove(const std::string& title, const int year)
{
	Repository::remove(title, year);
	this->writeToFile();
}

void AdminRepo::update(const std::string& title, const std::string& genre, const int year, const int nrLikes, const std::string& trailerLink)
{
	Repository::update(title, genre, year, nrLikes, trailerLink);
	this->writeToFile();
}

void AdminRepo::likeMovie(const std::string& title, const int year)
{
	Movie& movie = getMovie(title, year);
	movie.setNrLikes(movie.getNrLikes() + 1);
	this->writeToFile();
}


void AdminRepo::readFromFile()
{
	ifstream file(this->fileName);

	if (!file.is_open())
		throw FileException("The file could not be opened!");

	Movie m;
	while (file >> m)
		this->movies.push_back(m);

	file.close();
}


void AdminRepo::writeToFile()
{
	ofstream file(this->fileName);
	if (!file.is_open())
		throw FileException("The file could not be opened!");

	for (auto m : this->movies)
	{
		file << m;
	}

	file.close();
}

void CSVWatchlist::writeToFile()
{

	if (this->filename.empty())
		throw FileException("First you need to save the file");
	ofstream f(this->filename);

	if (!f.is_open())
		throw FileException("The file could not be opened!");

	for (auto m : this->movies)
		f << m;

	f.close();
}

void CSVWatchlist::displayPlaylist() const
{
	if (this->filename.empty())
		throw exception("First you have to save the file");
	string aux = "\"" + this->filename + "\""; // if the path contains spaces, we must put it inside quotations
	//ShellExecuteA(NULL, NULL, "C:\\Program Files (x86)\\OpenOffice 4\\program\\scalc.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
	ShellExecuteA(NULL, NULL, "c:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
}

void HTMLWatchlist::writeToFile()
{

	ofstream f(this->filename);

	if (!f.is_open())
		throw FileException("The file could not be opened!");

	f << "<!DOCTYPE html>\n";
	f << "<html>\n";
	f << "<head>\n";
	f << "    <title>Watchlist</title>\n";
	f << "</head>\n";
	f << "<body>\n";
	f << "<table border=\"1\">\n";
	f << "    <tr>\n";
	f << "        <td>Title</td>\n";
	f << "        <td>Genre</td>\n";
	f << "        <td>Year</td>\n";
	f << "        <td>Nr of likes</td>\n";
	f << "        <td>Trailer link</td>\n";
	f << "    </tr>\n";

	for (auto m : this->movies)
	{
		f << "    <tr>\n";
		f << "        <td>" + m.getTitle() + "</td>\n";
		f << "        <td>" + m.getGenre() + "</td>\n";
		f << "        <td>" + to_string(m.getYear()) + "</td>\n";
		f << "        <td>" + to_string(m.getNrLikes()) + "</td>\n";
		f << "        <td>" + m.getTrailerLink() + "</td>\n";
		f << "    </tr>\n";
	}

	f << "</table>\n";
	f << "</body>\n";
	f << "</html>";

	f.close();
}

void HTMLWatchlist::displayPlaylist() const
{

	if (this->filename.empty())
		throw FileException("First you need to save the file");
	string aux = "\"" + this->filename + "\""; // if the path contains spaces, we must put it inside quotations
	//ShellExecuteA(NULL, NULL, "C:\\Program Files (x86)\\OpenOffice 4\\program\\scalc.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
	//ShellExecuteA(NULL, NULL, "c:\\Users\\stefa\\AppData\\Local\\Programs\\Opera GX\\opera.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
	ShellExecuteA(NULL, "open", aux.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);
}
