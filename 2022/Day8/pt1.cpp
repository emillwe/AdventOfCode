#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

typedef vector<vector<int>> grove;

// function prototypes
bool isVisible(unsigned, unsigned, grove &);
bool checkNorth(unsigned, unsigned, grove &);
bool checkSouth(unsigned, unsigned, grove &);
bool checkEast(unsigned, unsigned, grove &);
bool checkWest(unsigned, unsigned, grove &);

// check if tree at position (a, b) is visible
bool isVisible(unsigned a, unsigned b, grove &trees) {
	bool visibleFromNorth = checkNorth(a, b, trees);
	if (!visibleFromNorth) {
		bool visibleFromSouth = checkSouth(a, b, trees);
		if(!visibleFromSouth) {
			bool visibleFromEast = checkEast(a, b, trees);
			if (!visibleFromEast) {
				bool visibleFromWest = checkWest(a, b, trees);
				return visibleFromWest;
			} else {
				return visibleFromEast;
			}
		} else {
			return visibleFromSouth;
		}
	} else {
		return visibleFromNorth;
	}
}

// check if tree at position (a, b) is visible from north
bool checkNorth(unsigned a, unsigned b, grove &trees) {
	// TEST PRINTING:
// 	cout << "Testing " << trees[a][b] << " at (" << a
// 		<< ", " << b << ")" << endl;

	// iterate south along column till we reach (a, b)
	for (int i = 0; i < a; ++i) {
		int tree = trees[i][b];
		if (tree >= trees[a][b]) {
// 			cout << "Invisible!" << endl;
			return false;
		}
	}
// 	cout << "Visible!" << endl;
	return true;
}
	
// check if tree at position (a, b) is visible from south
bool checkSouth(unsigned a, unsigned b, grove &trees) {
	// TEST PRINTING:
// 	cout << "Testing " << trees[a][b] << " at (" << a
// 		<< ", " << b << ")" << endl;

	// iterate north along column till we reach (a, b)
	for (int i = trees.size() - 1; i > a; --i) {
		int tree = trees[i][b];
		if (tree >= trees[a][b]) {
// 			cout << "Invisible!" << endl;
			return false;
		}
	}
	
// 	cout << "Visible!" << endl;
	return true;
}

// check if tree at position (a, b) is visible from east
bool checkEast(unsigned a, unsigned b, grove &trees) {
	// TEST PRINTING:
// 	cout << "Testing " << trees[a][b] << " at (" << a
// 		<< ", " << b << ")" << endl;

	// iterate west along row till we reach (a, b)
	for (int j = trees[0].size() - 1; j > b; --j) {
		int tree = trees[a][j];
		if (tree >= trees[a][b]) {
// 			cout << "Invisible!" << endl;
			return false;
		}
	}
	
// 	cout << "Visible!" << endl;
	return true;
}

// check if tree at position (a, b) is visible from west
bool checkWest(unsigned a, unsigned b, grove &trees) {
	// TEST PRINTING:
// 	cout << "Testing " << trees[a][b] << " at (" << a
// 		<< ", " << b << ")" << endl;

	// iterate east along row till we reach (a, b)
	for (int j = 0; j < b; ++j) {
		int tree = trees[a][j];
		if (tree >= trees[a][b]) {
// 			cout << "Invisible!" << endl;
			return false;
		}
	}
	
// 	cout << "Visible!" << endl;
	return true;
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
	
	int numVisible = 0;		// number of visible trees
	// iterate through sub-grove
	for (int i = 1; i < colSize - 1; ++i) {
		for (int j = 1; j < rowSize - 1; ++j) {
// 			cout << trees[i][j] << " ";
			if(isVisible(i, j, trees)) {
				++numVisible;
			};
		}
		cout << endl;
	} 

	cout << endl << endl;
	
	cout << "Num interior visible: " << numVisible << endl;
	
	// all exterior trees are visible: perimeter - 4 corners
	int exteriorVisible = (trees.size() * 2) + (trees[0].size() * 2) - 4;
	
	cout << "Num exterior visible: " << exteriorVisible << endl;
	
	cout << "Total visible: " << numVisible + exteriorVisible << endl;
	
	
	
	
	// print grove
// 	for (auto itr = trees.begin(); itr != trees.end(); ++itr) {
// 		for (auto it2 = (*itr).begin(); it2 != (*itr).end(); ++it2) {
// 			cout << *it2 << " ";
// 		}
// 		cout << endl;
// 	}
	
	return 0;
}