// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=277&page=show_problem&problem=3421

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

typedef std::pair<double, double> Interval;

double maxWidth = 75.0;
double maxLength = 100.0;
double epsilon = 0.0000001;

std::vector<Interval> length;
std::vector<Interval> width;

/* <= */
bool less_than(double x, double y){
	return x < y+epsilon;
}

/* >= */
bool greater_than(double x, double y){
	return x > y-epsilon;
}

// For debugging
void print_interval(const Interval &i){
	std::cout << "[" << i.first << "," << i.second << "]";
}

bool check_intervals(const std::vector<Interval> &intervals, double max){
	double current_max;
	if(!less_than(intervals[0].first, 0)){
		return false;
	}
	current_max = intervals[1].second;
	for(unsigned int i=1; i<intervals.size(); ++i){
		if(less_than(intervals[i].first, current_max)){
			current_max = std::max(current_max, intervals[i].second);
		}
		else{
			break;
		}
	}
	return greater_than(current_max, max);
}

void reset(){
	length.clear();
	width.clear();
}

void read_intervals(int nx, int ny, double half_w){
	double r;
	for(int i=0; i<nx; i++){
		std::cin >> r;
		length.push_back({std::max(0.0, r-half_w), std::min(maxWidth, r+half_w)});
	}
	for(int i=0; i<ny; i++){
		std::cin >> r;
		width.push_back({std::max(0.0, r-half_w), std::min(maxLength, r+half_w)});
	}
}

// For debugging
void print(){
	std::cout << "Intervals on length : " << std::endl;
	for(const auto &i : length){
		print_interval(i);
		std::cout << " ";
	}
	std::cout << std::endl << "Intervals on width : " << std::endl;
	for(const auto &i : width){
		print_interval(i);
		std::cout << " ";
	}
}

void compute_solution(int nx, int ny, double w){
	reset();
	read_intervals(nx, ny, 0.5*w);
	std::sort(length.begin(), length.end());
	std::sort(width.begin(), width.end());
	bool b = check_intervals(length, maxWidth) && check_intervals(width, maxLength);
	if(b){
		std::cout << "YES" << std::endl;
	}
	else{
		std::cout << "NO" << std::endl;
	}
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int nx, ny;
	double w;
	while(true){
		std::cin >> nx >> ny >> w;
		if(nx==0){
			break;
		}
		compute_solution(nx, ny, w);
	}
}

