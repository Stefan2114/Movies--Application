#include "Action.h"

void ActionAdd::makeUndo()
{
	repo.remove(movie.getTitle(), movie.getYear());
}

void ActionAdd::makeRedo()
{
	repo.add(movie);
}

void ActionRemove::makeUndo()
{
	repo.add(movie);
}

void ActionRemove::makeRedo()
{
	repo.remove(movie.getTitle(), movie.getYear());
}

void ActionUpdate::makeUndo()
{
	repo.update(movie.getTitle(), movie.getGenre(), movie.getYear(), movie.getNrLikes(), movie.getTrailerLink());
}

void ActionUpdate::makeRedo()
{
	repo.update(secondMovie.getTitle(), secondMovie.getGenre(), secondMovie.getYear(), secondMovie.getNrLikes(), secondMovie.getTrailerLink());
}
