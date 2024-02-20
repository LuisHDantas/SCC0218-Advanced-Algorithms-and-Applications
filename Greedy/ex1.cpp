#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;

    cin >> n;

    vector<pair<int,int>> schedule;

    int start, end;

    for(int i = 0; i < n; i++){
        cin >> start;
        cin >> end;
        schedule.push_back(make_pair(start,end));
    }

    //sort by end time
    sort(schedule.begin(), schedule.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.second != b.second) {
            return a.second < b.second;
        }
        return a.first > b.first;
    });
    
    int counter = 1;

    int lastEvent = 0;

    for (int i = 1; i < n; i++) {
        if(schedule[i].first >= schedule[lastEvent].second){
            counter++;
            lastEvent = i;
        }
    }

    cout << counter;

    return 0;
}
