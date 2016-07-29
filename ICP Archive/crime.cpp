// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=193&page=show_problem&problem=1213

#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <queue>
#include <algorithm>
#include <array>

typedef std::vector<std::list<int>> Graph;

Graph graph;
std::vector<int> visited;
std::array<int, 2> counts;
int count_minimum;
std::queue<int> dfs_queue;

void reset(){
	graph.clear();
	visited.clear();
	count_minimum = 0;
}

bool dfs(){
	while(!dfs_queue.empty()){
		int node = dfs_queue.front();
		dfs_queue.pop();
		for(int neighbor : graph[node]){
			if(visited[neighbor] == -1){
				int i = (visited[node]+1)%2;
				counts[i]++;
				visited[neighbor] = i;
				dfs_queue.push(neighbor);
			}
			else if (visited[neighbor] == visited[node]){
				return false;
			}
		}
	}
	return true;
}

void solve(const std::string &first_line){
	reset();
	std::stringstream ss(first_line);
	int N, M;
	ss >> N >> M;
	graph.resize(N);
	visited.resize(N);
	int v1, v2;
	for(int i=0; i<M; ++i){
		std::cin >> v1 >> v2;
		graph[v1-1].push_back(v2-1);
		graph[v2-1].push_back(v1-1);
	}
	std::fill(visited.begin(), visited.end(), -1);

	for(int i=0; i<N; ++i){
		if(visited[i] == -1 && !graph[i].empty()){
			visited[i] = 0;
			counts[0] = 1;
			counts[1] = 0;
			dfs_queue = std::queue<int>();
			dfs_queue.push(i);
			bool b = dfs();
			if(!b){
				std::cout << "Impossible\n";
				return;
			}
			count_minimum += std::min(counts[0], counts[1]);
		}
	}
	std::cout << count_minimum << '\n';
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::string first_line;
	while (std::getline(std::cin, first_line)) {
		if (!first_line.empty()){
			solve(first_line);
		}
	}
}
