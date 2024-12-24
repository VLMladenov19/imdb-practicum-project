#include "StrUtils.h"

size_t strLen(const char* str)
{
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