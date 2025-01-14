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

	file << movie.title << "#" << movie.year << "#" << movie.genre << "#" <<
		movie.director << "#";
	for (size_t i = 0; i < movie.castCount; i++)
	{
		file << movie.cast[i] << "#";
	}
	file << movie.castCount << "\n";

	file.close();
	return Response(true, "Success");
}

bool compareTitle(const char* title, char** movie)
{
	//// if title is shorter or equal return true
	//return strCaseCmp(title, movie[TITLE_INDEX]) <= 0 && 
	//	toLower(title[0]) == toLower(movie[TITLE_INDEX][0]);
	return strCaseContains(movie[TITLE_INDEX], title);
}

bool compareGenre(const char* genre, char** movie)
{
	//return strCaseCmp(genre, movie[GENRE_INDEX]) <= 0 && 
	//	toLower(genre[0]) == toLower(movie[GENRE_INDEX][0]);
	return strCaseContains(movie[GENRE_INDEX], genre);
}

Movie** getMoviesBy(const char* search,
	size_t& moviesCount,
	bool (*searchFunc)(const char*, char**))
{
	if (!search || !searchFunc) return nullptr;

	std::ifstream file("files/movies.txt");

	Movie** movies = new Movie*[STR_SIZE];
	moviesCount = 0;
	char line[STR_SIZE + 1];
	while (file.getline(line, STR_SIZE))
	{
		size_t infoCount = 0;
		char** movieInfo = split(line, '#', infoCount);
		size_t castCount = strToNum(movieInfo[infoCount - 1]);
		char** cast = new char* [castCount];
		for (size_t i = 0; i < castCount; i++)
		{
			cast[i] = new char[strLen(movieInfo[CAST_INDEX + i]) + 1];
			strCopy(cast[i], movieInfo[CAST_INDEX + i]);
		}

		if (!searchFunc(search, movieInfo))
		{
			freeMemory(movieInfo, infoCount);
			continue;
		}

		Movie* movie = new Movie(movieInfo[TITLE_INDEX], 
			strToNum(movieInfo[YEAR_INDEX]),
			movieInfo[GENRE_INDEX], 
			movieInfo[DIRECTORT_INDEX],
			cast,
			castCount);
		movies[moviesCount++] = movie;
		freeMemory(movieInfo, infoCount);
		freeMemory(cast, castCount);
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
		Movie* temp = new Movie(
			movies[i]->title,
			movies[i]->year,
			movies[i]->genre,
			movies[i]->director,
			movies[i]->cast,
			movies[i]->castCount);
		fixed[i] = temp;
		delete[] movies[i];
	}
	delete[] movies;

	return fixed;
}