// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3560

#include <iostream>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <vector>

typedef std::pair<double, double> HeightBreak;

double epsilon = 0.0000001;

/* == */
bool equal_to(double x, double y) {
	return std::abs(x - y) < epsilon;
}

std::vector<HeightBreak> height_breaks;
std::vector<HeightBreak> aggregated_height_breaks;

void reset() {
	height_breaks.clear();
	aggregated_height_breaks.clear();
}

double get_height(double total_water){
	double current_height = aggregated_height_breaks[0].first;
	double current_sup = aggregated_height_breaks[0].second;

	for(unsigned int i=1; i<aggregated_height_breaks.size(); ++i){
		double height = aggregated_height_breaks[i].first - current_height;
		if(height*current_sup > total_water)
			return current_height + total_water/current_sup;
		total_water -= height*current_sup;
		current_height = aggregated_height_breaks[i].first;
		current_sup = aggregated_height_breaks[i].second;
	}

	return -1.0;
}

void solve() {
	reset();
	int N_citerns;
	double base_height, height, width, depth;
	std::cin >> N_citerns;
	for (int i = 0; i < N_citerns; ++i) {
		std::cin >> base_height >> height >> width >> depth;
		height_breaks.push_back( { base_height, width * depth });
		height_breaks.push_back(
				{ base_height + height, -1.0 * width * depth });
	}
	double total_water;
	std::cin >> total_water;

	std::sort(height_breaks.begin(), height_breaks.end());

	double running_h = height_breaks[0].first;
	double running_sup = height_breaks[0].second;
	for(unsigned int i=1; i<height_breaks.size(); ++i){
		double new_h = height_breaks[i].first;
		if(!equal_to(running_h, new_h)){
			aggregated_height_breaks.push_back({running_h, running_sup});
			running_h = new_h;
		}
		running_sup += height_breaks[i].second;
	}
	aggregated_height_breaks.push_back({running_h, running_sup});

	double solution = get_height(total_water);

	if(solution<-0.5)
		printf("OVERFLOW\n");
	else
		printf("%.2f\n", solution);
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

