#include <cstdio>
#include <iostream>

using namespace std;

long long solve(long long n, long long k){
    long long counter = 0;

    while(n != 0){
        long long resto = n % k;    
        if(resto == 0){
            n = n/k;
            counter++;
        }else{
            n -= resto;
            counter += resto;
        }
    }
    
    return counter;   
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int iterations;
    long long n, k;             // 1 <= n <= 10^18 ; 2 <= k <= 10^18

    cin >> iterations;
    
    for(int i = 0; i < iterations; i++){
        cin >> n >> k;

        cout << solve(n,k) << endl;
    }

    return 0;
}