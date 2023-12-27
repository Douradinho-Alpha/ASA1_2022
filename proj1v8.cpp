#include <iostream>
#include <vector>
#include <map>
#include <cstring>
using namespace std;


vector<int> input;

map <vector<int>, unsigned long long> cache;

void get_input(){
	int temp;
	int n,m;
	cin>>n;
	cin>>m;
	for(int i=0; i<n; i++){
		cin >> temp;
		input.push_back(temp);
	}
}

/*
	Procura linhas consecutivas que tenham elementos maiores que 1.
	Se não existirem, é porque o puzzle foi resolvido.
	*/
bool has_solved(vector<int> puzzle){
	int counter =0;
	for(int i=0; i<(int)puzzle.size()-1 && counter<1; i++){
		if(puzzle[i]>1&&puzzle[i+1]>1)
			counter++;
	}
	return (counter>0 ? false : true);
}


int get_max_index(vector<int> puzzle){
	int biggest =0, index=0;
	for(int i=0; i<(int)puzzle.size();i++){
		if(puzzle[i]>=biggest){
			biggest=puzzle[i];
			index=i;
		}
	}
	return index;
}

int get_lsize(vector<int> puzzle, int cut_index){
	int lsize = 1;
	for(int i=cut_index; puzzle[i] == puzzle[i+1]
		&&lsize<puzzle[i] &&i<(int)puzzle.size()-1
		&&puzzle[i]>1; i++){
		
		lsize++;
	}
	return lsize;
}

unsigned long long solver(vector<int> puzzle){
	unsigned long long sol=0;
	int cut_index = get_max_index(puzzle);
	if(cache.find(puzzle)!=cache.end()){
		return cache.at(puzzle);
	}

	if(has_solved(puzzle)){
		cache.insert({puzzle, 1});
		return 1;
	}
	int lsize=1;
	int max_len = puzzle[cut_index];
	for(int i=cut_index; puzzle[i]==max_len&&lsize<=max_len; i--){
		vector<int> next_puzzle;
		
		for(int j = 0; j<(int)puzzle.size(); j++){
			if(j<=cut_index&&j>cut_index-lsize){
				next_puzzle.push_back(puzzle[j]-lsize);
			}
			else{
				next_puzzle.push_back(puzzle[j]);
			}
		}
		unsigned long long temp = solver(next_puzzle);
		sol +=temp;
		cache.insert({next_puzzle, temp});
		lsize++;
	}

	return sol;
}




int main(){
	get_input();
	if(input[input.size()-1]==0)
		printf("0\n");
	else
		printf("%llu\n", solver(input));
	return 0;
}
