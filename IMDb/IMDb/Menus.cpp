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
* File with all printable menus
*
*/

#include <iostream>

#include "Menus.h"
#include "Constants.h"
#include "StrUtils.h"
#include "Movies.h"

void waitForKeyPress()
{
	std::cout << "\nPress enter to continue...\n";
	std::cin.get();
}

void chooseRole()
{
	short role = -1;
	while (true)
	{
		system("cls");
		std::cout << "Choose role\n\n";
		std::cout << "\t" << ADMIN_ACTION << ".Admin\n";
		std::cout << "\t" << USER_ACTION << ".User\n";
		std::cout << "\t" << EXIT_ACTION << ".Exit\n\n";

		std::cout << "Select role: ";
		role = writeNum();

		switch (role)
		{
		case ADMIN_ACTION:
			adminMenu();
			break;
		case USER_ACTION:
			//userMenu();
			break;
		case EXIT_ACTION:
			exit(0);
			return;
		default:
			std::cout << "\nInvalid value for role\n";
			waitForKeyPress();
			break;
		}
	}
}

void adminMenu()
{
	short action = -1;
	while(true)
	{
		system("cls");

		std::cout << "Admin Menu\n\n";
        std::cout << "\t" << ADMIN_ADD_MOVIE_ACTION << ". Add movie\n";
        std::cout << "\t" << ADMIN_SEARCH_BY_TITLE_ACTION << ". Search by title\n";
        std::cout << "\t" << ADMIN_SEARCH_BY_GENRE_ACTION << ". Search by genre\n";
        std::cout << "\t" << ADMIN_LIST_ALL_ACTION << ". List all\n";
        std::cout << "\t" << ADMIN_UPDATE_MOVIE_ACTION << ". Update movie\n";
        std::cout << "\t" << ADMIN_REMOVE_MOVIE_ACTION << ". Remove movie\n";
        std::cout << "\t" << ADMIN_RATE_MOVIE_ACTION << ". Rate movie\n";
        std::cout << "\t" << ADMIN_SORT_ACTION << ". Sort movies\n";
        std::cout << "\t" << ADMIN_FILTER_ACTION << ". Filter movies\n";
        std::cout << "\t" << EXIT_ACTION << ". Exit\n\n";

		std::cout << "Select action: ";
		short action = writeNum();

		switch (action)
		{
		case ADMIN_ADD_MOVIE_ACTION:
			addMovieMenu();
			break;
		case ADMIN_SEARCH_BY_TITLE_ACTION:
			searchByMenu("Title", matchTitle);
			break;
		case ADMIN_SEARCH_BY_GENRE_ACTION:
			searchByMenu("Genre", matchGenre);
			break;
		case ADMIN_LIST_ALL_ACTION:
			listAllMenu();
			break;
		case ADMIN_UPDATE_MOVIE_ACTION:
			updateMovieMenu();
			break;
		case ADMIN_REMOVE_MOVIE_ACTION:
			removeMovieMenu();
			break;
		case ADMIN_RATE_MOVIE_ACTION:
			rateMovieMenu();
			break;
		case ADMIN_SORT_ACTION:
			sortMoviesMenu();
			break;
		case ADMIN_FILTER_ACTION:
			filterMoviesMenu();
			break;
		case EXIT_ACTION:
			exit(0);
			break;
		default:
			std::cout << "\nInvalid value for action\n";
			waitForKeyPress();
			break;
		}
	}
}

bool isInputValid(const char* input, const short maxLength)
{
	size_t length = strLen(input);
	return length != 0 && length <= maxLength
		&& !strCaseContains(input, "#");
}

bool isYearValid(const short year)
{
	return YEAR_MIN <= year && year <= YEAR_MAX;
}

bool validateInput(const char* input, const short maxLength, const char* placeholder)
{
	if (!isInputValid(input, maxLength))
	{
		std::cout << "Invalid " << placeholder << ", must be up to "
			<< TITLE_MAX_LENGTH << " characters.\n";
		waitForKeyPress();
		return false;
	}
	return true;
}

