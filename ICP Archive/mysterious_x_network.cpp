// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3589

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>

typedef std::vector<std::list<int>> Graph;

Graph graph;
std::vector<int> distances;
std::queue<int> queue;

void reset(){
	graph.clear();
	distances.clear();
	queue = std::queue<int>();
}

int dfs(int from, int to){
	for(unsigned int i=0; i<graph.size(); ++i){
		distances[i] = std::numeric_limits<int>::max();
	}
	distances[from] = 0;
	queue.push(from);
	while(!queue.empty()){
		int node = queue.front();
		//std::cout << "Considering node " << node << std::endl;
		queue.pop();
		if(node == to){
			return distances[node]-1;
		}

		else{
			int current_distance = distances[node];
			for(auto i : graph[node]){
				if(distances[i] == std::numeric_limits<int>::max()){
					//std::cout << "Current node is " << node << ". Current distance is " << current_distance << ". Looking at neighbor " << i << ".\n";
					distances[i] = current_distance + 1;
					queue.push(i);
				}
			}
		}
	}
	return -1;
}

void solve(){
	reset();
	int N, n;
	std::cin >> N;
	graph.resize(N);
	distances.resize(N);
	int n_neighbors;
	for(int i=0; i<N; ++i){
		std::cin >> n >> n_neighbors;
		int neighbor;
		for(int j=0; j<n_neighbors; ++j){
			std::cin >> neighbor;
			graph[n].push_back(neighbor);
		}
	}

	int i,j;
	std::cin >> i >> j;
	std::cout << i << " " << j << " " << dfs(i,j) << "\n";
}


int main(){
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


