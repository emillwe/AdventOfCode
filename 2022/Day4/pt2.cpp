#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

typedef pair<int, int> range;

const int PAIR_SIZE = 2;
const int GROUP_SIZE = 2;

// given two pairs of numbers, determine if one range is fully contained in the other
bool isContained(pair<int, int> p1, pair<int, int> p2) {
	// first pair inside second pair
	bool firstInside = (p1.first >= p2.first && p1.second <= p2.second);
	
	// second pair inside first pair
	bool lastInside = (p2.first >= p1.first && p2.second <= p1.second);
	return (firstInside || lastInside);
}

// given two ranges of numbers, determine if they overlap
bool isOverlap(pair<int, int> p1, pair<int, int> p2) {
	bool p1First = (p1.second >= p2.first) && (p1.first <= p2.first);
	bool p2First = (p2.second >= p1.first) && (p2.first <= p1.first);
	return ((p1First != p2First) || isContained(p1, p2));
}

int main(int argc, char *argv[]) {
	ifstream input(argv[1]);
	
	if (input) {
		cout << "Got file!" << endl << endl;
	} else {
		cerr << "Failed to read " << argv[1] << endl;
		return -1;
	}
	
	int numOverlap = 0;	// total number of overlapping assignments
	
	string line;
	string elf1, elf2;
	string section;
	range r1, r2;
	
	// read next pair of assignments
	while (getline(input, line)) {
		cout << "Line: " << line << endl;
		istringstream is1(line);
		
		// first elf's assignment
		getline(is1, elf1, ',');
		cout << "Elf 1: " << elf1 << endl;
		istringstream is2(elf1);
		
		// first elf's range limits
		getline(is2, section, '-');
		r1.first = stoi(section);
		getline(is2, section, '-');
		r1.second = stoi(section);
		
		cout << "Assignment: " << r1.first << " " << r1.second << endl;
		is2.clear();
		
		// second elf's assignment
		getline(is1, elf2, ',');
		cout << "Elf 2: " << elf2 << endl;
		is2.str(elf2);
		
		// second elf's range limits
		getline(is2, section, '-');
		r2.first = stoi(section);
		getline(is2, section, '-');
		r2.second = stoi(section);
		
		cout << "Assignment: " << r2.first << " " << r2.second << endl;
		
		// check for assignment overlap
		if (isOverlap(r1, r2)) {
			++numOverlap;
			cout << "Overlapping!\n";
		}
		
		cout << endl;
	}
	
	cout << "Total overlap: " << numOverlap << endl;

	return 0;
}