#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;

typedef pair<char, char> roundPair;
typedef map<roundPair, char> resultMap;
typedef map<char, int> scoreMap;
typedef map<char, char> shapeMap;

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

/*rock, paper, and scissors shapeMaps determine what we need
* to play for those respective shapes and a given outcome.
* NB first char refers to outcome (e.g. 'X' is lose).
* Second char refers to shape as before ('X' is rock) */
shapeMap rock 
{
	{'X', 'Z'},
	{'Y', 'X'},
	{'Z', 'Y'},
};

shapeMap paper 
{
	{'X', 'X'},
	{'Y', 'Y'},
	{'Z', 'Z'},
};

shapeMap scissors 
{
	{'X', 'Y'},
	{'Y', 'Z'},
	{'Z', 'X'},
};

scoreMap outcomeScores // possible outcome scores, e.g. W -> 6
{
	{ 'X', L_SCORE },
	{ 'Y', D_SCORE },
	{ 'Z', W_SCORE }
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
	bool printFlag = true;
	
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
			
			char result = p.second;
			
			// get shapeMap corresponding to opponent's shape
			shapeMap *sM;
			
			switch (p.first) {
				case 'A':
					sM = &rock;
					break;
				case 'B':
					sM = &paper;
					break;
				case 'C':
					sM = &scissors;
					break;
				default:
					cerr << "Did not recognize shape!\n";
			}
			
			// get shape given result
			char shape = (*sM)[result];
			
			// get outcome score
			int outcomeScore = outcomeScores[result];
			
			// get shape score
			int shapeScore = shapeScores[shape];
			
			// this round's score
			int roundScore = outcomeScore + shapeScore;
			
			// update total score
			totalScore += roundScore;
			
			if (printFlag) {
				cout << "round: " << roundString << endl;
				cout << "played: " << shape << endl;
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