bool validateYear(const short year)
{
	if (!isYearValid(year))
	{
		std::cout << "Invalid year, must be from "
			<< YEAR_MIN << " to " << YEAR_MAX << ".\n";
		waitForKeyPress();
		return false;
	}
	return true;
}

void addMovieMenu()
{
	while (true)
	{
		system("cls");

		std::cout << "Add Movie\n\n";

		std::cout << "Title: ";
		char* title = writeStr();
		if (!validateInput(title, TITLE_MAX_LENGTH, "title"))
		{
			delete[] title;
			continue;
		}

		std::cout << "Year: ";
		short year = writeNum();
		if (!validateYear(year))
		{
			delete[] title;
			continue;
		}

		std::cout << "Genre: ";
		char* genre = writeStr();
		if (!validateInput(genre, GENRE_MAX_LENGTH, "genre"))
		{
			delete[] title;
			delete[] genre;
			continue;
		}

		std::cout << "Director: ";
		char* director = writeStr();
		if (!validateInput(director, DIRECTOR_MAX_LENGTH, "director"))
		{
			delete[] title;
			delete[] genre;
			delete[] director;
			continue;
		}

		std::cout << "Cast Count: ";
		short castCount = writeNum();
		if (castCount == -1)
		{
			std::cout << "Invalid cast count.\n";
			waitForKeyPress();
			delete[] title;
			delete[] genre;
			delete[] director;
			continue;
		}

		char** cast = new char* [castCount];
		for (short i = 0; i < castCount; i++)
		{
			std::cout << "Cast Member " << i + 1 << ": ";

			cast[i] = writeStr();

			if (!validateInput(cast[i], CAST_MAX_LENGTH, "cast") || !strCmp(cast[i], ""))
			{
				delete[] cast[i];
				i--;
				continue;
			}
		}

		Movie* movie = new Movie(title, year, genre, 1, 5.0f, director, castCount, cast);
		Response response = addMovie(movie);

		delete[] title;
		delete[] genre;
		delete[] director;
		freeStrArray(cast, castCount);

		if (!response.isSuccessful)
		{
			std::cerr << "\n" << response.message << "\n";
			waitForKeyPress();
		}
		break;
	}
}

void printMovie(const Movie* movie)
{
	if (!movie) return;

	std::cout << "\t";
	std::cout << movie->title << ", ";
	std::cout << movie->year << ", ";
	std::cout << movie->genre << ", ";
	std::cout << movie->rating << ", ";
	std::cout << movie->director;
	char* cast = join(movie->cast, movie->castCount, ", ");
	if (strCmp(cast, ""))
	{
		std::cout << ", " << cast;
	}
	std::cout << "\n";
	delete[] cast;
}

void printMovies(Movie** movies, const size_t count)
{
	if (!movies) return;

	for (size_t i = 0; i < count; i++)
	{
		printMovie(movies[i]);
	}
}

void searchByMenu(const char* searchText, 
	bool (*searchFunc)(const char*, char**))
{
	system("cls");

	std::cout << "Search Movies by " << searchText << "\n\n";
	std::cout << searchText << ": ";
	char* search = writeStr();

	size_t moviesCount = 0;
	Movie** movies = getMoviesBy(search, moviesCount, *searchFunc);
	delete[] search;

	printMovies(movies, moviesCount);

	freeMovieArray(movies, moviesCount);
	waitForKeyPress();
}

void listAllMenu()
{
	system("cls");

	std::cout << "List all Movies\n\n";

    size_t moviesCount = 0;
    Movie** movies = getMoviesBy("", moviesCount);

	printMovies(movies, moviesCount);

	freeMovieArray(movies, moviesCount);
    waitForKeyPress();
}

