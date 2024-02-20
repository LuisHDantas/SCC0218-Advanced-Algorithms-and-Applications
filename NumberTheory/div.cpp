#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

bitset<10000010> crivo;
vector<long long> nums3Div;

void CrivoErastotenes(long long MAX){
        
    long long tamanhoCrivo;
    
    tamanhoCrivo=MAX+1;
    
    //todos são primos aqui!
    crivo.set();
    crivo[0] = crivo[1] = false;

    for(long long i = 2; i <= tamanhoCrivo; i++){
        //se for primo
        if(crivo[i]){
            //apaga os multiplos
            for(long long j = i*i; j <= tamanhoCrivo; j+=i){
                crivo[j] = false;
            }
            nums3Div.push_back(i*i);
        }
    }
}

bool checkDiv(long long number){
    return binary_search(nums3Div.begin(), nums3Div.end(), number);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    CrivoErastotenes(10000000);

    int inputSize;
    long long input;

    cin >> inputSize;

    for(int i = 0; i < inputSize; i++){
        cin >> input;
        if(checkDiv(input))
            cout << "1";
        else   
            cout << "0";
    }


    return 0;    
}