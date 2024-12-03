#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;

typedef pair<char, char> roundPair;
typedef map<roundPair, char> resultMap;
typedef map<char, int> scoreMap;

// outcome scores
const int L_SCORE = 0;
const int D_SCORE = 3;
const int W_SCORE = 6;

// shape scores
const int R_SCORE = 1;
const int P_SCORE = 2;
const int S_SCORE = 3;

// build round/score tables
resultMap roundResults // outcome of a round, e.g. (A, X) -> D
{
	// round-------outcome-----opponent vs. us
	{ {'A', 'X'}, 'D' },	// R vs R
	{ {'A', 'Y'}, 'W' },	// R vs P
	{ {'A', 'Z'}, 'L' },	// R vs S
	
	{ {'B', 'X'}, 'L' },	// P vs R
	{ {'B', 'Y'}, 'D' },	// P vs P
	{ {'B', 'Z'}, 'W' },	// P vs S
	
	{ {'C', 'X'}, 'W' },	// S vs R
	{ {'C', 'Y'}, 'L' },	// S vs P
	{ {'C', 'Z'}, 'D' }		// S vs S
};

scoreMap outcomeScores // possible outcome scores, e.g. W -> 6
{
	{ 'L', L_SCORE },
	{ 'D', D_SCORE },
	{ 'W', W_SCORE }
};

scoreMap shapeScores // possible shape scores, e.g. Z -> 3
{
	{ 'X', R_SCORE },
	{ 'Y', P_SCORE },
	{ 'Z', S_SCORE }
};

// args: input file name, print flag
// print flag: ('t' / 'T') prints results after each round
int main(int argc, char *argv[]) {
	bool printFlag = false;
	
	if (argv[2]) {
		printFlag = (argv[2][0] == 't' || argv[2][0] == 'T');	
	}
	
	ifstream input(argv[1]);		// input file
	if (input) {
		cout << "Got file: " << argv[1] << "!\n\n";
		
		int totalScore = 0;		// running sum
		string roundString;		// current round
		
		while (!input.eof() && input.good()) {
			// read current round into buffer
			getline(input, roundString);
		
			// read round into roundPair
			istringstream is(roundString);
			roundPair p;
			is >> p.first >> p.second;
			
			// get round result
			char result = roundResults[p];
			
			// get outcome score
			int outcomeScore = outcomeScores[result];
			
			// get shape score
			int shapeScore = shapeScores[p.second];
			
			// this round's score
			int roundScore = outcomeScore + shapeScore;
			
			// update total score
			totalScore += roundScore;
			
			if (printFlag) {
				cout << "round: " << roundString << endl;
				cout << "result: " << result << endl;
				cout << "outcome score: " << outcomeScore << endl;
				cout << "shape score: " << shapeScore << endl;
				int roundTotal = outcomeScore + shapeScore;
				cout << "round total: " <<  roundTotal << endl << endl;
				cout << "input state: " << input.rdstate() << endl << endl;
			}
		}
		
		cout << "Total: " << totalScore << endl;
		
		// istream diagnostics
// 		cout << "eof:" << istringstream::eofbit << endl;
// 		cout << "badbit:" << istringstream::badbit << endl;
// 		cout << "goodbit:" << istringstream::goodbit << endl;
// 		cout << "failbit:" << istringstream::failbit << endl;
		
	} else {
		cerr << "Error reading file" << endl;
	}

	return 0;
}