#include "Movie.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

Movie::Movie(const Movie& movie)
{
	this->title = movie.getTitle();
	this->genre = movie.getGenre();
	this->year = movie.getYear();
	this->nrLikes = movie.getNrLikes();
	this->trailerLink = movie.getTrailerLink();
}

const string Movie::toString() const
{
	std::string output;
	output += title + ", " + genre + ", " + std::to_string(year) + ", " + std::to_string(nrLikes) + ", " + trailerLink;
	return output;
}

bool Movie::operator==(const Movie& movie) const
{
	return this->title == movie.getTitle() && this->year == movie.getYear();
}



/*
	Tokenizes a string.
	Input:	str - the string to be tokenized.
			delimiter - char - the delimiter used for tokenization
	Output: a vector of strings, containing the tokens
*/

vector<string> tokenize(const string& str, char delimiter)
{
	vector <string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream& operator>>(std::istream& is, Movie& movie)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 5) // make sure all the starship data was valid
		return is;
	movie.title = tokens[0];
	movie.genre = tokens[1];
	movie.year = stoi(tokens[2]);
	movie.nrLikes = stoi(tokens[3]);
	movie.trailerLink = tokens[4];

	return is;
}

std::ostream& operator<<(std::ostream& os, const Movie& movie)
{
	os << movie.getTitle() << "," << movie.getGenre() << ","<<movie.getYear() << "," << movie.getNrLikes() << ","<< movie.getTrailerLink() << "\n";
	return os;
}

void Movie::play()
{
	system(string("start " + this->trailerLink).c_str());
}
