#pragma once

#include "StrUtils.h"
#include "Response.h"

struct User
{
	char* username;
	char* password;
	short role;

	User(const char* username, const char* password, const short role)
	{
		this->username = new char[strLen(username) + 1];
		strCopy(this->username, username);
		this->password = new char[strLen(password) + 1];
		strCopy(this->password, password);
		this->role = role;
	}
};

Response addUser(const User user);
User* getUser(const char* username);