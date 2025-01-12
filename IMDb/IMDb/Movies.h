#pragma once

#include "StrUtils.h"
#include "Response.h"

struct Movie
{
	char* title;
	unsigned year;
	char* genre;
	char* director;
	char* cast;

	Movie(const char* title, const unsigned year, 
		const char* genre, const char* director, const char* cast)
	{
		this->title = new char[strLen(title) + 1];
		strCopy(this->title, title);
		this->year = year;
		this->genre = new char[strLen(genre) + 1];
		strCopy(this->genre, genre);
		this->director = new char[strLen(director) + 1];
		strCopy(this->director, director);
		this->cast = new char[strLen(cast) + 1];
		strCopy(this->cast, cast);
	}
};

Response addMovie(const Movie);
Movie** fixMatrixSize(Movie**, size_t);

bool compareTitle(const char*, char**);
bool compareGenre(const char*, char**);
Movie** getMoviesBy(const char*,
	size_t&,
	bool(*)(const char*, char**) = [](const char*, char**) {return true; });