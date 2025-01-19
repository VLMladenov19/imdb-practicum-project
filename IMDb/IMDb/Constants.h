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
* Header file containing all constants used in the program
*
*/

#pragma once

constexpr size_t STR_SIZE = 1024;

constexpr char MOVIES_FILE[] = "movies.txt";
constexpr char FILE_DIVIDER_CHAR = '#';
constexpr char FILE_DIVIDER_STR[] = "#";

// Menu actions values
constexpr short EXIT_ACTION = 0;

// Choose role
constexpr short ADMIN_ACTION = 1;
constexpr short USER_ACTION = 2;

// Admin menu
constexpr short ADMIN_ADD_MOVIE_ACTION = 1;
constexpr short ADMIN_SEARCH_BY_TITLE_ACTION = 2;
constexpr short ADMIN_SEARCH_BY_GENRE_ACTION = 3;
constexpr short ADMIN_LIST_ALL_ACTION = 4;
constexpr short ADMIN_UPDATE_MOVIE_ACTION = 5;
constexpr short ADMIN_REMOVE_MOVIE_ACTION = 6;
constexpr short ADMIN_SORT_ACTION = 7;
constexpr short ADMIN_FILTER_ACTION = 8;

// User menu
constexpr short USER_SEARCH_BY_TITLE_ACTION = 1;
constexpr short USER_SEARCH_BY_GENRE_ACTION = 2;
constexpr short USER_LIST_ALL_ACTION = 3;
constexpr short USER_RATE_MOVIE_ACTION = 4;
constexpr short USER_SORT_ACTION = 5;
constexpr short USER_FILTER_ACTION = 6;

// Sort menu
constexpr short SORT_BY_TITLE_ASC = 1;
constexpr short SORT_BY_TITLE_DESC = 2;
constexpr short SORT_BY_GENRE_ASC = 3;
constexpr short SORT_BY_GENRE_DESC = 4;

// Indexes of all "Movie" elements
constexpr short TITLE_INDEX = 0;
constexpr short YEAR_INDEX = 1;
constexpr short GENRE_INDEX = 2;
constexpr short RATING_COUNT_INDEX = 3;
constexpr short RATING_INDEX = 4;
constexpr short DIRECTOR_INDEX = 5;
constexpr short CAST_COUNT_INDEX = 6;
constexpr short CAST_INDEX = 7; // Index to the first cast member (if exists)

// Movies info max lengths/value
constexpr short TITLE_MAX_LENGTH = 40;
constexpr short YEAR_MIN = 1850;
constexpr short YEAR_MAX = 2030;
constexpr short GENRE_MAX_LENGTH = 25;
constexpr short RATING_MIN = 0;
constexpr short RATING_MAX = 10;
constexpr short DIRECTOR_MAX_LENGTH = 25;
constexpr short CAST_MAX_LENGTH = 25;