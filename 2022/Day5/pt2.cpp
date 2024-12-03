#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

typedef stack<char> pile;
typedef vector<pile> cargo;

// const int NUM_STACKS = 3; // EXAMPLE RUN
const int NUM_STACKS = 9;
const int INDEX_OFFSET = 1;

// piles of crates
pile p1({'L', 'N', 'W', 'T', 'D'});
pile p2({'C', 'P', 'H'});
pile p3({'W', 'P', 'H', 'N', 'D', 'G', 'M', 'J'});
pile p4({'C', 'W', 'S', 'N', 'T', 'Q', 'L'});
pile p5({'P', 'H', 'C', 'N'});
pile p6({'T', 'H', 'N', 'D', 'M', 'W', 'Q', 'B'});
pile p7({'M', 'B', 'R', 'J', 'G', 'S', 'L'});
pile p8({'Z', 'N', 'W', 'G', 'V', 'B', 'R', 'T'});
pile p9({'W', 'G', 'D', 'N', 'P', 'L'});

// full cargo
cargo c {p1, p2, p3, p4, p5, p6, p7, p8, p9};

// EXAMPLE DATA:
// pile p1({'Z', 'N'});
// pile p2({'M', 'C', 'D'});
// pile p3({'P'});
// 
// cargo c {p1, p2, p3};

int main(int argc, char *argv[]) {
	ifstream input(argv[1]);
	if (input) {
		cout << "Got file " << argv[1] << endl << endl;
	} else {
		cerr << "Error reading file " << argv[1] << endl;
	}
	
	string command;
	// read each crane operation
	while (getline(input, command)) {
		istringstream iss(command);
		
		int numMoved, from, to;
		string buffer;
		
		// parse command
		// TODO: Learn regex!
		getline(iss, buffer, ' ');	// read "move"
		iss >> buffer;				// read number
		numMoved = stoi(buffer);	// save number as int

		iss >> buffer;				// read "from"
		iss >> buffer;				// read "from" stack number
		from = stoi(buffer);

		iss >> buffer;				// read "to"
		iss >> buffer;				// read "to" stack number
		to = stoi(buffer);
		
		// convert stack numbers to indices
		int fromIndex = from - INDEX_OFFSET;
		int toIndex = to - INDEX_OFFSET;
		
		pile temp; // temporary pile to preserve relative order

		// perform crane operations
		for (int i = 0; i < numMoved; ++i) {
			// remove from cargo pile
			char curr = c[fromIndex].top();
			c[fromIndex].pop();
			
			// place on temporary pile
			temp.push(curr);
		}
		
		for (int i = 0; i < numMoved; ++i) {
			// remove from temp pile
			char curr = temp.top();
			temp.pop();
			
			// place on cargo pile
			c[toIndex].push(curr);
		}
	}
	
	// read top of each cargo pile
	string result;
	for (int i = 0; i < NUM_STACKS; ++i) {
		result += c[i].top();
	}
	
	cout << result << endl;
	
	return 0;
}