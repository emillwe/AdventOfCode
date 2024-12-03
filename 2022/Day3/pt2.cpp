#include <iostream>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>

using namespace std;

const int LOWER_OFFSET = 96;
const int UPPER_OFFSET = 38;
const int ELF_GROUP_SIZE = 3;

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

// given a group of packs, return a string
// containing all common items
string getCommonItems(vector<string> &packs, bool printFlag = true) {
	for (auto &pack : packs) {
		sort(pack.begin(), pack.end());
	}

	// types of item in each pack
	string &pack1(packs[0]), 
			&pack2(packs[1]),
			&pack3(packs[2]);
			
	if (printFlag) {
		cout << pack1 << endl << pack2 << endl << pack3 << endl << endl;
	}
	
	string common;
	set_intersection(
		pack1.begin(), pack1.end(),
		pack2.begin(), pack2.end(),
		back_inserter(common)
	);
	
	string common2;
	set_intersection(
		common.begin(), common.end(),
		pack3.begin(), pack3.end(),
		back_inserter(common2)
	);
	
	return common2;
}

int main(int argc, char *argv[]) {
	bool printFlag = false;
	
	ifstream input(argv[1]);
	if (input) {
		cout << "Got file!" << endl << endl;
	} else {
		cerr << argv[1] <<" not found!" << endl;
		return -1;
	}
	
	int prioritySum = 0;			// running sum of item priorities
	string pack;					// pack is a string of letters
	vector<string> groupPacks;		// all packs of a group of elves
	
	// read all packs
	// TODO: abstraction for intersection of >3 packs?
	int packCount = 0;
	while (input.good()) {
		for (int i = 0; i < ELF_GROUP_SIZE; ++i) {
			getline(input, pack);
			groupPacks.push_back(pack);
		}
	
		string common = getCommonItems(groupPacks, printFlag);

		if (common.empty()) {
			cerr << "No intersection!" << endl << endl;
		} else {
			if (printFlag) {
				cout << "Common: " << common << endl << endl;	
			}
		}
		groupPacks.clear();

// 		// TODO: right now, only one char in string.
// 		// This will change if multiple common items
// 		// among group
		int itemPriority = getPriority(common[0]);
		
		prioritySum += itemPriority;
	}
	
	cout << "Sum of priorities: " << prioritySum << endl;
	
	return 0;
}