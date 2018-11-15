#include <iostream> 
#include <string.h> 
#include <vector> 
#define P 4 
#define R 4 

int total = 0; 

using namespace std; 
 
bool is_available(int process_id, int allocated[][R], 
				int max[][R], int need[][R], int available[]) 
{ 

	bool flag = true; 
 
	for (int i = 0; i < R; i++) { 

		if (need[process_id][i] > available[i]) 
			flag = false; 
	} 

	return flag; 
} 

void safe_sequence(bool marked[], int allocated[][R], int max[][R], 
				int need[][R], int available[], vector<int> safe) 
{ 

	for (int i = 0; i < P; i++) { 
 
		if (!marked[i] && is_available(i, allocated, max, need, available)) { 

			marked[i] = true; 
 
			for (int j = 0; j < R; j++) 
				available[j] += allocated[i][j]; 

			safe.push_back(i); 
			safe_sequence(marked, allocated, max, need, available, safe); 
			safe.pop_back(); 

			marked[i] = false; 

			for (int j = 0; j < R; j++) 
				available[j] -= allocated[i][j]; 
		} 
	} 

	if (safe.size() == P) { 

		total++; 
		for (int i = 0; i < P; i++) { 

			cout << "P" << safe[i] ; 
			if (i != (P - 1)) 
				cout << "--> "; 
		} 

		cout << endl; 
	} 
} 

int main() 
{ 

	int allocated[P][R] = { { 4,2,6,5 }, 
							{ 3,1,0,1 }, 
							{ 4,2,5,0}, 
							{ 1,0,0,2} }; 

	int max[P][R] = { { 7,6,7,7 }, 
					{ 6,5,3,4}, 
					{ 7,6,6,2 }, 
					{ 9,2,3,2} }; 

	int resources[R] = { 15,9,12,10 }; 

	int available[R]; 

	for (int i = 0; i < R; i++) { 

		int sum = 0; 
		for (int j = 0; j < P; j++) 
			sum += allocated[j][i]; 

		available[i] = resources[i] - sum; 
	} 

	vector<int> safe; 

	bool marked[P]; 
	memset(marked, false, sizeof(marked)); 

	int need[P][R]; 
	for (int i = 0; i < P; i++) 
		for (int j = 0; j < R; j++) 
			need[i][j] = max[i][j] - allocated[i][j]; 

	cout << "Safe sequences are:" << endl; 
	safe_sequence(marked, allocated, max, need, available, safe); 

	cout << "\nThere are total " << total << " safe-sequences" << endl; 
	return 0; 
} 
