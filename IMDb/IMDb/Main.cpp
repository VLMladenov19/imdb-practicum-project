#include <iostream>
#include "StrUtils.h"

int main()
{
	size_t wordsCount = 0;
	char** words = split("wow,this,is,amazing", ',', wordsCount);

	for (size_t i = 0; i < wordsCount; i++)
	{
		std::cout << words[i] << "\n";
	}
}