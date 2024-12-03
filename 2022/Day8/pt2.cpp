#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

typedef vector<vector<int>> grove;

// function prototypes
unsigned getScore(unsigned, unsigned, grove &);
unsigned checkNorth(unsigned, unsigned, grove &);
unsigned checkSouth(unsigned, unsigned, grove &);
unsigned checkEast(unsigned, unsigned, grove &);
unsigned checkWest(unsigned, unsigned, grove &);

// check if tree at position (a, b) is visible
unsigned getScore(unsigned a, unsigned b, grove &trees) {
// 	cout << "Checking " << trees[a][b] << " at "
// 		<< "(" << a << ", " << b << ")" << endl;

	// get direction scores
	unsigned north = checkNorth(a, b, trees);
// 	cout << "North: " << north << endl;

	unsigned south = checkSouth(a, b, trees);
// 	cout << "South: " << south << endl;
	
	unsigned east = checkEast(a, b, trees);
// 	cout << "East: " << east << endl;
	
	unsigned west = checkWest(a, b, trees);
// 	cout << "West: " << west << endl;
	
	// view score is the product of direction scores
	return (north * south * east * west);
}

// return tree score from (a, b) looking north
unsigned checkNorth(unsigned a, unsigned b, grove &trees) {
	int viewScore = 0;
	for (int i = a - 1; i >= 0; --i) {
		int tree = trees[i][b];
		++viewScore;
		if (tree >= trees[a][b]) {
			return viewScore;
		}
	}
	return viewScore;
}
	
// return tree score from (a, b) looking south
unsigned checkSouth(unsigned a, unsigned b, grove &trees) {
	int viewScore = 0;
	for (int i = a + 1; i <= trees.size() - 1; ++i) {
		int tree = trees[i][b];
		++viewScore;
		if (tree >= trees[a][b]) {
			return viewScore;
		}
	}
	return viewScore;
}

// return tree score from (a, b) looking east
unsigned checkEast(unsigned a, unsigned b, grove &trees) {
	int viewScore = 0;
	for (int j = b + 1; j <= trees.size() - 1; ++j) {
		int tree = trees[a][j];
		++viewScore;
		if (tree >= trees[a][b]) {
			return viewScore;
		}
	}
	return viewScore;
}

// return tree score from (a, b) looking west
unsigned checkWest(unsigned a, unsigned b, grove &trees) {
	int viewScore = 0;
	for (int j = b - 1; j >= 0; --j) {
		int tree = trees[a][j];
		++viewScore;
		if (tree >= trees[a][b]) {
			return viewScore;
		}
	}
	return viewScore;
}

int main(int argc, char *argv[]) {
	ifstream input(argv[1]);
	if (input) {
		cout << "Got file: " << argv[1] << endl;
	} else {
		cerr << "Error with file: " << argv[1] << endl;
	}
	
	grove trees;
	vector<int> row;
	
	string buff;
	while(getline(input, buff)) {
		istringstream iss(buff);
		char c;
		while (iss.get(c)) {
			row.push_back(c - '0');
		}
		trees.push_back(row);
		row.clear();
	}
	
	unsigned rowSize = trees[0].size();
	unsigned colSize = trees.size();
	
	int maxViewScore = 0;		// tree view score
	// iterate through sub-grove
	for (int i = 1; i < colSize - 1; ++i) {
		for (int j = 1; j < rowSize - 1; ++j) {
// 			cout << trees[i][j] << " ";
			int score = getScore(i, j, trees);
// 			cout << "Score: " << score << endl << endl;
			if (score > maxViewScore) {
				maxViewScore = score;
			}
		}
// 		cout << endl;
	} 

// 	cout << endl << endl;
		
	cout << "Max score: " << maxViewScore << endl;
	
	
	
	
	// print grove
// 	for (auto itr = trees.begin(); itr != trees.end(); ++itr) {
// 		for (auto it2 = (*itr).begin(); it2 != (*itr).end(); ++it2) {
// 			cout << *it2 << " ";
// 		}
// 		cout << endl;
// 	}
	
	return 0;
}