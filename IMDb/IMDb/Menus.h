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
* Header file containing all declarations of the printable menus
*
*/

#pragma once

#include "Movies.h"

void waitForKeyPress();

void chooseRole();

void adminMenu();
void userMenu();

void addMovieMenu();

void printMovies(Movie** movies, const size_t moviesCount);
void searchByMenu(const char* searchText,
	bool(*searchFunc)(const char*, char**));
void listAllMenu();

size_t chooseMovieMenu();
void updateMovieMenu();
void removeMovieMenu();
void rateMovieMenu();

void sortMoviesMenu();
void filterMoviesMenu();