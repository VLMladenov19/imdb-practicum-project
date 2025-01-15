#pragma once

constexpr size_t STR_SIZE = 1024;

constexpr short ADMIN_VALUE = 1;
constexpr short USER_VALUE = 2;

// Indexes of all "Movie" elements
constexpr short TITLE_INDEX = 0;
constexpr short YEAR_INDEX = 1;
constexpr short GENRE_INDEX = 2;
constexpr short RATING_COUNT_INDEX = 3;
constexpr short RATING_INDEX = 4;
constexpr short DIRECTORT_INDEX = 5;
constexpr short CAST_COUNT_INDEX = 6;
constexpr short CAST_INDEX = 7; // Index to the first cast member (if exists)

// Movies info max lengths
constexpr short TITLE_MAX = 40;
constexpr short YEAR_MAX = 2030;
constexpr short GENRE_MAX = 25;
constexpr short RATING_MAX = 10;
constexpr short DIRECTOR_MAX = 25;
constexpr short CAST_MAX = 25;