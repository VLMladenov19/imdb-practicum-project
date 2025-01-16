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

short chooseAction()
{
	char* input = writeStr();
	short action = strToNum(input);
	delete[] input;

	return action;
}

void chooseRole()
{
	short role = -1;
	while (true)
	{
		system("cls");
		std::cout << "Choose role\n";
		std::cout << "\t" << ADMIN_ACTION << ".Admin\n";
		std::cout << "\t" << USER_ACTION << ".User\n";
		std::cout << "\t" << EXIT_ACTION << ".Exit\n\n";

		std::cout << "Select role: ";
		role = chooseAction();

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
			std::cout << "Invalid value for role\n";
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
        std::cout << "\t" << ADMIN_SORT_FILTER_ACTION << ". Sort and filter by rating\n";
        std::cout << "\t" << EXIT_ACTION << ". Exit\n\n";

		std::cout << "Select action: ";
		short action = chooseAction();

		switch (action)
		{
		case ADMIN_ADD_MOVIE_ACTION:
			addMovieMenu();
			break;
		case ADMIN_SEARCH_BY_TITLE_ACTION:
			searchByMenu("Title", *compareTitle);
			break;
		case ADMIN_SEARCH_BY_GENRE_ACTION:
			searchByMenu("Genre", *compareGenre);
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
		case ADMIN_SORT_FILTER_ACTION:
			break;
		case EXIT_ACTION:
			exit(0);
			break;
		default:
			std::cout << "Invalid value for action\n";
			waitForKeyPress();
			break;
		}
	}
}

void addMovieMenu()
{
	system("cls");

	std::cout << "Add Movie\n\n";

	std::cout << "Title: ";
	char* title = writeStr();

	std::cout << "Year: ";
	short year;
	std::cin >> year;

	std::cout << "Genre: ";
	char* genre = writeStr();

	std::cout << "Director: ";
	char* director = writeStr();

	std::cout << "Cast Count: ";
	short castCount;
	std::cin >> castCount;

	char** cast = new char* [castCount];
	for (short i = 0; i < castCount; i++)
	{
		std::cout << "Cast Member "<< i + 1 << ": ";

		cast[i] = writeStr();

		if (!strCmp(cast[i], ""))
		{
			delete[] cast[i];
			i--;
			castCount;
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
}

void printMovies(Movie** movies, const size_t count)
{
	if (!movies) return;

	for (size_t i = 0; i < count; i++)
	{
		std::cout << "\t";
		std::cout << movies[i]->title << ", ";
		std::cout << movies[i]->year << ", ";
		std::cout << movies[i]->genre << ", ";
		std::cout << movies[i]->rating << ", ";
		std::cout << movies[i]->director;
		char* cast = join(movies[i]->cast, movies[i]->castCount, ", ");
		if(strCmp(cast, ""))
		{
			std::cout << ", " << cast;
		}
		std::cout << "\n";
		delete[] cast;
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

		std::cout << "Select movie by index: ";
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

	std::cout << "Current Title: " << movie->title << "\n";
	std::cout << "New Title: ";
	char* newTitle = writeStr();

	std::cout << "Current Year: " << movie->year << "\n";
	std::cout << "New Year: ";
	unsigned newYear;
	std::cin >> newYear;

	std::cout << "Current Genre: " << movie->genre << "\n";
	std::cout << "New Genre: ";
	char* newGenre = writeStr();

	std::cout << "Current Director: " << movie->director << "\n";
	std::cout << "New Director: ";
	char* newDirector = writeStr();

	std::cout << "Current Cast Count: " << movie->castCount << "\n";
	std::cout << "New Cast Count: ";
	size_t newCastCount;
	std::cin >> newCastCount;

	char** newCast = new char*[newCastCount];
	for (size_t i = 0; i < newCastCount; i++)
	{
		std::cout << "New Cast Member " << i + 1 << ": ";
		newCast[i] = writeStr();
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

	std::cout << "Rating(0-10): ";
	char* ratingStr = writeStr();
	float ratingFloat = strToFloat(ratingStr);
	delete[] ratingStr;

	Response response = addRating(movieIndex, ratingFloat);

	if (!response.isSuccessful)
	{
		std::cerr << response.message << "\n";
		waitForKeyPress();
	}
}
