//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3450

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>

struct Subnetwork {
	int cost = 0;
	std::vector<int> cities = { };
};

std::vector<Subnetwork> subnetworks;
std::vector<std::pair<int, int>> cities;

struct Link {
	int c1, c2, cost;

	Link(int _c1, int _c2) :
			c1(_c1), c2(_c2) {
		int xx = cities[c1].first - cities[c2].first;
		int yy = cities[c1].second - cities[c2].second;
		cost = xx * xx + yy * yy;
	}

	Link(int _c1, int _c2, int _cost) :
			c1(_c1), c2(_c2), cost(_cost) {
	}

	bool operator<(const Link &l) const {
		return l.cost < cost;
	}
};

struct UnionFind {
	std::vector<int> v;
	UnionFind(int n) {
		v.resize(n);
		std::iota(v.begin(), v.end(), 0);
	}

	int find_op(int i){
		if(v[i] != i){
			v[i] = find_op(v[i]);
		}
		return v[i];
	}

	bool union_op(int i1, int i2){
		int parent1 = find_op(i1);
		int parent2 = find_op(i2);
		if(parent1 != parent2){
			v[parent1] = parent2;
			return true;
		}
		return false;
	}
};

void reset() {
	subnetworks.clear();
	cities.clear();
}

int solve_with_subnetworks(int q, int subsets,
		std::priority_queue<Link> links) {

	int cost = 0;

	for (int j = 0; j < q; ++j) {
		if (subsets & (1 << j)) {
			cost += subnetworks[j].cost;
			for(unsigned int i=1; i<subnetworks[j].cities.size(); ++i){
				Link link = Link(subnetworks[j].cities[i-1], subnetworks[j].cities[i], 0);
				links.push(link);
			}
		}
	}

	int n = cities.size();

	UnionFind union_find(n);

	while(n>1){
		Link l = links.top();
		links.pop();
		if(union_find.union_op(l.c1, l.c2)){
			std::cout << l.c1 << ' ' << l.c2 << '\n';
			--n;
			cost += l.cost;
		}
	}

	return cost;
}

void solve() {
	reset();
	int n, q;
	std::cin >> n >> q;

	for (int j = 0; j < q; ++j) {
		Subnetwork subnet;
		int size_subnet;
		std::cin >> size_subnet >> subnet.cost;
		int x;
		for (int i = 0; i < size_subnet; ++i) {
			std::cin >> x;
			subnet.cities.push_back(x - 1);
		}
		subnetworks.push_back(subnet);
	}

	int x, y;

	for (int i = 0; i < n; ++i) {
		std::cin >> x >> y;
		cities.push_back( { x, y });
	}

	std::priority_queue<Link> links;

	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			Link l = Link(i, j);
			links.push(l);
		}
	}

	int current_best_cost = std::numeric_limits<int>::max();

	for (int i = 0; i < (1 << q); ++i) {
		int cost = solve_with_subnetworks(q, i, links);
		if (cost < current_best_cost)
			current_best_cost = cost;
	}

	std::cout << current_best_cost << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n_runs;
	std::cin >> n_runs;
	while (n_runs > 0) {
		solve();
		--n_runs;
		if (n_runs > 0)
			std::cout << "\n";
	}
}
