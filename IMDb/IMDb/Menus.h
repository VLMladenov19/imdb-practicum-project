#pragma once

#include "Movies.h"

void waitForKeyPress();
short chooseAction();

void chooseRole();

void adminMenu();
void userMenu();

void addMovieMenu();

void printMovies(Movie**, const size_t);
void searchByMenu(const char*, 
	bool(*)(const char*, char**));
void listAllMenu();

size_t chooseMovieMenu();
void updateMovieMenu();
void removeMovieMenu();
void rateMovieMenu();