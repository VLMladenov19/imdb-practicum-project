#include <iostream>
#include <fstream>

#include "Response.h"
#include "Movies.h"
#include "Constants.h"

Response addMovie(const Movie movie)
{
	// Directory has to be created for code to work
	std::ofstream file("files/movies.txt", std::ios::app);

	if (!file.is_open())
	{
		return Response(false, "Error: File not found");
	}

	file << movie.title << "," << movie.year << "," << movie.genre << "," <<
		movie.director << "," << movie.cast << "\n";

	file.close();
	return Response(true, "Success");
}

bool compareTitle(const char* title, char** movie)
{
	// if title is shorter or equal return true
	return strCmp(title, movie[TITLE_INDEX]) <= 0 && title[0] == movie[TITLE_INDEX][0];
}

bool compareGenre(const char* genre, char** movie)
{
	return strCmp(genre, movie[GENRE_INDEX]) <= 0 && genre[0] == movie[GENRE_INDEX][0];
}

Movie** getMoviesBy(const char* search,
	bool (*searchFunc)(const char*, char**),
	size_t& moviesCount)
{
	if (!search || !searchFunc) return nullptr;

	std::ifstream file("files/movies.txt");

	Movie** movies = new Movie*[STR_SIZE];
	moviesCount = 0;
	char line[STR_SIZE + 1];
	while (file.getline(line, STR_SIZE))
	{
		size_t infoCount = 0;
		char** movieInfo = split(line, ',', infoCount);

		if (!searchFunc(search, movieInfo))
		{
			freeMemory(movieInfo, infoCount);
			continue;
		}

		Movie* movie = new Movie(movieInfo[TITLE_INDEX], 
			strToNum(movieInfo[YEAR_INDEX]),
			movieInfo[GENRE_INDEX], 
			movieInfo[DIRECTORT_INDEX],
			movieInfo[CAST_INDEX]);
		movies[moviesCount++] = movie;
		freeMemory(movieInfo, infoCount);
	}

	movies = fixMatrixSize(movies, moviesCount);

	return movies;
}

Movie** fixMatrixSize(Movie** movies, size_t count)
{
	if (!movies) return nullptr;

	Movie** fixed = new Movie*[count];
	for (size_t i = 0; i < count; i++)
	{
		Movie* temp = new Movie(movies[i]->title,
			movies[i]->year,
			movies[i]->genre,
			movies[i]->director,
			movies[i]->cast);
		fixed[i] = temp;
		delete[] movies[i];
	}
	delete[] movies;

	return fixed;
}