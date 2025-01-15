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

char* writeStr();
char* fixSize(const char* str);
void freeStrArray(char** str, size_t size);