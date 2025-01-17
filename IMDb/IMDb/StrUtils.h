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
* Header file with all declarations of C-style string helper functions
*
*/

#pragma once

#include "Constants.h"

size_t strLen(const char* str);
char toLower(const char sym);
bool isDigit(const char sym);
short charToDigit(const char sym);
int strToNum(const char* str);
float strToFloat(const char* str);

void strCopy(char* dest, const char* src);
int strCmp(const char* str1, const char* str2);
int strCaseCmp(const char* str1, const char* str2);
char** split(const char* str, const char delimiter, size_t& outSize);
char* join(char** arr, const size_t size, const char* joinStr);
bool strCaseContains(const char* str, const char* subStr);
void removeSymbol(char* str, const char sym);

char* writeStr();
short writeNum();
char* fixSize(const char* str);
void freeStrArray(char** str, size_t size);