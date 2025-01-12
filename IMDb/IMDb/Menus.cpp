#include <iostream>

#include "Menus.h"
#include "Constants.h"
#include "StrUtils.h"
#include "Movies.h"

void chooseRole()
{
	std::cout << "Choose role:\n";
	std::cout << "\t1. Admin\n";
	std::cout << "\t2. User\n";

	short role;
	std::cin >> role;

	switch (role)
	{
	case ADMIN_VALUE:
		adminMenu();
		break;
	case USER_VALUE:
		//userMenu();
		break;
	default:
		std::cout << "Invalid value for role\n";
		chooseRole();
		break;
	}
}

void adminMenu()
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

	short action;
	std::cin >> action;

	switch (action)
	{
	case 1:
		addMovieMenu();
		break;
	case 2:
		searchByTitleMenu(*adminMenu);
		break;
	case 3:
		searchByGenreMenu(*adminMenu);
		break;
	case 4:
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
		adminMenu();
		break;
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

	std::cout << "Cast: ";
	char* cast = writeStr();

	Response response = addMovie(Movie(title, year, genre, director, cast));

	if (!response.isSuccessful)
	{
		std::cerr << response.message << "\n";
		addMovieMenu();
		return;
	}

	adminMenu();
}

void searchByTitleMenu(void (*returnMenu)())
{
	std::cout << "Title: ";
	char* title = writeStr();

	size_t moviesCount = 0;
	Movie** movies = getMoviesBy(title, *compareTitle, moviesCount);

	for (size_t i = 0; i < moviesCount; i++)
	{
		std::cout << "\t";
		std::cout << movies[i]->title << ", ";
		std::cout << movies[i]->year << ", ";
		std::cout << movies[i]->genre << ", ";
		std::cout << movies[i]->director << ", ";
		std::cout << movies[i]->cast << "\n";
	}

	std::cin.get();
	returnMenu();
}

void searchByGenreMenu(void (*returnMenu)())
{
	std::cout << "Genre: ";
	char* genre = writeStr();

	size_t moviesCount = 0;
	Movie** movies = getMoviesBy(genre, *compareGenre, moviesCount);

	for (size_t i = 0; i < moviesCount; i++)
	{
		std::cout << "\t";
		std::cout << movies[i]->title << ", ";
		std::cout << movies[i]->year << ", ";
		std::cout << movies[i]->genre << ", ";
		std::cout << movies[i]->director << ", ";
		std::cout << movies[i]->cast << "\n";
	}

	std::cin.get();
	returnMenu();
}