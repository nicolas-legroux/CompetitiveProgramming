// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3571

#include <iostream>
#include <vector>

// This actually works !!
#define TIME_MAX 300

std::vector<bool> null_state;
std::vector<int> schedules;

void reset() {
	null_state.clear();
	schedules.clear();
}

void show_state(const std::vector<bool> &times, int N, int t){
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			if(times[t * N * N + j + N * i]){
				std::cout << '.';
			}
			else
				std::cout << '#';
		}
		std::cout << '\n';
	}
}

void solve(int N) {
	reset();
	null_state.resize(N * N);
	schedules.resize(N * N);
	char c;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> c;
			null_state[j + N * i] = (c == '.');
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> c;
			schedules[j + N * i] = c - '0';
		}
	}

	std::vector<bool> times(N * N * TIME_MAX, false);
	times[0] = true;

	for (int t = 1; t < TIME_MAX; ++t) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				int a = j + N * i;
				int b = t * N * N + a;
				int schedule = schedules[a];
				bool ok = true;

				if (schedule == 0)
					ok = null_state[a];
				else {
					int r = (t / schedule) % 2;
					if (r == 0)
						ok = null_state[a];
					else
						ok = !null_state[a];
				}
				if (ok) {

					if (times[(t - 1) * N * N + a]) {
						times[b] = true;
						continue;
					}
					if (i > 0 && times[(t - 1) * N * N + j + N * (i - 1)]) {
						times[b] = true;
						continue;
					}
					if (j > 0 && times[(t - 1) * N * N + j - 1 + N * i]) {
						times[b] = true;
						continue;
					}
					if (i < N - 1 && times[(t - 1) * N * N + j + N * (i + 1)]) {
						times[b] = true;
						continue;
					}
					if (j < N - 1 && times[(t - 1) * N * N + j + 1 + N * i]) {
						times[b] = true;
						continue;
					}

				}
			}

		}

		if (times[t * N * N + N * N - 1]) {
			std::cout << t << '\n';
			return;
		}
	}

	std::cout << "NO\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	bool first = true;
	std::string first_line;
	while (std::getline(std::cin, first_line)) {
		if (!first_line.empty()){
			if(!first)
				std::cout << '\n';
			solve(atoi(first_line.c_str()));
		}

		first = false;
	}
}
