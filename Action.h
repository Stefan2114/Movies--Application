#pragma once
#include "Repository.h"
class Action
{

protected:
	Movie movie;
	AdminRepo& repo;

public:
	Action(Movie& movie, AdminRepo& repo) : movie(movie), repo(repo) {}

	virtual void makeUndo() = 0;
	virtual void makeRedo() = 0;
	virtual ~Action() {}

};

class ActionAdd : public Action
{
public:

	ActionAdd(Movie& movie, AdminRepo& repo) : Action(movie, repo) {}
	void makeUndo() override;
	void makeRedo() override;
};

class ActionRemove : public Action
{
public:
	ActionRemove(Movie& movie, AdminRepo& repo) : Action(movie, repo) {}
	void makeUndo() override;
	void makeRedo() override;
};


class ActionUpdate : public Action
{
private:
	Movie secondMovie;
public:
	ActionUpdate(Movie& movie1, Movie& movie2, AdminRepo& repo) : Action(movie1, repo), secondMovie(movie2) {}
	void makeUndo() override;
	void makeRedo() override;
};

