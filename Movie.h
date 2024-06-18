#pragma once
#include <string>

class Movie
{
private:
	std::string title;
	std::string genre;
	int year;
	int nrLikes;
	std::string trailerLink;

public:
	Movie(const std::string& title, const std::string& genre, const int year, const int nrLikes, const std::string& trailerLink)
		:title(title), genre(genre), year(year), nrLikes(nrLikes), trailerLink(trailerLink) {}

	Movie(): year(0), nrLikes(0) {}

	Movie(const Movie& movie);

	~Movie() {}
	std::string getTitle() const { return title; }
	std::string getGenre() const { return genre; }
	int getYear() const { return year; }
	int getNrLikes() const { return nrLikes; }
	std::string getTrailerLink() const { return trailerLink; }

	void setGenre(const std::string& newGenre) { this->genre = newGenre; }
	void setNrLikes(const int newNrLikes) { this->nrLikes = newNrLikes; }
	void setTrailerLink(const std::string& newTrailerLink) { this->trailerLink = newTrailerLink; }

	const std::string toString() const;

	bool operator==(const Movie& movie) const;

	void play();

	friend std::istream& operator>>(std::istream& stream, Movie& movie);
	friend std::ostream& operator<<(std::ostream& stream, const Movie& movie);
	

};
