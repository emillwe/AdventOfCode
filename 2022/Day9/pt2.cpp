#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <cmath>
#include <vector>

using namespace std;

typedef pair<int, int> point;

const int NUM_KNOTS = 10;

// string pointToString(point p) {
// 	return ("(" + string(p.first) + ", " + string(p.second) + ")");
// }

// end of a rope with position
class RopeEnd {
	private:
		int x, y;				// coordinates
		set<point> visited;		// visited coordinates
	public:
		// constructors
		RopeEnd(): x(0), y(0) {
			visited.insert(this->getPos());
		}
		
		RopeEnd(int a, int b): x(a), y(b) {
			visited.insert(this->getPos());
		}
		
		// getter methods
		point getPos() {
			return {x, y};
		}
		
		// set new position and return it
		point setPos(int a, int b) {
			x = a;
			y = b;
			
			return this->getPos();
		}
		
		// move one step in a given direction
		void move(char c) {
			point pos = this->getPos();
			
			int a = pos.first;
			int b = pos.second;
			
			switch(c) {
				case 'U':
					this->setPos(a, b + 1);
					break;
				case 'D':
					this->setPos(a, b - 1);
					break;
				case 'L':
					this->setPos(a - 1, b);
					break;
				case 'R':
					this->setPos(a + 1, b);
					break;
				default:
					cerr << "Did not recognize direction" << endl;
			}
		}
		
		// move a given number of steps in a given direction
		void moveSteps(char c, int steps) {
			for (int i = 0; i < steps; ++i) {
				move(c);
			}
		}
		
		// follow another rope end and return new position
		point follow(RopeEnd &r) {
			// if head ant tail are not touching
			if (getDist(r) > 1) {
				point diff = getPosDiff(r);
				int dX = diff.first;
				int dY = diff.second;
				
				/* case I: if the head is ever two steps directly up,
				* down, left, or right from the tail, the tail must
				* also move one step in that direction so it remains
				* close enough */
				if (!dX || !dY) {
					// move in the direction of the nonzero element
					if (dX) {
						if (dX > 0) {
							// move right
							move('R');
						} else { // dX < 0
							// move left
							move('L');
						}
					} else { // dY is nonzero
						if (dY > 0) {
							// move up
							move('U');
						} else { // dY < 0
							move('D');
						}
					}
				} else { // dX and dY are nonzero
					/* case II: if the head and tail aren't touching
					* and aren't in the same row or column, the tail
					* always moves one step diagonally to keep up */
					char dirX, dirY;
					if (dX > 0) {
						dirX = 'R';
					} else {
						dirX = 'L';
					}
					if (dY > 0) {
						dirY = 'U';
					} else {
						dirY = 'D';
					}
					// move diagonally
					move(dirX);
					move(dirY);
				}
				
			}
			// add new position to visited
			visited.insert(getPos());
			
			return getPos();
		}
		
		// get position difference from this point to another
		point getPosDiff(RopeEnd &r) {
			point pos = getPos();		// this rope end's position
			point target = r.getPos();		// target's position
			
			// calculate x and y distances
			int dX = target.first - pos.first;
			int dY = target.second - pos.second;
			
			return {dX, dY};
		}
		
		// get distance from this point to another
		int getDist(RopeEnd &r) {
			point diff = getPosDiff(r);		// get position difference
			
			// pythagorean theorem
			int radius = sqrt(
				pow(diff.first, 2) + pow(diff.second, 2)
			);
			
			// NB: radius is an int. For our purposes, root 2 is identical to 1.
			return radius;
		}
		
		// print current position
		ostream &printPos(ostream &os) {
			point pos = this->getPos();
			os << "(" << pos.first << ", "
				<< pos.second << ")";
			return os;
		}
		
		// print visited points
		ostream &printVisited(ostream &os) {
			for (auto elem : visited) {
				os << "(" << elem.first << ", "
					<< elem.second << ") ";
			}
			return os;
		}
		
		unsigned getNumVisited() {
			return visited.size();
		}
};

int main(int argc, char *argv[]) {
	ifstream input(argv[1]);
	
	if (input) {
		cout << "Got file: " << argv[1] << endl;
	} else {
		cerr << "Couldn't read " << argv[1] << endl;
	}
	
	// make rope
	vector<RopeEnd> rope(10);
		
	// read instructions
	int lineNo = 0;
	string buff;
	while (getline(input, buff)) {
		istringstream iss(buff);
		char dir;				// direction of rope head
		unsigned steps;			// number of steps in direction
		iss >> dir >> steps;	// read this instruction
		++lineNo;
			
		// move rope
		for (int i = 0; i < steps; ++i) {
			// move rope head
			rope[0].move(dir);
			
			// subsequent knots follow those in front
			for (auto itr = rope.begin() + 1; itr != rope.end(); ++itr) {
				RopeEnd &prev = *(itr - 1);
				(*itr).follow(prev);
			}
		}
	}
	
	RopeEnd &tail = *(rope.end() - 1);
	
	cout << tail.getNumVisited() << " points visited" << endl;	

	return 0;
}