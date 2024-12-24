#pragma once

#include "StrUtils.h"

struct Response
{
	bool isSuccessful;
	char* message;

	Response(bool isSuccessful, const char* message)
	{
		this->isSuccessful = isSuccessful;
		this->message = new char[strLen(message) + 1];
		strCopy(this->message, message);
	}
};