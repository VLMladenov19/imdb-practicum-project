#include <iostream>
#include "StrUtils.h"
#include "Users.h"
#include "Response.h"

int main()
{
	size_t wordsCount = 0;
	char** words = split("wow,this,is,amazing", ',', wordsCount);

	for (size_t i = 0; i < wordsCount; i++)
	{
		std::cout << words[i] << "\n";
	}

	Response response = addUser(User("username", "pass", 0));

	std::cout << response.isSuccessful << " " << response.message;
}