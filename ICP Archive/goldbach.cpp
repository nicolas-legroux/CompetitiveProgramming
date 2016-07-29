// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=484

#include <iostream>
#include <vector>
#include <utility>

std::vector<bool> primes(1000001, true);

void run_erathostene(){
	primes[0] = false;
	primes[1] = false;
	unsigned int current = 2;
	while(current < primes.size()){
		if(primes[current]){
			unsigned int i = 2 * current;
			while(i < primes.size()){
				primes[i] = false;
				i += current;
			}
		}
		current++;
	}
}

bool is_prime(int i){
	return primes[i];
}

void show_primes(){
	for(int i=0; i<100; i++){
		if (is_prime(i)){
			std::cout << i << std::endl;
		}
	}
}

int get_goldbach(int i){
	int current = i-3;
	while(current>=0){
		if(is_prime(current) && is_prime(i-current)){
			return current;
		}
		current -= 2;
	}
	return -1;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	run_erathostene();
	int i;
	while(true){
		std::cin >> i;
		if(i==0){
			break;
		}
		else{
			int g = get_goldbach(i);
			std::cout << i << " = " << (i-g) << " + " << g << std::endl;
		}
	}
}

