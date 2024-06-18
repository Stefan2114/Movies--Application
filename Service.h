#pragma once
#include "Repository.h"
#include "Action.h"
#include <memory>

class Service
{
private:
	AdminRepo& adminRepo;
	FileWatchlist* watchList;
	std::vector<std::unique_ptr<Action>> undoStack;
	std::vector<std::unique_ptr<Action>> redoStack;


public:
	Service(AdminRepo& adminRepo, FileWatchlist* watchList) : adminRepo(adminRepo), watchList(watchList) {}
	~Service() { delete watchList; }


	/*
	* adds a movie to the adminRepo if all the data is valid
	*/
	void addMovieAdmin(const std::string& title, const std::string& genre, const int year, const int nrLikes, const std::string& trailerLink);

	/*
	* adds a movie to the userRepo if all the data is valid
	*/
	void addMovieUser(Movie& movie);
	/*
	* removes a movie from the adminRepo if all the data is valid
	*/
	void removeMovieAdmin(const std::string& title, const int year);


	/*
	* removes a movie from the userRepo if all the data is valid
	*/
	void removeMovieUser(const std::string& title, const int year);

	/*
	* updates a movie from the adminRepo if all the data is valid
	*/
	void updateMovie(const std::string& title, const std::string& genre, const int year, const int nrLikes, const std::string& trailerLink);


	void undo();
	void redo();


	/*
	* gets all the movies from the adminRepo
	*/
	std::vector<Movie> getMovies()const { return this->adminRepo.getMovies(); }


	/*
	* gets all the movies from the userRepo
	*/
	std::vector<Movie> getWatchList()const { return this->watchList->getMovies(); }

	/*
	* gets all the movies from the adminRepo that have the given genre
	*/
	std::vector<Movie> getMoviesByGender(const std::string& genre);

	/*
	* likes the movie that has the given title and year
	*/
	void likeMovie(const std::string& title, const int year);

	/*
	* generates 10 movies at the start
	*/
	void generateMovies();

	void saveWatchlist(const std::string& filename);
	void openWatchlist() const;

private:

	/*
	* validates all the data of the movie
	*/
	void validateMovie(const std::string& title, const std::string& genre, const int year, const int nrLikes, const std::string& trailerLink)const;

	/*
	* validates the title of the movie
	*/
	void validateTitle(const std::string& title)const;


	/*
	* validates the genre of the movie
	*/
	void validateGenre(const std::string& genre)const;


	/*
	* validates the year of release of the movie
	*/
	void validateYear(const int year)const;

	/*
	* validates the nr of likes of the movie
	*/
	void validateNrLikes(const int nrLikes)const;


	/*
	* validates the trailer link of the movie
	*/
	void validateTrailerLink(const std::string& trailerLink) const;

};
