/*
- Luís Henrique Dantas - 13782369
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INFINITY INT_MAX

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long numSongs;

    cin >> numSongs;

    long long *songs = new long long[numSongs];
    vector<long long> memorize;

    for(int i = 0; i < numSongs; i++){
        cin >> songs[i];
        memorize.push_back(INFINITY);
    }

    memorize[0] = 0;
    memorize[1] = abs(songs[1] - songs[0]);

    for(long long i = 2; i < numSongs; i++)
        memorize[i] = min(memorize[i-1] + abs(songs[i] - songs[i-1]), memorize[i-2] + abs(songs[i] - songs[i-2]));

    cout << memorize[numSongs-1];
    return 0;
}