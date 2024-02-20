/*
- Luís Henrique Giorgetti Dantas - 13782369
*/
#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long>> readData(long long &n, long long &k){
    cin >> n >> k;

    vector<vector<long long>> dataStorage(n, vector<long long>(k));

    for(long long i = 0; i < n; i++){
        for(long long j = 0; j < k; j++){
            cin >> dataStorage[i][j];
        }
    }

    return dataStorage;
}


long long maxProfit(vector<vector<long long>> data){
    //pares para armezanar as duas possibilidades mais lucrativas do dia anterior (indice, valor)
    pair<long long, long long> previousMax = make_pair(0, 0);
    pair<long long, long long> previousSecondMax = make_pair(0, 0);

    for(vector<long long> i: data){
        pair<long long, long long> temp = make_pair(0,0);
        pair<long long, long long> temp2 = make_pair(0,0);

        for(long long index = 0; index < i.size(); index++){
            if(index != previousMax.first){
                if(i[index] + previousMax.second > temp.second){
                    temp2.first = temp.first;
                    temp2.second = temp.second;

                    temp.first = index;
                    temp.second = (i[index] + previousMax.second);
                }
                else if(i[index] + previousMax.second > temp2.second){
                    temp2.first = index;
                    temp2.second = i[index] + previousMax.second;
                }
            }
            else{
                if(i[index] + previousSecondMax.second > temp.second){
                    temp2.first = temp.first;
                    temp2.second = temp.second;

                    temp.first = index;
                    temp.second = (i[index] + previousSecondMax.second);
                }
                else if(i[index] + previousSecondMax.second > temp2.second){
                    temp2.first = index;
                    temp2.second = i[index] + previousSecondMax.second;
                }
            }
        }

        previousMax = temp;
        previousSecondMax = temp2;
    }

    return previousMax.second;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long n, k;
    vector<vector<long long>> data = readData(n, k);

    cout << maxProfit(data);

    return 0;
}