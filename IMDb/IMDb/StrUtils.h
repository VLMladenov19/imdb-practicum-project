#pragma once

constexpr size_t STR_SIZE = 1024;

size_t strLen(const char* str);

void strCopy(char* dest, const char* src);
int strCmp(const char* str1, const char* str2);
int strCaseCmp(const char* str1, const char* str2);
char** split(const char* str, const char delimiter, size_t& outSize);
char* join(char** arr, const size_t size, const char* joinStr);

char toLower(const char sym);
short charToDigit(const char sym);
int strToNum(const char* str);

char* writeStr();
char* fixSize(const char* str);
void freeMemory(char** str, size_t size);