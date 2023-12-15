/*
-Luís Henrique Giorgetti Dantas
-13782369
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void Search(const vector<int>& data, unordered_set<int>& sums, vector<int> subset = {}, int counter = 0, int partialSum = 0){
    if(counter == data.size()){
        //process subset
        if(subset.empty()) return;
        
        sums.insert(partialSum);
    }
    else{
        //analyze subset without element of index "counter"
        Search(data, sums, subset, counter + 1, partialSum);

        //analyze subset with element of index "counter"
        subset.push_back(data[counter]);
        Search(data, sums, subset, counter + 1, partialSum + data[counter]);
    }

    return;
}

int DistinctSums(const vector<int> data){
    unordered_set<int> sums;

    Search(data, sums);

    return sums.size();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    //reading data from cin
    int numBees;

    cin >> numBees;
    vector<int> polen(numBees);

    for(int i = 0; i < numBees; i++)
        cin >> polen[i];
    
    //calculate
    cout << DistinctSums(polen);

    return 0;
}
