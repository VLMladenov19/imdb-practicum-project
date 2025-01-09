#include <iostream>
#include <fstream>

#include "Users.h"
#include "Response.h"

Response addUser(const User user)
{
	// Directory has to be created for code to work
	std::ofstream file("files/users.txt", std::ios::app);

	if (!file.is_open())
	{
		return Response(false, "Error: File not found");
	}

	file << user.username << "," << user.password << "," << user.role << "\n";

	file.close();
	return Response(true, "Success");
}

User* getUser(const char* username)
{
	std::ifstream file("files/users.txt");

	char line[STR_SIZE + 1];
	while (file.getline(line, STR_SIZE))
	{
		size_t infoCount = 0;
		char** userInfo = split(line, ',', infoCount);
		
		if (infoCount != 3 || strCmp(username, userInfo[0]))
		{
			freeMemory(userInfo, infoCount);
			continue;
		}

		User* user = new User(userInfo[0], userInfo[1], strToNum(userInfo[2]));
		freeMemory(userInfo, infoCount);
		return user;
	}

	return nullptr;
}