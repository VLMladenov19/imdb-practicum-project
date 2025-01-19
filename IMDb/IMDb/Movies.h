/**
*
* Solution to course project # 06 - IMDb
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Vasil Mladenov
* @idnumber 5MI0600475
* @compiler VC
*
* Header file for all declarations of movies related functions
*
*/

#pragma once

#include "StrUtils.h"
#include "Response.h"

struct Movie
{
	char* title;
	short year;
	char* genre;
	unsigned ratingsCount;
	float rating;
	char* director;
	short castCount;
	char** cast;

	Movie(const char* title, const short year, 
		const char* genre, const unsigned ratingsCount, 
		const float rating, const char* director, 
		const short castCount, char** cast)
	{
		this->title = new char[strLen(title) + 1];
		strCopy(this->title, title);
		this->year = year;
		this->genre = new char[strLen(genre) + 1];
		strCopy(this->genre, genre);
		this->ratingsCount = ratingsCount;
		this->rating = rating;
		this->director = new char[strLen(director) + 1];
		strCopy(this->director, director);
		this->castCount = castCount;
		this->cast = new char*[castCount];
		for (short i = 0; i < castCount; i++)
		{
			this->cast[i] = new char[strLen(cast[i]) + 1];
			strCopy(this->cast[i], cast[i]);
		}
	}
};

// Functions accessing file with movies
Response addMovie(const Movie* movie);
Response removeAllMovies();
Response removeMovie(const size_t movieIndex);
Response updateMovie(const size_t movieIndex, const Movie* newMovie);
Movie* getMovie(const size_t movieIndex);

bool matchTitle(const char* title, char** movie);
bool matchGenre(const char* genre, char** movie);
Movie** getMoviesBy(const char* search, size_t& moviesCount,
	bool(*searchFunc)(const char*, char**) = [](const char*, char**) { return true; });

float calculateNewRating(const Movie* movie, const float newRating);
Response addRating(const size_t movieIndex, const float newRating);

void swapMovies(Movie*& movie1, Movie*& movie2);
void reverseMovies(Movie** movies, const size_t moviesCount);
int compareTitle(Movie* movie1, Movie* movie2);
int compareGenre(Movie* movie1, Movie* movie2);
void sortBy(Movie** movies, const size_t moviesCount, 
	int (*compare)(Movie*, Movie*) = [](Movie*, Movie*) { return 0; });

// Functions handling dynamic memory related to the Movie struct
Movie** fixMatrixSize(Movie** movies, size_t moviesCount);
void freeMovie(Movie* movie);
void freeMovieArray(Movie** movies, size_t count);