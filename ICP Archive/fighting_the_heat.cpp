// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3583

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <array>

#define NMAX 40
#define MMAX 40

char grid[NMAX][MMAX];
bool mask[NMAX][MMAX];
std::vector<std::string> words;
std::vector<std::array<int, 26>> shifts;

void reset() {
	words.clear();
	shifts.clear();
	std::fill(mask[0], mask[0] + NMAX * MMAX, false);
}

std::vector<int> boyer_moore(const std::string &text,
		const std::string &pattern, const std::array<int, 26> &shift) {
	std::vector<int> found;
	int size_text = text.size();
	int size_pattern = pattern.size();
	int skip = 0;
	while(size_text - skip >= size_pattern){
		int i = size_pattern - 1;
		while(text[skip+i] == pattern[i]){
			if(i==0){
				found.push_back(skip);
				break;
			}
			--i;
		}
		skip += shift[text[skip+size_pattern-1]-'A'];
	}
	return found;
}

void solve(int start_x, int start_y, int dir_x, int dir_y, int n, int m, int k){
	std::string s;
	int x = start_x;
	int y = start_y;
	while(x>=0 && x<n && y>=0 && y < m){
		s.push_back(grid[x][y]);
		x += dir_x;
		y += dir_y;
	}

	for(int i=0; i<2*k; ++i){
		std::vector<int> found = boyer_moore(s, words[i], shifts[i]);
		for(auto f : found){
			x = start_x + f*dir_x;
			y = start_y + f*dir_y;
			for(unsigned int j=0; j<words[i].size(); ++j){
				mask[x][y] = true;
				x += dir_x;
				y += dir_y;
			}
		}
	}
}

void solve(const std::string &s) {
	reset();
	std::stringstream ss(s);
	int n, m;
	ss >> n >> m;
	int k;
	std::cin >> k;
	std::string word;
	for (int i = 0; i < k; ++i) {
		std::cin >> word;
		words.push_back(word);
		std::string word_reversed(word.rbegin(), word.rend());
		words.push_back(word_reversed);
	}

	shifts.resize(2 * k);
	for (int i = 0; i < 2 * k; ++i) {
		int size_pattern = words[i].size();
		std::fill(shifts[i].begin(), shifts[i].end(), size_pattern);
		for (int j = 0; j < size_pattern - 1; ++j) {
			shifts[i][words[i][j] - 'A'] = size_pattern - 1 - j;
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> grid[i][j];
		}
	}

	for(int i=0; i<n; ++i){
		solve(i, 0, 0, 1, n, m, k);
		solve(i, 0, 1, 1, n, m, k);
		solve(i, m-1, 1, -1, n, m, k);
	}

	for(int j=0; j<m; ++j){
		solve(0, j, 1, 0, n, m, k);
		solve(0, j, 1, -1, n, m, k);
		solve(0, j, 1, 1, n, m, k);
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!mask[i][j])
				std::cout << grid[i][j];
		}
	}
	std::cout << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::string first_line;
	while (std::getline(std::cin, first_line)) {
		if (!first_line.empty()) {
			solve(first_line);
		}
	}
}
