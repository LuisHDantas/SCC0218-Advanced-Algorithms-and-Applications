//Cover Interval Problem

#include <iostream>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, range;

    cin >> n; 
    cin >> range;

    int i = 0;
    int covered = 0;
    int guardsCounter = 0;
    int statuePosition;

    do{
        cin >> statuePosition;

        if(statuePosition > covered){
            guardsCounter++;
            covered = statuePosition + 2*range;
        }

        i++;
    }while(i < n);

    cout << guardsCounter;

    return 0;
}
