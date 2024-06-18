#pragma once
#include "Movie.h"
#include <vector>
#include "RepoExceptions.h"
#include <stdexcept>


class Repository
{
protected:
	std::vector<Movie> movies;
public:
	Repository() {}
	virtual ~Repository(){}

	/*
	* adds the movie to the vector if it doesn't already exist
	*/
	virtual void add(Movie& movie);

	/*
	* removes the movie from the vector if it exist
	*/
	virtual void remove(const std::string& title, const int year);

	/*
	* updates the movie from the vector if it exist
	*/
	virtual void update(const std::string& title, const std::string& genre, const int year, const int nrLikes, const std::string& trailerLink);
	
	/*
	* gets all movies from the vector
	*/
	std::vector<Movie> getMovies() const;

	/*
	* gets the pointer of a specific movie
	*/
	Movie& getMovie(const std::string& title, const int year);
};


class AdminRepo : public Repository
{
private:
	std::string fileName;
public:

	AdminRepo(std::string& fileName);
	~AdminRepo() {}

	/*
	* adds the movie to the vector if it doesn't already exist
	*/
	void add(Movie& movie) override;

	/*
	* removes the movie from the vector if it exist
	*/
	void remove(const std::string& title, const int year) override;

	/*
	* updates the movie from the vector if it exist
	*/
	void update(const std::string& title, const std::string& genre, const int year, const int nrLikes, const std::string& trailerLink) override;

	/*
	* likes a movie from the vector if it exists
	*/
	void likeMovie(const std::string& title, const int year);

private:
	void readFromFile();
	void writeToFile();

};

class FileWatchlist : public Repository
{
protected:
	std::string filename;

public:
	FileWatchlist():filename("") {}
	virtual ~FileWatchlist() {}

	//sets the name of the file that will be saved
	void setFilename(const std::string& filename) { this->filename = filename; }

	//writes to the file
	virtual void writeToFile() = 0;

	//display the file that was saved
	virtual void displayPlaylist() const = 0;
};


class CSVWatchlist : public FileWatchlist
{
public:

	CSVWatchlist(): FileWatchlist{} {}
	~CSVWatchlist() {}
	/*
		Writes the playlist to file.
		Throws: FileException - if it cannot write.
	*/
	void writeToFile() override;

	/*
		Displays the playlist using Microsof Excel.
	*/
	void displayPlaylist() const override;
};




class HTMLWatchlist : public FileWatchlist
{
public:
	HTMLWatchlist() :FileWatchlist{} {}
	~HTMLWatchlist() {}
	/*
		Writes the playlist to file.
		Throws: FileException - if it cannot write.
	*/
	void writeToFile() override;

	/*
		Displays the playlist saved as html file on opera.
	*/
	void displayPlaylist() const override;
};

