#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>

long long countPrefix(std::vector<std::string>& words, std::string prefix){
    long long count=0;
    long long wordsSize = words.size();
    int prefixSize = prefix.length();

    for(auto &i: words){
        if(i.substr(0,prefixSize) == prefix){           
            count++;
        }
    }
    return count;
}


int main(){
    long long q;
    int op;
    std::vector<std::string> stringSet;

    std::cin >> q;

    std::string aux;
    for(long long i = 0; i < q; i++){
        std::cin >> op;
        std::cin >> aux;

        switch(op){
            case 1:
                stringSet.push_back(aux);
                break;

            case 2:{
                auto it = find(stringSet.begin(), stringSet.end(), aux);
                if(it != stringSet.end())
                    stringSet.erase(it);
                break;
            }
            case 3:
                std::cout << countPrefix(stringSet, aux) << "\n";
                break;
        }
    }


    return 0;
}