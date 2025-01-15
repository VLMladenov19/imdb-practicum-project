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
		std::cout << "Choose role:\n";
		std::cout << "\t1. Admin\n";
		std::cout << "\t2. User\n";

		role = chooseAction();

		switch (role)
		{
		case ADMIN_VALUE:
			adminMenu();
			return;
		case USER_VALUE:
			//userMenu();
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
		std::cout << "Select action:\n";
		std::cout << "\t1. Add movie\n";
		std::cout << "\t2. Search by title\n";
		std::cout << "\t3. Search by genre\n";
		std::cout << "\t4. List all\n";
		std::cout << "\t5. Update movie\n";
		std::cout << "\t6. Remove movie\n";
		std::cout << "\t7. Review movie\n";
		std::cout << "\t8. Sort and filter by rating\n";
		std::cout << "\t9. Exit\n";

		short action = chooseAction();

		switch (action)
		{
		case 1:
			addMovieMenu();
			break;
		case 2:
			searchByMenu("Title", *compareTitle);
			break;
		case 3:
			searchByMenu("Genre", *compareGenre);
			break;
		case 4:
			listAllMenu();
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			exit(0);
			break;
		default:
			std::cout << "Invalid value for action\n";
			break;
		}
	}
}

void addMovieMenu()
{
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

	std::cout << "Cast: ";
	char** cast = new char* [castCount];
	for (short i = 0; i < castCount; i++)
	{
		std::cout << (i ? '\t' : '\0');

		cast[i] = writeStr();

		if (!strCmp(cast[i], "\n"))
		{
			delete[] cast[i];
			i--;
			castCount--;
		}
	}

	Response response = addMovie(Movie(title, year, genre, 1, 5.0f, director, castCount, cast));

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
		strCmp(cast, "") ? std::cout << ", " << cast << "\n" : std::cout << "\n";
		delete[] cast;
	}
}

void searchByMenu(const char* searchText, 
	bool (*searchFunc)(const char*, char**))
{
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
    size_t moviesCount = 0;
    Movie** movies = getMoviesBy("", moviesCount);

	printMovies(movies, moviesCount);

	freeMovieArray(movies, moviesCount);
    waitForKeyPress();
}