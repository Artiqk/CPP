#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>

using namespace std;

vector<string> decToBinary(unsigned long long n);
string getHashString(bitset<63> binData);

int main(void)
{
	vector<string> binaryNb;
	bitset<63> data;
	int zBitCount = 0;
	int oBitCount = 0;
	const unsigned long long primeKey = 3197729356749581189;
	unsigned long long asciiMsg = 0;
	string msg;

	cout << "Enter text to hash : "; cin >> msg;

	for(int i = 0; i < msg.length(); i++)
		asciiMsg += int(msg[i]);

	asciiMsg *= primeKey;
	binaryNb = decToBinary(asciiMsg);

	for(int i = 0; i < binaryNb.size(); i++){
		if(binaryNb[i] == "0")
			data[i] = 0;
		else if(binaryNb[i] == "1")
			data[i] = 1;
	}

	for(int i = 0; i < data.size(); i++){
		if(data[i] == 0)
			zBitCount++;
		else if(data[i] == 1)
			oBitCount++;
	}

	if(zBitCount > oBitCount){
		for(int i = 0; i < data.size(); i++){
			if(data[i] == 0)
				data[i] = 1;
			else if(data[i] == 1)
				data[i] = 0;
		}
	}

	string hash = getHashString(data);

	cout << "NSH = " << hash << endl;

	return 0;
}

string getHashString(bitset<63> binData){
	stringstream hash;
	hash << hex << binData.to_ullong();
	return hash.str();
}


vector<string> decToBinary(unsigned long long n) 
{
	vector<string> bin;
	int binaryNum[64];
	int i = 0; 

	while (n > 0) { 
		binaryNum[i] = n % 2; 
	    n = n / 2; 
	    i++; 
	}

	for (int j = i - 1; j >= 0; j--)
	    bin.push_back(to_string(binaryNum[j]));

	return bin;
}