// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3560

#include <iostream>
#include <queue>
#include <vector>
#include <list>

typedef std::vector<std::list<int>> Graph;

std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
std::vector<int> unresolved_dependencies;
std::vector<bool> is_leaf;
Graph graph;

void reset() {
	minHeap = std::priority_queue<int, std::vector<int>, std::greater<int>>();
	unresolved_dependencies.clear();
	is_leaf.clear();
	graph.clear();
}

void solve() {
	reset();
	int N, M;
	std::cin >> N >> M;
	unresolved_dependencies.resize(N);
	is_leaf = std::vector<bool>(N, true);
	graph.resize(N);

	int task1, k, task2;

	for(int i=0; i<M; ++i){
		std::cin >> task1 >> k;
		is_leaf[task1-1] = false;
		unresolved_dependencies[task1-1] = k;
		for(int j=0; j<k; ++j){
			std::cin >> task2;
			graph[task2-1].push_back(task1-1);
		}
	}

	for(int i=0; i<N; ++i)
		if(is_leaf[i])
			minHeap.push(i);

	bool first = true;
	while(!minHeap.empty()){
		int next = minHeap.top();
		minHeap.pop();

		for(const auto neighbor : graph[next]){
			if(--unresolved_dependencies[neighbor] == 0){
				minHeap.push(neighbor);
			}
		}

		if(!first){
			std::cout << " ";
		}
		first = false;
		std::cout << (next+1);
	}

	std::cout << "\n";
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

