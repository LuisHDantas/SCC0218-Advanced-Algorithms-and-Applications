#include <iostream>
#include <vector>
#include <numeric>

/*
- S = x1 XOR x2 XOR ... xn
S=0 perde, else vence
*/

bool IsWinning(std::vector<int>& stackSizes){
    return std::accumulate(stackSizes.begin() + 1, stackSizes.end(), stackSizes[0], [&](int a, int b){return a xor b;});
}

int NimSolver(int n, std::vector<int>& stackSizes){
    return (IsWinning(stackSizes)) ? 0 : 1;
}

int main(){
    int t, n, aux;
    std::vector<int> stackSizes;

    std::cin >> t;

    for(int i = 0; i < t; i++){
        std::cin >> n;

        for(int j = 0; j < n; j++){
            std::cin >> aux;
            stackSizes.push_back(aux);
        }

        //returns number of moves to reach a winning state
        std::cout << NimSolver(n,stackSizes) << "\n";

        //reset for next game
        stackSizes.clear();
    }

    return 0;
}