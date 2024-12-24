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

	char line[1024];
	while (file.getline(line, 1024))
	{

	}

	return nullptr;
}