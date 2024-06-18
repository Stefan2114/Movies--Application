#include "Tests.h"
#include "Service.h"
#include <cassert>
using namespace std;


void testMovie()
{
	//test movies
	Movie movie1("Inception", "Science Fiction/Thriller", 2010, 5000, "https://www.youtube.com/watch?v=YoHD9XEInc0");
	Movie movie2("The Shawshank Redemption", "Drama/Crime", 1994, 8200, "https://www.youtube.com/watch?v=6hB3S9bIaco");
	Movie movie3("Pulp Fiction", "Crime/Drama", 1994, 3500, "https://www.youtube.com/watch?v=s7EdQ4FqbhY");
	Movie movie4("The Dark Knight", "Action/Crime", 2008, 6700, "https://www.youtube.com/watch?v=EXeTwQWrcwY");
	Movie movie5("Forrest Gump", "Drama/Romance", 1994, 9100, "https://www.youtube.com/watch?v=bLvqoHBptjg");
	assert(movie1.getTitle() == "Inception");
	assert(movie1.getGenre() == "Science Fiction/Thriller");
	assert(movie1.getYear() == 2010);
	assert(movie1.getNrLikes() == 5000);
	assert(movie1.getTrailerLink() == "https://www.youtube.com/watch?v=YoHD9XEInc0");

	movie1.setGenre("Drama");
	movie1.setNrLikes(10);
	movie1.setTrailerLink("https://www.youtube.com/watc");
	assert(movie1.getGenre() == "Drama");
	assert(movie1.getNrLikes() == 10);
	assert(movie1.getTrailerLink() == "https://www.youtube.com/watc");
	string output = "Title: " + movie1.getTitle() + '\n' + "Genre: " + movie1.getGenre() + '\n' + "Year or release: " + to_string(movie1.getYear()) + '\n' + "Number of likes: " + to_string(movie1.getNrLikes()) + '\n' + "Trailer link: " + movie1.getTrailerLink() + '\n';
	//assert(movie1.toString() == output);

}



void testRepo()
{
	//test constructor
	string repoFile("tests.txt");
	AdminRepo repository(repoFile);

	Movie movie1("Inception", "Science Fiction/Thriller", 2010, 5000, "https://www.youtube.com/watch?v=YoHD9XEInc0");
	Movie movie2("The Shawshank Redemption", "Drama/Crime", 1994, 8200, "https://www.youtube.com/watch?v=6hB3S9bIaco");
	Movie movie3("Pulp Fiction", "Crime/Drama", 1994, 3500, "https://www.youtube.com/watch?v=s7EdQ4FqbhY");
	Movie movie4("The Dark Knight", "Action/Crime", 2008, 6700, "https://www.youtube.com/watch?v=EXeTwQWrcwY");
	Movie movie5("Forrest Gump", "Drama/Romance", 1994, 9100, "https://www.youtube.com/watch?v=bLvqoHBptjg");


	//test add
	repository.add(movie1);
	repository.add(movie2);
	repository.add(movie3);
	repository.add(movie4);
	repository.add(movie5);
	try {
		Movie movie6("Forrest Gump", "Action", 1994, 1000, "https://vnwjonjkew");
		repository.add(movie6);}
	catch (const exception& e) 
	{ assert(true); }
	vector<Movie> vector = repository.getMovies();
	assert(vector[0].getTitle() == "Inception");
	assert(vector[1].getGenre() == "Drama/Crime");
	assert(vector[2].getYear() == 1994);
	assert(vector[3].getNrLikes() == 6700);


	//test delete
	repository.remove("Inception", 2010);
	vector = repository.getMovies();
	assert(vector[0].getTitle() == "The Shawshank Redemption");
	assert(vector[0].getGenre() == "Drama/Crime");
	assert(vector[0].getYear() == 1994);
	assert(vector[0].getNrLikes() == 8200);
	assert(vector[0].getTrailerLink() == "https://www.youtube.com/watch?v=6hB3S9bIaco");
	try {
		repository.remove("Inception", 2010);
	}
	catch (const exception& e) { assert(true); }
	

	//test update
	
	repository.update("The Shawshank Redemption", "Crime/Drama", 1994, 200, "https://www.youtube.com/watch");
	vector = repository.getMovies();
	assert(vector[0].getTitle() == "The Shawshank Redemption");
	assert(vector[0].getGenre() == "Crime/Drama");
	assert(vector[0].getYear() == 1994);
	assert(vector[0].getNrLikes() == 200);
	assert(vector[0].getTrailerLink() == "https://www.youtube.com/watch");
	try {
		repository.update("The Shawshank Redemption", "Crime/Drama", 19, 200, "https://www.youtube.com/watch");
	}
	catch (const exception& e) { assert(true); }

	//test like
	repository.likeMovie("The Shawshank Redemption", 1994);
	vector = repository.getMovies();
	assert(vector[0].getNrLikes() == 201);
	try {
		repository.likeMovie("The Shawshank Redemption", 19);
	}
	catch (const exception& e) { assert(true); }
	
}

