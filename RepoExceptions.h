#pragma once
#include <exception>
#include <string>

class FileException : public std::exception
{
protected:
	std::string message;
public:
	FileException(const std::string& message);
	~FileException() {}
	const char* what();
};

class RepoException : public std::exception
{
protected:
	std::string message;
public:
	RepoException();
	RepoException(const std::string& message);
	virtual ~RepoException() {}
	virtual const char* what();
};

class DuplicateMovieException : public RepoException
{
public:
	const char* what() const noexcept override;
};

class InexistenMovieException : public RepoException
{
public:
	const char* what() const noexcept override;
};

