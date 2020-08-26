#include "PasswordManager.hpp"

using namespace std;

PasswordManager::PasswordManager() {
	/*int menuChoice = 0;
	string label;

	cout << "1. Create password\n2. Get Password\n:";
	cin >> menuChoice;
	system("cls");

	if (menuChoice == 1) {
		cout << "Label for password : ";
		cin >> label;
		string tempPass = this->generatePassword(DEFAULT_VALUE);
		cout << label << ":" << tempPass << endl;
	}
	else if (menuChoice == 2) {
		//TODO --> need DB
	}*/

	fullSize = strlen(lwcase) + strlen(upcase) + strlen(digits) + strlen(special) + 4;

	all = (char*)malloc(sizeof(char) * fullSize);

	strcpy_s(all, strlen(lwcase), lwcase);
	strcat_s(all, strlen(upcase), upcase);
	strcat_s(all, strlen(digits), digits);
	strcat_s(all, strlen(special), special);
}

char* PasswordManager::generatePassword(int defaultValue) {
	int rd = 0;
	char* password;

	password = (char *)malloc(sizeof(char) * DEFAULT_VALUE);

	srand((unsigned)time(NULL));

	for (int i = 0; i < defaultValue; i++) {
		rd = rand() % (fullSize - 4);
		strcpy_s(&password[i], defaultValue, &all[rd]);
	}

	/*for (int i = 0; i < arrayPass.size(); i++) {
		strcpy(password[i], arrayPass[i]);
	}*/

	return password;
}

bool PasswordManager::checkPassword(string checkPass) {
	bool hasLwcase = false, hasUpcase = false, hasEnoughCharacters = false, hasDigits = false, hasSpecial = false;
	int lwcaseNb = 0, upcaseNb = 0, digitsNb = 0;

	for (int i = 0; i < strlen(lwcase); i++) {
		if (checkPass.find(lwcase[i]) != string::npos) {
			lwcaseNb++;
			if (lwcaseNb > 0)
				hasLwcase = true;
		}
	}

	for (int i = 0; i < strlen(upcase); i++) {
		if (checkPass.find(upcase[i]) != string::npos) {
			upcaseNb++;
			if (upcaseNb > 0)
				hasUpcase = true;
		}
	}

	if ((lwcaseNb + lwcaseNb) >= 8)
		hasEnoughCharacters = true;

	for (int i = 0; i < strlen(digits); i++) {
		if (checkPass.find(digits[i]) != string::npos) {
			digitsNb++;
			if (digitsNb >= 2)
				hasDigits = true;
		}
	}

	for (int i = 0; i < strlen(special); i++) {
		if (checkPass.find(special[i]) != string::npos) {
			hasSpecial = true;
		}
	}

	//DEBUG LINE
	cout << "UPCASE: " << upcaseNb << "\nLWCASE: " << lwcaseNb << "\nDIGITS: " << digitsNb << "\nSPECIAL: " << hasSpecial << endl;

	if (hasLwcase && hasUpcase && hasDigits && hasSpecial) {
		cout << "TRUE" << endl;
		return true;
	}
	else {
		cout << "FALSE" << endl;
		return false;
	}
}