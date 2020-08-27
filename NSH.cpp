#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>

using namespace std;

string nsh(string wordToHash){
	const unsigned long long key = 3197729356749581189;

	bitset<64> binData;
	stringstream hash;
	int zBitCount = 0;
	int oBitCount = 0;

	unsigned long long calcMsg = 0;

	for(int i = 0; i < wordToHash.length(); i++){
		calcMsg += (int(wordToHash[i]) % 9) * i + (int(wordToHash[i]));
	}

	calcMsg *= key;
	binData = decToBinary(calcMsg);

	for(int i = 0; i < binData.size(); i++){
		if(binData[i] == 0)
			zBitCount++;
		else if(binData[i] == 1)
			oBitCount++;
	}

	if(zBitCount > oBitCount){
		for(int i = 0; i < binData.size(); i++){
			if(binData[i] == 0)
				binData[i] = 1;
			else if(binData[i] == 1)
				binData[i] = 0;
		}
	}

	hash << hex << binData.to_ullong();
	
	return hash.str();
}

bitset<64> decToBinary(unsigned long long n) 
{
	int binaryNum[64];
	int i = 0; 

	while (n > 0) { 
		binaryNum[i] = n % 2; 
	    n = n / 2; 
	    i++; 
	}

	bitset<64> binData;

	for (int j = i - 1; j >= 0; j--)
	    binData[j] = binaryNum[j];

	return binData;
}