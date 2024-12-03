#include <iostream>
#include <unordered_map>
#include <fstream>
#include <algorithm>

using namespace std;

const int LOWER_OFFSET = 96;
const int UPPER_OFFSET = 38;

// given a pack item (char c),
// return that item's priority, or
// -1 if failure
int getPriority(char c) {
	// make sure c is alphabetic char
	if (!isalpha(c)) {
		cerr << "Error: non alphabetic char in pack" << endl;
		return -1;
	}
	
	if (islower(c)) {
		return c - LOWER_OFFSET;
	} else { // c is uppercase
		return c - UPPER_OFFSET;
	}
}

int main(int argc, char *argv[]) {
	ifstream input(argv[1]);
	if (input) {
		cout << "Got file!" << endl << endl;
	} else {
		cerr << argv[1] <<" not found!" << endl;
	}
	
	int prioritySum = 0;		// running sum of item priorities
	string pack;				// pack is a string of letters
	
	// read current line into pack
	while (getline(input, pack)) {
		auto length = pack.length();

		// separate pack compartments
		string comp1(pack.begin(), pack.begin() + length / 2);
		string comp2(pack.begin() + length / 2, pack.end());
		
		// test printing
// 		cout << pack << ": " << length << endl;
// 		cout << comp1 << ": " << comp1.length() << endl;
// 		cout << comp2 << ": " << comp2.length() << endl << endl;

		// sort compartments for intersection
		sort(comp1.begin(), comp1.end());
		sort(comp2.begin(), comp2.end());
		
		string common;		// intersection of compartments
		set_intersection
		(
			comp1.begin(), comp1.end(), comp2.begin(), comp2.end(), &common
		);
		
		// test printing
// 		cout << common << endl;
		
		// TODO: right now, only one char in string.
		// This will change if multiple items in
		// both compartments
		int itemPriority = getPriority(common[0]);
		
		prioritySum += itemPriority;
	}
	cout << "Sum of priorities: " << prioritySum << endl;
	
	return 0;
}