#include <iostream>
#include <vector>
#include <limits>

#define MAX_N 100001

int sum_distances[MAX_N];
int x[MAX_N];
int y[MAX_N];
int weights[MAX_N];

void solve(){
	int C, N;
	std::cin >> C >> N;
	for(int i=1; i<=N; ++i){
		std::cin >> x[i] >> y[i] >> weights[i];
		sum_distances[i] = sum_distances[i-1] + std::abs(x[i]-x[i-1]) + std::abs(y[i]-y[i-1]);
	}

	std::vector<int> best_dist_until(N+1, std::numeric_limits<int>::max());
	best_dist_until[0] = 0;

	for(int i=1; i<=N; ++i){
		int w = 0;
		for(int j=i; j>=1; --j){
			w += weights[j];
			if(w>C){
				break;
			}
			int d = best_dist_until[j-1] + sum_distances[i] - sum_distances[j] + x[j] + x[i] + y[j] + y[i];
			best_dist_until[i] = std::min(best_dist_until[i], d);
		}
	}

	std::cout << best_dist_until[N] << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n_runs;
	std::cin >> n_runs;
	while (n_runs > 0) {
		solve();
		--n_runs;
		if (n_runs > 0)
			std::cout << '\n';
	}
}
