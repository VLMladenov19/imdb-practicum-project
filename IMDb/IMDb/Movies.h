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
	unsigned year;
	char* genre;
	unsigned ratingsCount;
	float rating;
	char* director;
	size_t castCount;
	char** cast;

	Movie(const char* title, const unsigned year, 
		const char* genre, const unsigned ratingsCount, 
		const float rating, const char* director, 
		const unsigned castCount, char** cast)
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
		for (size_t i = 0; i < castCount; i++)
		{
			this->cast[i] = new char[strLen(cast[i]) + 1];
			strCopy(this->cast[i], cast[i]);
		}
	}
};

Response addMovie(const Movie*);
Response removeAllMovies();
Response removeMovie(const size_t);
Response updateMovie(const size_t, const Movie*);
Movie* getMovie(const size_t);

float calculateNewRating(const Movie*, const float);

bool compareTitle(const char*, char**);
bool compareGenre(const char*, char**);
Movie** getMoviesBy(const char*,
	size_t&,
	bool(*)(const char*, char**) = [](const char*, char**) 
	{return true;});
Response addRating(const size_t, const float);

Movie** fixMatrixSize(Movie**, size_t);
void freeMovie(Movie*);
void freeMovieArray(Movie**, size_t);