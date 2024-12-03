#include <iostream>
#include <fstream>

using namespace std;

int getMaxCals(string fileName, bool print = false) {
	ifstream input(fileName);	// input file
	int maxCals = 0;			// max calories an elf is carrying
	
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
				maxCals = (calSum > maxCals) ? calSum : maxCals;
				calSum = 0;		// reset running sum
			}
		}
		// check last elf
		maxCals = (calSum > maxCals) ? calSum : maxCals;
	} else {
		cerr << "No data!" << endl;
	}
	
	return maxCals;
}

int main(int argc, char *argv[]) {

	cout << getMaxCals(argv[1]) << endl;

	return 0;
}
