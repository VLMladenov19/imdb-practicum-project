#pragma once

void chooseRole();

void waitForKeyPress();
short chooseAction();

void adminMenu();
void userMenu();

void addMovieMenu();
void searchByMenu(const char*, 
	bool(*)(const char*, char**), 
	void (*)() = *chooseRole);
void listAllMenu(void (*)() = *chooseRole);