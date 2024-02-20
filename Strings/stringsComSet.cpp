#include <iostream>
#include <algorithm>
#include <set>
#include <string>

long long countPrefix(std::set<std::string>& words, std::string prefix){
    long long count=0;
    long long wordsSize = words.size();
    int prefixSize = prefix.length();
    bool found = false;

    for(auto &i: words){
        if(i.substr(0,prefixSize) == prefix){    
            found = true;       
            count++;
        }
        else if(found)
            break;
    }

    return count;
}


int main(){
    long long q;
    int op;
    std::set<std::string> stringSet;

    std::cin >> q;

    std::string aux;
    for(long long i = 0; i < q; i++){
        std::cin >> op;
        std::cin >> aux;

        switch(op){
            case 1:
                stringSet.insert(aux);
                break;

            case 2:{
                stringSet.erase(aux);
                break;
            }
            case 3:
                std::cout << countPrefix(stringSet, aux) << "\n";
                break;
        }
    }


    return 0;
}