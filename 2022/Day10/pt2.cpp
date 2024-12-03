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
void drawCRT();
void noop();
void checkCycles();
int getSignalStrength();
int getStrengthSum();
pair<int, int> getXSprite();
int getScreenLine();
ostream &printScreen(ostream &);

// TODO: drawCRT on multiple lines
// i.e. 2d vector, select which row from modulo.
// print rows sequentially

// constants: functions
const int ADDX_PERIOD = 2;
const int NOOP_PERIOD = 1;
// CRT dims
const int CRT_ROW_SIZE = 40;
const int CRT_HEIGHT = 6;
const int SPRITE_SIZE = 3;

// global variables
int x = 1;			// register value
int cycle = 0;		// clock cycles
set<int> criticalCycles {20, 60, 100, 140, 180, 220};
map<int, int> cyclesToValues;		// register value at given clock cycle
vector<int> strengths;				// signal strength
vector<char> crtLine(CRT_ROW_SIZE, '.');
vector<vector<char>> crtScreen {CRT_HEIGHT, crtLine};

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
// 	cout << "Sum of strengths: " << getStrengthSum() << endl;
	
	// TODO: printScreen()
	printScreen(cout) << endl;
// 	for (auto c : crtLine) {
// 		cout << c;
// 	}
// 	cout << endl;
	
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

////////////////CPU COMMANDS////////////////


// add value to register
void addX(int amt) {
	for (int i = 0; i < ADDX_PERIOD; ++i) {
		++cycle;
		drawCRT();
		checkCycles();
	}
	x += amt;		// update register
}

// no operation
void noop() {
	for (int i = 0; i < NOOP_PERIOD; ++i) {
		++cycle;
		drawCRT();
		checkCycles();
	}
}

////////////////SIGNAL STRENGTH FUNCTIONS////////////////

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

// save signal strength at critcal clock cycles
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

////////////////CRT FUNCTIONS////////////////

// find x sprite on CRT line
pair<int, int> getXSprite() {
	int lower, upper;	// sprite bounds
	lower = x - 1;
	upper = x + 1;
	return {lower, upper};
}

// write contents to CRT line
void drawCRT() {
	// get current line on screen
	int screenLine = getScreenLine();
	vector<char> &line = crtScreen[screenLine];
	
	// get cursor from clock
	int cursor = (cycle % CRT_ROW_SIZE) - 1;
	
	// get sprite bounds
	pair<int, int> p = getXSprite();
	int lower = p.first;
	int upper = p.second;

	// if cursor within sprite bounds
	if (cursor >= lower && cursor <= upper) {
		// draw '#'
		line[cursor] = '#';
	}
}

// get current CRT line on screen between [0, CRT_HEIGHT)
int getScreenLine() {
	return cycle / CRT_ROW_SIZE;
}

// print CRT screen contents
ostream &printScreen(ostream &os) {
	for (vector<char> &v : crtScreen) {
		for (char c : v) {
			os << c << " ";
		}
		os << endl;
	}
	return os;
}