size_t chooseMovieMenu()
{
	size_t moviesCount = 0;
	Movie** movies = getMoviesBy("", moviesCount);

	if (!movies) return -1;

	for (size_t i = 0; i < moviesCount; i++)
	{
		std::cout << "\t";
		std::cout << i + 1 << ". ";
		std::cout << movies[i]->title << ", ";
		std::cout << movies[i]->rating << "\n";
	}
	std::cout << "\t" << EXIT_ACTION << ". Cancel\n\n";

	std::cout << "Select movie by index: ";
	char* movieIndexStr = writeStr();
	size_t movieIndex = strToNum(movieIndexStr);
	delete[] movieIndexStr;

	while (movieIndex < 0 || movieIndex > moviesCount)
	{
		std::cout << "Invalid index\n";

		std::cout << "\nSelect movie by index: ";
		movieIndexStr = writeStr();
		movieIndex = strToNum(movieIndexStr);
		delete[] movieIndexStr;
	}

	freeMovieArray(movies, moviesCount);
	return movieIndex;
}

void updateMovieMenu()
{
	system("cls");

	std::cout << "Update Movie\n\n";
	// Minus 1 to match index of movies in file
	size_t movieIndex = chooseMovieMenu() - 1;

	if (movieIndex == EXIT_ACTION - 1)
	{
		return;
	}

	Movie* movie = getMovie(movieIndex);

	while(true)
	{
		system("cls");

		std::cout << "Update Movie\n\n";
		printMovie(movie);

		std::cout << "\nCurrent Title: " << movie->title << "\n";
		std::cout << "New Title: ";
		char* newTitle = writeStr();
		if (!validateInput(newTitle, TITLE_MAX_LENGTH, "title"))
		{
			delete[] newTitle;
			freeMovie(movie);
			continue;
		}

		std::cout << "Current Year: " << movie->year << "\n";
		std::cout << "New Year: ";
		short newYear = writeNum();
		if (!validateYear(newYear))
		{
			delete[] newTitle;
			freeMovie(movie);
			continue;
		}

		std::cout << "Current Genre: " << movie->genre << "\n";
		std::cout << "New Genre: ";
		char* newGenre = writeStr();
		if (!validateInput(newGenre, GENRE_MAX_LENGTH, "genre"))
		{
			delete[] newTitle;
			delete[] newGenre;
			freeMovie(movie);
			continue;
		}

		std::cout << "Current Director: " << movie->director << "\n";
		std::cout << "New Director: ";
		char* newDirector = writeStr();
		if (!validateInput(newDirector, DIRECTOR_MAX_LENGTH, "director"))
		{
			delete[] newTitle;
			delete[] newGenre;
			delete[] newDirector;
			freeMovie(movie);
			continue;
		}

		std::cout << "Current Cast Count: " << movie->castCount << "\n";
		std::cout << "New Cast Count: ";
		short newCastCount = writeNum();

		char** newCast = new char* [newCastCount];
		for (short i = 0; i < newCastCount; i++)
		{
			std::cout << "New Cast Member " << i + 1 << ": ";
			newCast[i] = writeStr();
			if (!validateInput(newCast[i], CAST_MAX_LENGTH, "cast") || !strCmp(newCast[i], ""))
			{
				delete[] newCast[i];
				i--;
				continue;
			}
		}

		Movie* newMovie = new Movie(
			newTitle,
			newYear,
			newGenre,
			movie->ratingsCount,
			movie->rating,
			newDirector,
			newCastCount,
			newCast);
		Response response = updateMovie(movieIndex, newMovie);

		delete[] newTitle;
		delete[] newGenre;
		delete[] newDirector;
		freeStrArray(newCast, newCastCount);
		freeMovie(movie);
		freeMovie(newMovie);

		if (!response.isSuccessful)
		{
			std::cerr << response.message << "\n";
			waitForKeyPress();
		}
		break;
	}
}

void removeMovieMenu()
{
	system("cls");

	std::cout << "Remove Movie\n\n";
	size_t movieIndex = chooseMovieMenu() - 1;

	if (movieIndex == EXIT_ACTION - 1)
	{
		return;
	}

	Response response = removeMovie(movieIndex);

	if (!response.isSuccessful)
	{
		std::cerr << response.message << "\n";
		waitForKeyPress();
	}
}

