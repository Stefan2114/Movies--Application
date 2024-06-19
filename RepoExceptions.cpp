#include "RepoExceptions.h"


FileException::FileException(const std::string& message) : message(message)
{
}

const char* FileException::what()
{
	return this->message.c_str();
}

RepoException::RepoException(const std::string& message) : message(message)
{
}
RepoException::RepoException() : exception{}, message{ "" }
{
}
const char* RepoException::what()
{
	return this->message.c_str();
}

const char* DuplicateMovieException::what() const noexcept
{
	return "There is another movie with the same title and year!";
}

const char* InexistenMovieException::what() const noexcept
{
	return "There are no movies with the given title and year!";
}
