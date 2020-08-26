#include <iostream>
#include <string>
#include <locale>
#include <vector>
#include <thread>
#include "artiqk.h"

using namespace std;

char alpha[26] = {0};

void alphabet()
{

	for(int i = 0; i < 26; i++)
	{
		alpha[i] = (char)(97 + i);
 	}
}

string cesarCrypt(string input, int delay)
{
	for(int i = 0; i < input.size(); i++)
	{
		for(int j = 0; j < 26; j++)
		{
			if(input[i] == (char)(97 + j))
			{
				j += delay;
				if((97 + j) > 122)
				{
					int h = (97 + j) - 123;
					if(h > 26)
					{
						while(h > 26)
							h -= 26;
					}
					input[i] = (char)(97 + h);
				} else {
					input[i] = (char)(97 + j);
				}
			}
		}
	}

	return input;
}

int main(int argc, char *argv[])
{
	locale loc;
	int wordNbr = argc;
	vector<string> wordList;
	string cracked[26];

	alphabet();

	system("cls");

	for(int i = 1; i < wordNbr; i++){
		wordList.push_back(argv[i]);
	}

	for(int i = 0; i < 26; i++){
		for(int j = 0; j < wordList.size(); j++){
			cracked[i] = cesarCrypt(wordList[j], i);
			cout << cracked[i] << " ";
		}
		cout << endl;
	}
	
	return 0;
}