#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

typedef pair<int, int> range;

const int PAIR_SIZE = 2;
const int GROUP_SIZE = 2;

// given two pairs of numbers, determine if one range is fully contained in the other
bool isContained(pair<int, int> p1, pair<int, int> p2) {
	bool firstInside = (p1.first >= p2.first && p1.second <= p2.second);
	bool lastInside = (p2.first >= p1.first && p2.second <= p1.second);
	return (firstInside || lastInside);
}

int main(int argc, char *argv[]) {
	ifstream input(argv[1]);
	
	if (input) {
		cout << "Got file!" << endl << endl;
	} else {
		cerr << "Failed to read " << argv[1] << endl;
		return -1;
	}
	
	int numContained = 0;	// total number of wholly contained
							// assignments
	
	string line;
	string elf1, elf2;
	string section;
	range r1, r2;
	
	// read next pair of assignments
	while (getline(input, line)) {
		cout << "Line: " << line << endl;
		istringstream is1(line);
		
		getline(is1, elf1, ',');
		cout << "Elf 1: " << elf1 << endl;
		istringstream is2(elf1);
		
		getline(is2, section, '-');
		r1.first = stoi(section);
		getline(is2, section, '-');
		r1.second = stoi(section);
		
		cout << "Assignment: " << r1.first << " " << r1.second << endl;
		is2.clear();
		
		getline(is1, elf2, ',');
		cout << "Elf 2: " << elf2 << endl;
		is2.str(elf2);
		
		getline(is2, section, '-');
		r2.first = stoi(section);
		getline(is2, section, '-');
		r2.second = stoi(section);
		
		cout << "Assignment: " << r2.first << " " << r2.second << endl;
		
		if (isContained(r1, r2)) {
			++numContained;
			cout << "Contained!\n";
		}
		
		cout << endl;
	}
	
	cout << "Total contained: " << numContained << endl;

	return 0;
}