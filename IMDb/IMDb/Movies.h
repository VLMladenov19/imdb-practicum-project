#pragma once

#include "StrUtils.h"
#include "Response.h"

struct Movie
{
	char* title;
	unsigned year;
	char* genre;
	char* director;
	char** cast;
	size_t castCount;

	Movie(const char* title, const unsigned year, 
		const char* genre, const char* director, char** cast, const unsigned castCount)
	{
		this->title = new char[strLen(title) + 1];
		strCopy(this->title, title);
		this->year = year;
		this->genre = new char[strLen(genre) + 1];
		strCopy(this->genre, genre);
		this->director = new char[strLen(director) + 1];
		strCopy(this->director, director);
		this->cast = new char*[castCount];
		for (size_t i = 0; i < castCount; i++)
		{
			this->cast[i] = new char[strLen(cast[i]) + 1];
			strCopy(this->cast[i], cast[i]);
		}
		this->castCount = castCount;
	}
};

Response addMovie(const Movie);

bool compareTitle(const char*, char**);
bool compareGenre(const char*, char**);
Movie** getMoviesBy(const char*,
	size_t&,
	bool(*)(const char*, char**) = [](const char*, char**) {return true; });

Movie** fixMatrixSize(Movie**, size_t);
