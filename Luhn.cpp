#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int digitSum(int nbr);

int main()
{
    int total = 0;
    string cardStr;
    char cardC[16];
    vector<int> luhnCard, card;
    
    cout << "Numero de carte : "; cin >> cardStr;
    strcpy(cardC, cardStr.c_str());

    for(int i = 0; i < 16; i++){
        card.push_back(cardC[i] - '0');
    }

    for(int i = 0; i < 15; i++) {
        int tempVar = 0;

        if((i + 1) %  2 != 0) {
            tempVar = card[i] * 2;
            if(tempVar >= 10) {
                tempVar = digitSum(tempVar);
            }
        } else {
            tempVar = card[i];
        }
        
        luhnCard.push_back(tempVar);
    }

    for(int i = 0; i < 15; i++) {
        total += luhnCard[i];
    }

    if(10 - (total % 10) == card[15]){
        cout << "La carte est valide" << endl;
    } else {
        cout << "La carte est invalide" << endl;
    }

    return 0;
}

int digitSum(int nbr)
{
    int sum = 0;
    while(nbr != 0) {
        sum = sum + nbr % 10;
        nbr = nbr / 10;
    }

    return sum;
}