#pragma once

void chooseRole();

void waitForKeyPress();
short chooseAction();

void adminMenu();
void userMenu();

void addMovieMenu();
void searchByTitleMenu(void (*)() = *chooseRole);
void searchByGenreMenu(void (*)() = *chooseRole);
void listAllMenu(void (*)() = *chooseRole);