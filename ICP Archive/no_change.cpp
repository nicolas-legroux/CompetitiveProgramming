// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3561

#include <iostream>
#include <vector>
#include <algorithm>

int target;
int number_of_coins;
std::vector<int> coin_values;
std::vector<bool> can_pay(1000001);

void reset() {
	coin_values.clear();
	std::fill(can_pay.begin(), can_pay.end(), false);
	can_pay[0] = true;
}

void solve() {
	reset();
	std::cin >> target >> number_of_coins;
	int v;
	for (int i = 0; i < number_of_coins; ++i) {
		std::cin >> v;
		coin_values.push_back(v);
	}
	std::vector<int> accumulated_values = coin_values;
	for (int i = 1; i < number_of_coins; ++i) {
		accumulated_values[i] += accumulated_values[i - 1];
	}

	for(int i=accumulated_values[0]; i<=target; ++i){
		for(int j=0; j<number_of_coins; ++j){
			if(i-accumulated_values[j]>=0 && can_pay[i-accumulated_values[j]]){
				can_pay[i] = true;
			}
		}
	}

	if(can_pay[target]){
		std::cout << "YES" << std::endl;
	}
	else{
		std::cout << "NO" << std::endl;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n_runs;
	std::cin >> n_runs;
	while (n_runs > 0) {
		solve();
		--n_runs;
		if(n_runs>0){
			std::cout << std::endl;
		}
	}
}

