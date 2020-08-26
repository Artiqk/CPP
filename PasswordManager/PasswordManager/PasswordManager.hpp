#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>

#define DEFAULT_VALUE 16

class PasswordManager {
private:
	char lwcase[27] = "abcdefghijklmnopqrstuvwxyz";
	char upcase[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char digits[11] = "0123456789";
	char special[27] = "-_@#({[|]})</>=+*$%!:;?";

	int fullSize;

	//std::string all = lwcase + upcase + digits + special;
	char* all;

public:
	PasswordManager();
	char* generatePassword(int defaultValue);
	bool checkPassword(std::string checkPass);
};