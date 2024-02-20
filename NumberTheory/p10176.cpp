#include <iostream>
#include <bitset>

const long long n = 131071;

int main(){
    std::string line;
    std::string numberString;

    while(std::getline(std::cin, line)){
        numberString += line;
        //if number ends in this line 
        if(line.back() == '#'){
            //remove '#'
            numberString.pop_back();

            long long number = 0;

            for(char c: numberString){
                number <<= 1;
                
                if(c == '1')
                    number++;

                number = number % n;    
            }

            (number == 0) ? std::cout << "YES" : std::cout << "NO";
            std::cout << "\n";

            numberString.clear();
        }
    }

    return 0;
}