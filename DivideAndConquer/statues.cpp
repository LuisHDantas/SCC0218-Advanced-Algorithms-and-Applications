/*
-Luís Henrique Giorgetti Dantas
-13782369
*/

#include <iostream>
#include <vector>

using namespace std;

//returns true if the current radius satisfies the conditions for the explosion to work
bool Explodes(const vector<int>& positions, const int numBombs, const int radius){
    int statueCounter = 1;
    int lastStatue = positions[0];

    for(int i = 1; i < positions.size(); i++){
        if(positions[i] - lastStatue > 2*radius){
            statueCounter++;
            lastStatue = positions[i];
        }
    }

    return (statueCounter <= numBombs);
}


//binary search in a vector of possible radius values
int MininumRadius(const vector<int>& positions, const int numBombs){
    int start = 0;
    int end = positions[positions.size()-1] - positions[0];

    while(start < end){
        int middle = start + (end - start) / 2;

        if(Explodes(positions, numBombs, middle)) 
            end = middle;
        else 
            start = middle + 1;
    }

    return start;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    //reading data
    int numStatues;
    int numBombs;
    vector<int> positions;

    cin >> numStatues;
    cin >> numBombs;

    int input;

    for(int i = 0; i < numStatues; i++){
        cin >> input;
        positions.push_back(input);
    }

    //calculates the best solution

    cout << MininumRadius(positions, numBombs);

    return 0;
}