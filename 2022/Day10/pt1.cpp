#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>

using namespace std;

// function prototypes
void processLine(string);
void addX(int);
void noop();
void checkCycles();
int getSignalStrength();
int getStrengthSum();

// constants: functions
const int ADDX_PERIOD = 2;
const int NOOP_PERIOD = 1;
// CRT dims
const int CRT_ROW_SIZE = 40;
const int CRT_HEIGHT = 6;

// global variables
int x = 1;			// register value
int cycle = 0;		// clock cycles
set<int> criticalCycles {20, 60, 100, 140, 180, 220};
map<int, int> cyclesToValues;		// register value at given clock cycle
vector<int> strengths;				// signal strength

int main(int argc, char *argv[]) {
	// check input
	ifstream input(argv[1]);
	if (input) {
		cout << "Got file: " << argv[1] << endl;
	} else {
		cerr << "Couln't read: " << argv[1] << endl;
	}
	
	// read input
	string buff;
	while (getline(input, buff)) {
		// process command
		processLine(buff);
	}
	
	// print sum of signal strengths
	cout << "Sum of strengths: " << getStrengthSum() << endl;
	
	return 0;
}

// execute command at given line
void processLine(string str) {
	istringstream iss(str);
	string command;		// e.g. addx or noop
	iss >> command;
	
	if (command == "addx") {
		int amt;
		iss >> amt;
		
		addX(amt);
	}
	else if (command == "noop") {
		noop();
	}
}

// add value to register
void addX(int amt) {
	for (int i = 0; i < ADDX_PERIOD; ++i) {
		++cycle;
		checkCycles();
	}
	x += amt;
}

// no operation
void noop() {
	for (int i = 0; i < NOOP_PERIOD; ++i) {
		++cycle;
		checkCycles();
	}
}

// check if current cycle is critical
void checkCycles() {
	if (criticalCycles.count(cycle)) {
		// save x value at this cycle
		cyclesToValues[cycle] = x;
		cout << "Cycle: " << cycle << " X: " << x << endl;
		cout << "Signal strength: " << getSignalStrength() << endl;
		
		// save signal strength
		strengths.push_back(getSignalStrength());
	}
}

// return signal strength
int getSignalStrength() {
	return x * cycle;
}

// sum all signal strengths
int getStrengthSum() {
	int sum = 0;
	for (auto i : strengths) {
		sum += i;
	}
	return sum;
}