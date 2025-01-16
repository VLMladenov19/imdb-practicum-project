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
* Header file containing a struct used for responses from functions
*
*/

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