void testService()
{
	////test constructor
	//string repoFile("tests.txt");
	//AdminRepo repository(repoFile);
	//FileWatchlist* watchlist = new CSVWatchlist();
	////Service service(repository);
	////service.generateMovies();

	////test add
	//service.addMovieAdmin("Never give up", "Action", 2010, 100000, "https://www.cokwnvokno");
	//vector<Movie> vector = service.getMovies();
	//assert(vector.size() == 11);
	//assert(vector[10].getTitle() == "Never give up");
	//assert(vector[10].getGenre() == "Action");
	//assert(vector[10].getYear() == 2010);
	//assert(vector[10].getNrLikes() == 100000);
	//assert(vector[10].getTrailerLink() == "https://www.cokwnvokno");
	//try {
	//	service.addMovieAdmin("Inception", "Comedy", 2010, 1000, "https://cwnoknvfoew");
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}
	//try {
	//	service.addMovieAdmin("I", "Comedy", 2010, 1000, "https://cwnoknvfoew");
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}
	//try {
	//	service.addMovieAdmin("Inception", "C", 2010, 1000, "https://cwnoknvfoew");
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}


	////test remove
	//assert(vector[0].getTitle() == "Inception");
	//assert(vector[0].getGenre() == "Science Fiction/Thriller");
	//assert(vector[0].getYear() == 2010);


	//service.removeMovieAdmin("Inception", 2010);
	//vector = service.getMovies();
	//assert(vector[0].getTitle() == "The Shawshank Redemption");
	//assert(vector[0].getGenre() == "Drama/Crime");
	//assert(vector[0].getYear() == 1994);
	//assert(vector[0].getNrLikes() == 8200);
	//assert(vector[0].getTrailerLink() == "https://www.youtube.com/watch?v=6hB3S9bIaco");
	//try {
	//	service.removeMovieAdmin("Inception", 2010);
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}
	//try {
	//	service.removeMovieAdmin("The Shawshank Redemption", -10);
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}

	////test update
	//service.updateMovie("The Shawshank Redemption", "Crime", 1994, 800, "https://www.youtube.com/watch?v");
	//vector = service.getMovies();
	//assert(vector[0].getTitle() == "The Shawshank Redemption");
	//assert(vector[0].getGenre() == "Crime");
	//assert(vector[0].getYear() == 1994);
	//assert(vector[0].getNrLikes() == 800);
	//assert(vector[0].getTrailerLink() == "https://www.youtube.com/watch?v");
	//try {
	//	service.updateMovie("The Shawshank", "Crime", 1994, 800, "https://www.youtube.com/watch?v");
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}
	//try {
	//	service.updateMovie("The Shawshank Redemption", "Crime", 1994, -100, "https://www.youtube.com/watch?v");
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}
	//try {
	//	service.updateMovie("The Shawshank Redemption", "Crime", 1994, 800, "htt://www.youtube.com/watch?v");
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}
	//try {
	//	service.updateMovie("The Shawshank Redemption", "Crime", 1994, 800, "https://");
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}
	//try {
	//	service.updateMovie("The Shawshank Redemption", "Crime", 1994, 800, "https://www.youtube.com/watch?vncwonvfnenvldnvlndkmvnkenviknepiknfpiknpnvpwnpgn");
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}
	//try {
	//	service.updateMovie("The Shawshank Redemption mkpsm pmsponvoieionklfnkwncnklsnclsmnkclnsklnvfklwnwkcnkwnmvklmn", "Crime", 1994, 800, "htt://www.youtube.com/watch?v");
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}
	//try {
	//	service.updateMovie("The Shawshank Redemption", "vncownvonwmnvfpmvpmswpvmcpwmcpmwpckopswmvkpmspmvp", 1994, 800, "htt://www.youtube.com/watch?v");
	//}
	//catch (const exception& e) {
	//	assert(true);
	//}


	////test like
	//service.likeMovie("The Shawshank Redemption", 1994);


	////test get movies with a genre
	//vector = service.getMoviesByGender("Drama");
	//for (auto it = vector.begin(); it != vector.end(); ++it)
	//	assert((*it).getGenre().find("Drama") != string::npos);

}

void testAll()
{
	testMovie();
	testRepo();
	testService();
}
