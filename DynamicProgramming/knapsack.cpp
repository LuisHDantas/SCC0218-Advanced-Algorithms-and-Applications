/*
- Luís Henrique Giorgetti Dantas - 13782369
*/

#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long>> readData(long long &n, long long &weight) {
    cin >> n >> weight;

    vector<vector<long long>> dataStorage(n + 1, vector<long long>(2));

    for (long long i = 1; i < n + 1; i++) {
        for (long long j = 0; j < 2; j++) {
            cin >> dataStorage[i][j];
        }
    }

    return dataStorage;
}

long long maxValue(vector<vector<long long>> data, long long weight) {

    vector<vector<long long>> MEMO(data.size(), vector<long long>(weight + 1, 0));

    // for each item
    for (int i = 1; i < data.size(); i++) {
        // for each possible weight
        for (int j = 0; j <= weight; j++) {
            if (j < data[i][0])
                MEMO[i][j] = MEMO[i - 1][j];
            else
                MEMO[i][j] = max(MEMO[i - 1][j], data[i][1] + MEMO[i - 1][j - data[i][0]]);
        }
    }

    return MEMO[data.size() - 1][weight];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long n, weight;

    vector<vector<long long>> data = readData(n, weight);

    cout << maxValue(data, weight);

    return 0;
}
