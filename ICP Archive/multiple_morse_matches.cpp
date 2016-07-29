// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3554

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

const int MORSE_MAX_SIZE = 1000;
std::vector<std::string> morse_code = {
		".-",	//A
		"-...",	//B
		"-.-.",	//C
		"-..",	//D.
		".",	//E
		"..-.",	//F
		"--.",	//G
		"....",	//H
		"..",	//I
		".---",	//J
		"-.-",	//K
		".-..",	//L
		"--",	//M
		"-.",	//N.
		"---",	//O
		".--.",	//P
		"--.-",	//Q
		".-.",	//R
		"...",	//S
		"-",	//T
		"..-",	//U
		"...-",	//V,
		".--",	//W
		"-..-",	//X
		"-.--",	//Y
		"--.."	//Z
};

std::string get_morse_of_word(const std::string &word){
	std::stringstream ss;
	for(char c : word)
		ss << morse_code[c-'A'];
	return ss.str();
}

std::string code;
std::unordered_map<std::string, int> morse_to_count;
std::vector<int> mem;

void reset(){
	morse_to_count.clear();
	mem = std::vector<int>(MORSE_MAX_SIZE);
}

int get_morse_to_count(const std::string &s){
	auto it = morse_to_count.find(s);
	if(it == morse_to_count.end())
		return 0;
	else
		return it->second;
}

void compute_prefixcount(int i){
	mem[i] = get_morse_to_count(code.substr(0, i+1));
	if(i>0)
		for(int k=1; k<=i; k++)
			mem[i] += mem[k-1]*get_morse_to_count(code.substr(k, i-k+1));
}

void solve(){
	reset();
	int dict_size;
	std::cin >> code >> dict_size;
	std::string word;
	for(int i=0; i<dict_size; i++){
		std::cin >> word;
		++morse_to_count[get_morse_of_word(word)];
	}
	for(unsigned int k=0; k<code.size(); ++k)
		compute_prefixcount(k);
	std::cout << mem[code.size()-1] << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
	int n_runs;
	std::cin >> n_runs;
	while (n_runs > 0) {
		solve();
		--n_runs;
		if(n_runs>0)
			std::cout << std::endl;
	}
}
