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
* File with helper functions for C-style strings
*
*/

#include <iostream>

#include "StrUtils.h"
#include "Constants.h"

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

char toLower(const char sym)
{
	if ('A' <= sym && sym <= 'Z')
	{
		return sym - 'A' + 'a';
	}
	return sym;
}

bool isDigit(const char sym)
{
	return '0' <= sym && sym <= '9';
}

short charToDigit(const char sym)
{
	if (isDigit(sym))
	{
		return sym - '0';
	}
	return -1;
}

int strToNum(const char* str)
{
	if (!str || !isDigit(*str)) return -1;

	int num = 0;
	while (*str)
	{
		short digit = charToDigit(*str);
		if (digit == -1)
		{
			return num;
		}
		num = num * 10 + digit;
		str++;
	}

	return num;
}

float strToFloat(const char* str)
{
	if (!str || !isDigit(*str)) return -1;

	float result = 0;
	while (*str != '.' || *str == ',')
	{
		short digit = charToDigit(*str);
		if(digit == -1)
		{
			return result;
		}
		result = result * 10 + digit;
		str++;
	}

	float fractionMult = 0.1f;
	while (*str)
	{
		if (isDigit(*str))
		{
			result += charToDigit(*str) * fractionMult;
			fractionMult *= 0.1f;
		}
		str++;
	}

	return result;
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

// Case insensitive compare
int strCaseCmp(const char* str1, const char* str2)
{
	// Handle nullptr cases
	if (!str1) return str2 ? -1 : 0;
	if (!str2) return 1;

	while (*str1 && *str2)
	{
		if (toLower(*str1) != toLower(*str2))
		{
			return toLower(*str1) - toLower(*str2);
		}
		str1++;
		str2++;
	}
	return toLower(*str1) - toLower(*str2);
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
			continue;
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

char* join(char** arr, const size_t size, const char* joinStr)
{
	if (!arr) return nullptr;

	if (!size)
	{
		char* emptyStr = new char[1];
		strCopy(emptyStr, "");
		return emptyStr;
	}

	char* str = new char[STR_SIZE];
	char* firstIndex = str;
	for (size_t i = 0; i < size - 1; i++)
	{
		strCopy(str, arr[i]);
		str += strLen(arr[i]);
		strCopy(str, joinStr);
		str += strLen(joinStr);
	}
	strCopy(str, arr[size - 1]);

	return fixSize(firstIndex);
}

bool strCaseContains(const char* str, const char* subStr)
{
	if (!str || !subStr) return false;

	if (!*subStr)
		return true;

	while (*str)
	{
		const char* strPtr = str;
		const char* subStrPtr = subStr;

		while (*strPtr && *subStrPtr && toLower(*strPtr) == toLower(*subStrPtr))
		{
			strPtr++;
			subStrPtr++;
		}

		if (!*subStrPtr)
			return true;

		str++;
	}
	return false;
}

void removeSymbol(char* str, const char sym)
{
	if (!str) return;

	char* strPos = str;
	while (*str)
	{
		if (*str != sym)
		{
			*strPos = *str;
			strPos++;
		}
		str++;
	}
	*strPos = '\0';
}

char* writeStr()
{
	char* str = new char[STR_SIZE + 1];

	if (std::cin.peek() == '\n')
	{
		std::cin.ignore();
	}
	std::cin.getline(str, STR_SIZE);

	str = fixSize(str);
	removeSymbol(str, '\n');
	
	return fixSize(str);
}

char* fixSize(const char* str)
{
	if (!str) return nullptr;

	char* fixed = new char[strLen(str) + 1];
	strCopy(fixed, str);
	
	delete[] str;
	return fixed;
}

void freeStrArray(char** strArr, size_t size)
{
	if (!strArr) return;

	for (size_t i = 0; i < size; i++)
	{
		delete[] strArr[i];
	}
	delete[] strArr;
}