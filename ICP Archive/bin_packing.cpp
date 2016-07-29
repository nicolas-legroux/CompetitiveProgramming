#include <vector>
#include <iostream>
#include <algorithm>

std::vector<int> bins;

void reset() {
	bins.clear();
}

void solve(){
	reset();
	int n, l;
	std::cin >> n >> l;
	int bin;
	for(int i=0; i<n; ++i){
		std::cin >> bin;
		bins.push_back(bin);
	}

	std::sort(bins.begin(), bins.end());

	int number_of_bins = 1;
	int space_left = l - bins.back();
	bool can_add_item = true;

	auto ptr_left = bins.begin();
	auto ptr_right = --(bins.end());

	while(ptr_left != ptr_right){
		if(*ptr_left<=space_left && can_add_item){
			space_left -= *(ptr_left++);
			can_add_item = false;
		}
		else{
			++number_of_bins;
			space_left = l - *(--ptr_right);
			can_add_item = true;
		}
	}

	std::cout << number_of_bins << '\n';

}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n_runs;
	std::cin >> n_runs;
	while (n_runs > 0) {
		solve();
		--n_runs;
		if (n_runs > 0) {
			std::cout << "\n";
		}
	}
}

