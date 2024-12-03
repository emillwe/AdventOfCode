#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define VECTOR_SIZE 3

int getMaxCals(string fileName, bool print = false) {
	ifstream input(fileName);			// input file
	vector<int> maxCals {0, 0, 0};		// top 3 calorie loads
	int min = *maxCals.rbegin();
	
	if (input) {	// check for valid file
		cout << "Got file!" << endl;
		
		int currCals = 0;
		int calSum = 0;
		string next;
		
		// read until there's nothing left in the stream
		while (getline(input, next)) {
			if (!next.empty()) {		// if there's not a line break,
				currCals = stoi(next);
				calSum += currCals;		// update running sum
			} else {	// newline
				if (print) {
					cout << "calSum: " << calSum << endl;
				}
				// check for new max
// 				maxCals = (calSum > maxCals) ? calSum : maxCals;
				if (calSum > min) {
					auto itr = maxCals.begin();
					// TODO: iterator out of bounds?
					while (calSum < *itr) {
						++itr;
					}
					// calSum <= *(itr - 1): insert at itr
					maxCals.insert(itr, calSum);
					maxCals.pop_back();			// remove old minimum
					min = *maxCals.rbegin();	// new minimum
				}
				calSum = 0;		// reset running sum
			}
		}
		// check last elf
		if (calSum > min) {
			auto itr = maxCals.begin();
			while (calSum < *itr) {
				++itr;
			}
			// calSum <= *(itr - 1): insert at itr
			maxCals.insert(itr, calSum);
			maxCals.pop_back();			// remove old minimum
			min = *maxCals.rbegin();	// new minimum
		}
	} else {
		cerr << "No data!" << endl;
	}
	
	// sum top 3 caloric loads
	int maxSum = 0;
	for (auto &elem : maxCals) {
		maxSum += elem;
	}
	
	return maxSum;
}

int main(int argc, char *argv[]) {

	cout << getMaxCals(argv[1]) << endl;

	return 0;
}
