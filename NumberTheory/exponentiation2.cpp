#include <iostream>

const long long n = 1000000007;

long long solve(long long a, long long b, long long n){
    if(b == 0) return 1;
    if(a == 0) return 0;

    long long result = 1;

    while(b > 0){
        if(b%2 == 1)
            result = (result*a)%n;

        b /= 2;
        a = (a*a)%n;
    }

    return result;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int iterations;
    long long a,b,c;

    std::cin >> iterations;

    for(int i = 0; i < iterations; i++){
        std::cin >> a >> b >> c;
        std::cout << solve(a, solve(b, c, n-1), n) << "\n";
    }

    return 0;
}