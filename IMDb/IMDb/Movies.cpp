#include <iostream>
#include <fstream>

#include "Movies.h"
#include "Response.h"
#include "Constants.h"

Response addMovie(const Movie* movie)
{
	std::ofstream file(MOVIES_FILE, std::ios::app);

	if (!file.is_open())
	{
		return Response(false, "Error: File not found");
	}

    file << movie->title << "#" << movie->year << "#" << movie->genre << "#" << 
		movie->ratingsCount << "#" << movie->rating << "#" << 
		movie->director << "#" << movie->castCount;
	for (size_t i = 0; i < movie->castCount; i++)
	{
		file << "#" << movie->cast[i];
	}
	file << "\n";

	file.close();
	return Response(true, "Movie added successfully.");
}

Response removeAllMovies()
{
	std::ofstream file(MOVIES_FILE, std::ios::out | std::ios::trunc);

	if (!file.is_open())
	{
		return Response(false, "Error: File not found. Movies not removed.");
	}

	file.close();
	return Response(true, "All movies removed successfully.");
}

Response removeMovie(const size_t movieIndex)
{
	size_t moviesCount = 0;
	Movie** movies = getMoviesBy("", moviesCount);

	Response removeMoviesResponse = removeAllMovies();

	if (!removeMoviesResponse.isSuccessful)
	{
		freeMovieArray(movies, moviesCount);
		return removeMoviesResponse;
	}

	Response addMovieResponse(true, "Success");
	for (int i = 0; i < moviesCount; i++)
	{
		if (i != movieIndex)
		{
			addMovieResponse = addMovie(movies[i]);

			if (!addMovieResponse.isSuccessful)
			{
				freeMovieArray(movies, moviesCount);
				return addMovieResponse;
			}
		}
	}

	freeMovieArray(movies, moviesCount);
	return Response(true, "Movie removed successfully.");
}

Response updateMovie(const size_t movieIndex, const Movie* newMovie)
{
	if (!newMovie) return Response(false, "Error: Invalid movie for updating.");

	Response removeMovieResponse = removeMovie(movieIndex);
	if (!removeMovieResponse.isSuccessful)
	{
		return removeMovieResponse;
	}

	Response addNewMovieResponse = addMovie(newMovie);
	if (!addNewMovieResponse.isSuccessful)
	{
		return addNewMovieResponse;
	}

	return Response(true, "Movie successfully updated.");
}

Movie* getMovie(const size_t movieIndex)
{
	size_t moviesCount = 0;
	Movie** movies = getMoviesBy("", moviesCount);

	if (movieIndex < 0 || movieIndex >= moviesCount)
	{
		return nullptr;
	}

	return new Movie(
		movies[movieIndex]->title,
		movies[movieIndex]->year,
		movies[movieIndex]->genre,
		movies[movieIndex]->ratingsCount,
		movies[movieIndex]->rating,
		movies[movieIndex]->director,
		movies[movieIndex]->castCount,
		movies[movieIndex]->cast
	);
}

float calculateNewRating(const Movie* movie, const float newRating)
{
	float floatRating = (movie->rating * movie->ratingsCount + newRating) 
		/ (movie->ratingsCount + 1);
	int intRating = floatRating * 100;
	return intRating / 100.0f;
}

bool compareTitle(const char* title, char** movie)
{
	return strCaseContains(movie[TITLE_INDEX], title);
}

bool compareGenre(const char* genre, char** movie)
{
	return strCaseContains(movie[GENRE_INDEX], genre);
}

Movie** getMoviesBy(const char* search, size_t& moviesCount,
	bool (*searchFunc)(const char*, char**))
{
	if (!search || !searchFunc) return nullptr;

	std::ifstream file(MOVIES_FILE);

	Movie** movies = new Movie*[STR_SIZE];
	moviesCount = 0;
	char line[STR_SIZE + 1];
	while (file.getline(line, STR_SIZE))
	{
		size_t infoCount = 0;
		char** movieInfo = split(line, '#', infoCount);
		size_t castCount = strToNum(movieInfo[CAST_COUNT_INDEX]);
		char** cast = new char* [castCount];
		for (size_t i = 0; i < castCount; i++)
		{
			cast[i] = new char[strLen(movieInfo[CAST_INDEX + i]) + 1];
			strCopy(cast[i], movieInfo[CAST_INDEX + i]);
		}

		if (!searchFunc(search, movieInfo))
		{
			freeStrArray(movieInfo, infoCount);
			freeStrArray(cast, castCount);
			continue;
		}

		Movie* movie = new Movie(movieInfo[TITLE_INDEX],
			strToNum(movieInfo[YEAR_INDEX]),
			movieInfo[GENRE_INDEX],
			strToNum(movieInfo[RATING_COUNT_INDEX]),
			strToFloat(movieInfo[RATING_INDEX]),
			movieInfo[DIRECTORT_INDEX],
			castCount,
			cast);
		movies[moviesCount++] = movie;
		freeStrArray(movieInfo, infoCount);
		freeStrArray(cast, castCount);
	}

	movies = fixMatrixSize(movies, moviesCount);

	return movies;
}

Response addRating(const size_t movieIndex, const float newRating)
{
	Movie* movie = getMovie(movieIndex);

	if (!movie)
	{
		return Response(false, "Error: Invalid movie index.");
	}

	movie->rating = calculateNewRating(movie, newRating);
	movie->ratingsCount++;

	Response response = updateMovie(movieIndex, movie);

	freeMovie(movie);
	if (!response.isSuccessful)
	{
		return response;
	}

	return Response(true, "Movie rated successfully.");
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
			movies[i]->ratingsCount,
			movies[i]->rating,
			movies[i]->director,
			movies[i]->castCount,
			movies[i]->cast);
		fixed[i] = temp;
		delete[] movies[i];
	}
	delete[] movies;

	return fixed;
}

void freeMovie(Movie* movie)
{
	if (!movie) return;

	delete[] movie->title;
	delete[] movie->genre;
	delete[] movie->director;
	freeStrArray(movie->cast, movie->castCount);
	delete movie;
}

void freeMovieArray(Movie** movies, size_t count)
{
	if (!movies) return;

	for (size_t i = 0; i < count; i++)
	{
		freeMovie(movies[i]);
	}
	delete[] movies;
}