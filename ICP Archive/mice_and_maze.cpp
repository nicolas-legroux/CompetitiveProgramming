// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3553

#include <vector>
#include <list>
#include <iostream>
#include <limits>

typedef std::pair<int, int> Edge;
typedef std::vector<std::list<Edge>> EdgeList;

EdgeList edge_list;
std::vector<int> times;
std::vector<bool> visited;

void reset(){
    edge_list.clear();
    times.clear();
    visited.clear();
}

int next_vertex(){
    int next = -1;
    int best_distance = std::numeric_limits<int>::max();

    for(unsigned int i=0; i<visited.size(); ++i){
        if(!visited[i] && times[i] < best_distance){
            best_distance = times[i];
            next = i;
        }
    }

    return next;
}

void run_dijkstra(){
    int next;
    while(true){
        next = next_vertex();
        if(next == -1){
            break;
        }
        else{
            visited[next] = true;
            for(const auto &edge : edge_list[next]){
                int neighbor = edge.first;
                times[neighbor] = std::min(times[neighbor], times[next] + edge.second);
            }
        }
    }

}

int get_total_mice(int T_Total){
    int count = 0;
    for(auto i : times){
        if(i<=T_Total){
            ++count;
        }
    }
    return count;
}

void solve(){
    reset();
    int N, E, T_total, M;
    std::cin >> N >> E >> T_total;

    edge_list.resize(N);
    times.resize(N);
    visited.resize(N);

    for(unsigned int i=0; i<times.size(); ++i){
        times[i] = std::numeric_limits<int>::max();
        visited[i] = false;
    }

    times[E-1] = 0;

    std::cin >> M;
    int A, B, T;
    for(int i=0; i<M; ++i){
        std::cin >> A >> B >> T;
        edge_list[B-1].push_back({A-1, T});
    }

    run_dijkstra();
    std::cout << get_total_mice(T_total) << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int n_runs;
    std::cin >> n_runs;
    while (n_runs > 0) {
        solve();
        --n_runs;
        if(n_runs>0){
            std::cout << "\n";
        }
    }
}


