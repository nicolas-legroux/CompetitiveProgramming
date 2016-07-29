#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

std::vector<int> houses;

void reset() {
	houses.clear();
}

bool can_find_better_gap(int gap, int k) {
	int current_count = 1;
	int current_position = houses[0] + gap;
	for (auto pos : houses) {
		if (pos > current_position + gap) {
			current_position = pos + gap;
			++current_count;
		}
	}
	return (current_count <= k);
}

void solve() {
	reset();
	int n, m;
	std::cin >> n >> m;
	int j;
	for (int i = 0; i < m; ++i) {
		std::cin >> j;
		houses.push_back(2 * j);
	}

	if (n >= m) {
		std::cout << "0.0\n";
	}

	else {
		std::sort(houses.begin(), houses.end());
		int low = 0;
		int high = (houses.back() - houses[0]);
		int mid;

		while(high-low>1){
			mid = low + (high-low)/2;
			bool b = can_find_better_gap(mid, n);
			if(b){
				high = mid;
			}
			else{
				low = mid;
			}
		}

		if(high-low==1){
			if(can_find_better_gap(low, n)){
				mid = low;
			}
			else{
				mid = high;
			}
		}

		if (mid % 2 == 0) {
			std::cout << mid / 2 << ".0\n";
		} else {
			std::cout << mid / 2 << ".5\n";
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n_runs;
	std::cin >> n_runs;
	while (n_runs > 0) {
		solve();
		--n_runs;
	}
}
