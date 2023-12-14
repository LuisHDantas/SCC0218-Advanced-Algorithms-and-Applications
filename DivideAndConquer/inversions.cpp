#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long DivideAndConquer(vector<long long>& data, long long start, long long end){
    if(start >= end) return 0;

    long long middle = start + (end - start)/2;

    long long leftInversions = DivideAndConquer(data, start, middle);
    long long rightInversions = DivideAndConquer(data, middle + 1, end);

    long long inversions = 0;
    long long l = start;
    long long r = middle + 1;


    vector<long long> temp(end - start + 1);

    long long indexTracker = 0;           

    while (l <= middle && r <= end) {
        if(data[l] <= data[r]){
            temp[indexTracker++] = data[l];
            l++;
        } 
        else{
            temp[indexTracker++] = data[r];
            r++;
            inversions += middle - l + 1; 
        }
    }

    while(l <= middle){
        temp[indexTracker++] = data[l];
        l++;
    }

    while(r <= end){
        temp[indexTracker++] = data[r];
        r++;
    }

    for(l = start, r = 0; l <= end; l++, r++)
        data[l] = temp[r];
    

    return (leftInversions + rightInversions + inversions);
}

long long CountInversions(vector<long long>& data){
    return DivideAndConquer(data, 0 , data.size()-1);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long arraySize;
    long long input;
    vector<long long> data;

    //read data
    cin >> arraySize;
    
    for(long long i = 0; i < arraySize; i++){
        cin >> input;
        data.push_back(input);
    }

    //divide and conquer
    cout << CountInversions(data);

    return 0;
}