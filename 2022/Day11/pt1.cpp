#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int RELIEF_LEVEL = 3;

// functions
int relief(int);

// classes
class Monkey {
	private:
		int inspections = 0;				// number of times monkey has inspected items
		queue<int> items;				// inventory
		int (*worry)(int);				// update worry level
		bool (*testItem)(int);			// test function
		int trueMonkey, falseMonkey;	// candidate target monkeys
		int targetMonkey;				// throw item to this monkey
	public:
		// TODO: Monkey constructors
		Monkey() = default;
		Monkey(vector<int> args) {
			for (auto i : args) {
				items.push(i);
			}
		}
		
		// given list of monkeys, inspect, worry, relief, test, and throw items
		// to necessary monkeys
		void routine(vector<Monkey> &monkeys) {
			// check for items
			if (items.empty()) {
				// skip turn if not holding items
				return;
			}
			
			// as long as monkey is holding items:
			while(!items.empty()) {
				// inspect next item
				int &item = items.front();
				inspect(item);
				
				item = relief(item);				// be relieved
				bool testResult = testItem(item);	// figure out which monkey to throw to
				if (testResult) {
					targetMonkey = trueMonkey;
				} else {
					targetMonkey = falseMonkey;
				}
				throwItem(item);						// throw item to target Monkey
			}
		}
		
		// inspect an item
		void inspect(int &item) {
			++inspections;
			item = worry(item);	// update worry level
		}
		
		// TODO: getTestItem();
		// TODO: getWorry();
		
		// throw current item to another monkey
		void throwItem(int item) {
			monkeys[targetMonkey].catchItem(item);
			items.pop();
		}
		
		// catch an item from another monkey
		void catchItem(int item) {
			items.push(item);
		}
		
		// return target monkey's number in line
		int getTarget() {
			return targetMonkey;
		}
};

int main(int argc, char *argv[]) {
	ifstream input(argv[1]);	// get input
	// test input
	if (input) {
		cout << "Got file: " << argv[1] << endl;
	} else {
		cerr << "Error: " << argv[1] << endl;
	}
	
	vector<Monkey> monkeys;
	
	// read monkeys one at a time
		// create monkey
		// give it attributes
			// vector of items
			// define worry function
			// define test function
			// define t/f monkeys
			
		// add monkey to vector
		
	// iterate through monkeys
		// inspect
		// worry function
		// relief
		// test
		// throw items
		
	vector<int> items {54, 65, 75, 74};
	
	Monkey m(items);

	return 0;
}

// after inspection, worry decreases
int relief(int worry) {
	return worry / RELIEF_LEVEL;
}