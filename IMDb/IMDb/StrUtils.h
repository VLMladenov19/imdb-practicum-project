#pragma once

constexpr size_t STR_SIZE = 1024;

size_t strLen(const char* str);
void strCopy(char* dest, const char* src);
int strCmp(const char* str1, const char* str2);
char** split(const char* str, const char delimiter, size_t& outSize);