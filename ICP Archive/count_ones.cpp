#include <iostream>
#include <sstream>
#include <stdint.h>

int closest_power_2(uint64_t n){
    int i=0;
    uint64_t c = 1;
    while(2ULL*c <= n){
        ++i;
        c *= 2ULL;
    }
    return i;
}

uint64_t solve_to_zero(uint64_t n){
    if(n==1){
        return 1;
    }

    if(n==0){
        return 0;
    }

    uint64_t count = 0;
    int i = closest_power_2(n);
    count += (1ULL<<i)*i/2ULL;
    count += n-(1ULL<<i)+1ULL;
    count += solve_to_zero(n-(1ULL<<i));

    return count;
}

int64_t solve(uint64_t lb, uint64_t ub){
    return solve_to_zero(ub) - solve_to_zero(lb-1);
}

int main(){
    std::string s;
    while(std::getline(std::cin, s)){
        std::stringstream ss(s);
        uint64_t lb, ub;
        ss >> lb >> ub;
        std::cout << solve(lb, ub) << '\n';
    }        
}

