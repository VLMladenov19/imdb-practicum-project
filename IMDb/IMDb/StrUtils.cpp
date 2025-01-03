#include "StrUtils.h"

size_t strLen(const char* str)
{
	if (!str) return 0;

	size_t len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return len;
}

void strCopy(char* dest, const char* src)
{
	if (!dest || !src) return;

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

int strCmp(const char* str1, const char* str2)
{
	// Handle nullptr cases
	if (!str1) return str2 ? -1 : 0;
	if (!str2) return 1;

	while (*str1 && *str2)
	{
		if (*str1 != *str2)
		{
			return *str1 - *str2;
		}
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

char** split(const char* str, const char delimiter, size_t& outSize)
{
	if (!str) return nullptr;

	outSize = 1;
	const char* temp = str;
	while (*temp)
	{
		if (*temp == delimiter)
		{
			outSize++;
		}
		temp++;
	}

	// Ensure enough space is reserved
	char** result = new char*[outSize + 1];
	size_t index = 0;
	size_t length = 0;
	char* currWord = new char[STR_SIZE];
	while (*str)
	{
		if (*str == delimiter)
		{
			currWord[length] = '\0';
			result[index] = new char[length + 1];
			strCopy(result[index], currWord);
			currWord = new char[STR_SIZE];
			length = 0;
			index++;
			str++;
		}
		currWord[length++] = *str;
		str++;
	}
	if (length)
	{
		currWord[length] = '\0';
		result[index] = new char[length + 1];
		strCopy(result[index], currWord);
		delete[] currWord;
		length = 0;
	}

	return result;
}

short charToDigit(const char c)
{
	if ('0' <= c && c <= '9')
	{
		return c - '0';
	}
	return -1;
}

int strToNum(const char* str)
{
	if (!str) return 0;

	size_t length = strLen(str);
	int num = 0;
	for (size_t i = 0; i < length; i++)
	{
		short digit = charToDigit(str[i]);
		if (digit == -1)
			return num;
		num = num * 10 + digit;
	}

	return num;
}

void freeMemory(char** str, size_t size)
{
	if (!str) return;

	for (size_t i = 0; i < size; i++)
	{
		delete[] str[i];
	}
	delete[] str;
}