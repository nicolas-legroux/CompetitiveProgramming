// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=475

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

double EPSILON = 0.000001;

typedef std::array<int, 3> Point;
double distance_between_points[6][6];
std::vector<Point> points;
std::vector<double> max_radiuses;
std::vector<double> radiuses;

double dist(const Point &p1, const Point &p2) {
	int d = 0;
	for (int i = 0; i < 3; ++i) {
		d += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	}
	return std::sqrt((double) d);
}

bool is_inside_box(const Point &corner1, const Point &corner2, const Point &p) {
	return ((p[0] > corner1[0] && p[0] < corner2[0])
			|| (p[0] > corner2[0] && p[0] < corner1[0]))
			&& ((p[1] > corner1[1] && p[1] < corner2[1])
					|| (p[1] > corner2[1] && p[1] < corner1[1]))
			&& ((p[2] > corner1[2] && p[2] < corner2[2])
					|| (p[2] > corner2[2] && p[2] < corner1[2]));
}

std::vector<double> compute_max_radiuses(const Point &corner1,
		const Point &corner2, int m) {
	std::vector<double> w;
	for (int i = 0; i < m; ++i) {
		std::vector<double> v = { std::abs(
				(double) (corner1[0] - points[i][0])), std::abs(
				(double) (corner2[0] - points[i][0])), std::abs(
				(double) (corner1[1] - points[i][1])), std::abs(
				(double) (corner2[1] - points[i][1])), std::abs(
				(double) (corner1[2] - points[i][2])), std::abs(
				(double) (corner2[2] - points[i][2])) };

		auto itr = std::min_element(v.begin(), v.end());
		w.push_back(*itr);
	}
	return w;
}

void inflate_balloon(int i, int m) {
	double r = max_radiuses[i];
	max_radiuses[i] = 0;
	if(r>EPSILON){
		radiuses[i] = r;
		for (int j = 0; j < m; ++j) {
			if (i != j) {
				if (distance_between_points[i][j] < r) {
					max_radiuses[j] = 0.0;
				} else {
					max_radiuses[j] = std::min(max_radiuses[j],
							distance_between_points[i][j] - r);
				}
			}
		}
	}
}

double solve(std::vector<int> permutation) {
	int m = permutation.size();
	for(int i=0; i<m; ++i)
		inflate_balloon(permutation[i], m);
	double vol_occupied = 0;
	double PI = 3.1415926535;
	for (int i = 0; i < m; ++i) {
		vol_occupied += 4.0 / 3.0 * PI * std::pow(radiuses[i], 3.0);
	}
	return vol_occupied;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;
	int count = 1;
	while (true) {
		std::cin >> n;
		if (n == 0)
			break;
		std::cout << "Box " << count << ": ";
		++count;

		int x, y, z;
		std::cin >> x >> y >> z;
		Point corner1 = { x, y, z };
		std::cin >> x >> y >> z;
		Point corner2 = { x, y, z };

		int m = 0;

		points.clear();

		for (int i = 0; i < n; ++i) {
			std::cin >> x >> y >> z;
			Point p = { x, y, z };
			if (is_inside_box(corner1, corner2, p)) {
				++m;
				points.push_back(p);
			}
		}

		for (int i = 0; i < m - 1; ++i) {
			for (int j = i + 1; j < m; ++j) {
				distance_between_points[i][j] = distance_between_points[j][i] =
						dist(points[i], points[j]);
			}
		}

		radiuses.resize(m);
		max_radiuses.resize(m);

		std::vector<double> max_r = compute_max_radiuses(corner1, corner2, m);

		std::vector<int> permutation(m);
		std::iota(permutation.begin(), permutation.end(), 0);

		double best_vol = 0;

		do {
			std::fill(radiuses.begin(), radiuses.end(), 0);
			max_radiuses = max_r;
			double vol = solve(permutation);
			if(vol>best_vol) best_vol = vol;
		} while (std::next_permutation(permutation.begin(), permutation.end()));

		double vol_box = 1.0;
		for (int i = 0; i < 3; ++i) {
			vol_box *= std::abs((double) (corner1[i] - corner2[i]));
		}

		std::cout << (int)(std::round(vol_box - best_vol)) << "\n\n";
	}
}
