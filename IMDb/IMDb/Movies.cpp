#include <iostream>
#include <fstream>

#include "Response.h"
#include "Movies.h"

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