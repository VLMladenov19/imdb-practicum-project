#pragma once

void chooseRole();

void adminMenu();
void userMenu();

void addMovieMenu();
void searchByTitleMenu(void (*)() = *chooseRole);
void searchByGenreMenu(void (*)() = *chooseRole);