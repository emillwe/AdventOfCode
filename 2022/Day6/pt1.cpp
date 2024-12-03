#include <iostream>
#include <queue>
#include <set>
#include <fstream>
#include <map>

using namespace std;

typedef queue<char> buffer;

const int BUFF_SIZE = 4;

int main(int argc, char* argv[]) {
	ifstream input(argv[1]);
	
	if (input) {
		cout << "Got file: " << argv[1] << endl;
	} else {
		cerr << "Error--no such file: " << argv[1] << endl;
	}
	
	buffer q;			// last 4 chars in signal
	set<char> s;		// unique chars in buffer
	map<char, int> m; 	// character histogram
	char c; 			// next char in signal

	// read first 4 chars
	for (int i = 0; i < BUFF_SIZE; ++i) {
		input.get(c);
		q.push(c);
		s.insert(c);
		++m[c];
	}
	
	// check if first 4 are unique
	if (s.size() == BUFF_SIZE) {
		return BUFF_SIZE;
	}
	
	// running tally of processed chars
	int processed = BUFF_SIZE;
	
	while (!input.eof()) {
		// remove this char at buffer front from set of uniques
		// only if there's exactly one left in buffer
		if (m[q.front()] == 1) {
			s.erase(q.front());	
		}
		--m[q.front()];		// update hsitogram
		q.pop();			// advance buffer
		
		input.get(c);	// read next char in signal
		s.insert(c);	// get ready to check buffer uniqueness
		q.push(c);		// add to buffer
		++m[c];			// update histogram
		++processed;
		
		// TEST PRINTING
		// check unique chars in buffer
// 		for (auto i = s.begin(); i != s.end(); ++i) {
// 			cout << *i << " ";
// 		}
// 		cout << endl;
		
		// check for unique buffer
		if (s.size() == BUFF_SIZE) {
			cout << "Processed " << processed << " chars." << endl;
			return 0;
		}
	}

	return 0;
}