void rateMovieMenu()
{
	system("cls");

	std::cout << "Rate Movie\n\n";
	size_t movieIndex = chooseMovieMenu() - 1;

	if (movieIndex == EXIT_ACTION - 1)
	{
		return;
	}

	while (true)
	{
		std::cout << "Rating(0-10): ";
		char* ratingStr = writeStr();
		float ratingFloat = strToFloat(ratingStr);
		delete[] ratingStr;

		if (ratingFloat < RATING_MIN || ratingFloat > RATING_MAX)
		{
			std::cout << "Invalid rating, must be between 1 and 10.\n";
			waitForKeyPress();
			continue;
		}

		Response response = addRating(movieIndex, ratingFloat);

		if (!response.isSuccessful)
		{
			std::cerr << response.message << "\n";
			waitForKeyPress();
		}
		return;
	}
}

void sortMoviesMenu()
{
	size_t moviesCount = 0;
	Movie** movies = getMoviesBy("", moviesCount);
	while(true)
	{
		system("cls");
		std::cout << "Sort Movies\n\n";

		for (size_t i = 0; i < moviesCount; i++)
		{
			std::cout << "\t";
			std::cout << movies[i]->title << ", ";
			std::cout << movies[i]->genre << ", ";
			std::cout << movies[i]->rating << "\n";
		}

		std::cout << "\n\tSort by:\n";
		std::cout << "\t" << SORT_BY_TITLE_ASC << ". Title ASC\n";
		std::cout << "\t" << SORT_BY_TITLE_DESC << ". Title DESC\n";
		std::cout << "\t" << SORT_BY_GENRE_ASC << ". Genre ASC\n";
		std::cout << "\t" << SORT_BY_GENRE_DESC << ". Genre DESC\n";
		std::cout << "\t" << EXIT_ACTION << ". Cancel\n";
		std::cout << "\nSelect action: ";
		short action = writeNum();

		switch (action)
		{
		case SORT_BY_TITLE_ASC:
			sortBy(movies, moviesCount, compareTitle);
			break;
		case SORT_BY_TITLE_DESC:
			sortBy(movies, moviesCount, compareTitle);
			reverseMovies(movies, moviesCount);
			break;
		case SORT_BY_GENRE_ASC:
			sortBy(movies, moviesCount, compareGenre);
			break;
		case SORT_BY_GENRE_DESC:
			sortBy(movies, moviesCount, compareGenre);
			reverseMovies(movies, moviesCount);
			break;
		case EXIT_ACTION:
			freeMovieArray(movies, moviesCount);
			return;
		}
	}
}

void filterMoviesMenu()
{
	size_t moviesCount = 0;
	Movie** movies = getMoviesBy("", moviesCount);
	float minRating = 0.0f;
	while (true)
	{
		system("cls");
		std::cout << "Filter Movies\n\n";

		for (size_t i = 0; i < moviesCount; i++)
		{
			if (movies[i]->rating >= minRating)
			{
				std::cout << "\t";
				std::cout << movies[i]->title << ", ";
				std::cout << movies[i]->genre << ", ";
				std::cout << movies[i]->rating << "\n";
			}
		}

		std::cout << "\n\t-1 to exit.";
		std::cout << "\n\tMinimum Rating(0-10): ";
		char* ratingStr = writeStr();
		float ratingFloat = strToFloat(ratingStr);
		delete[] ratingStr;

		if (ratingFloat == -1)
		{
			freeMovieArray(movies, moviesCount);
			waitForKeyPress();
			return;
		}
		if (ratingFloat < RATING_MIN || ratingFloat > RATING_MAX)
		{
			std::cout << "\nInvalid rating value.";
			waitForKeyPress();
			continue;
		}
		minRating = ratingFloat;
	}
}