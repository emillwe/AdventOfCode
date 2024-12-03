#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

class File;
class Directory;
class Browser;

const int MAX_SIZE = 100000;
const int DISK_SPACE = 70000000;
const int MIN_SPACE = 30000000;

// class to represent a named file with size (kB)
class File {
	private:
		string name;
		unsigned size;
		
	public:
		File() = default;
		File(string str): name(str) { }
		File(unsigned i): size(i) {}
		File(unsigned i, string str): name(str), size(i) { }
		
		string getName() {
			return name;
		}
		
		unsigned getSize() {
			return size;
		}
		
		void setName(string str) {
			name = str;
		}
		
		void setSize(unsigned s) {
			size = s;
		}
};

// class to represent a named directory with files and subdirectories
class Directory {
	private:
		Directory *parent;				// enclosing directory
		string name;					// this directory's name
		unsigned size;					// size of files (indirect and direct)
		map<string, File> files;		// all files in this directory
		map<string, Directory> subs;	// all subdirectories in this directory
	public:
		// constructors
		Directory() = default;
		Directory(string str): name(str) { }
		Directory(string str, Directory *p): name(str), parent(p) { }
		
		// getter functions
		string getName() {
			return name;
		}
		
		unsigned getSize() {
			return size;
		}
		
		Directory *getParent() {
			return parent;
		}

		// setter functions
		void setName(string str) {
			name = str;
		}
		
		// recursively get size of file
		void setSize() {
			unsigned resultSize = 0;
			
			// add size of files in this directory
			for (auto &p : files) {
				File f = p.second;
				resultSize += f.getSize();
			}
			
			// add size of files in contained directories
			for (auto &p : subs) {
				Directory &d = p.second;
				d.setSize();
				resultSize += d.getSize();
			}
			size = resultSize;
// 			cout << "name: " << this->getName() << " size: "
// 				<< this->getSize() << endl;
		}
		
		void setSize(unsigned i) {
			size = i;
		}
		
		void setParent(Directory *d) {
			parent = d;
		}
	
		
		// functions to add elements to this directory
		void putFile(File &f) {
			files[f.getName()] = f;
		}
		
		void putFile(unsigned i, string str) {
			File f(i, str);
			files[f.getName()] = f;
		}
		
		void putDir(Directory &d) {
			subs[d.getName()] = d;
		}
		
		void putDir(string str) {
			Directory d(str);
			subs[d.getName()] = d;
		}
		
		// print functions
		ostream& printFiles(ostream &os) {
			for (auto p : files) {
				os << p.first << " ";
			}
			
			return os;
		}
		
		ostream& printSubs(ostream &os) {
			for (auto p : subs) {
				os << p.first << " ";
			}
			
			return os;
		}
		
		// recursively search this directory and all its
		// subdirectories, summing any directory sizes
		// greater than MAX_SIZE
		unsigned searchSize() {
			int result = 0;
// 			cout << "name: " << this->getName() << " size: "
// 				<< this->getSize() << endl;
			if (this->getSize() <= MAX_SIZE) {
// 				cout << "adding " << this->getName() << endl;
				result += this->getSize();
			}
			for (auto &p : subs) {
				Directory &d = p.second;
				result += d.searchSize();
			}
			return result;
		}
		
		// friends
		friend Browser;
};

// TODO: Build tree
// class to navigate a directory tree
class Browser {
	private:
		Directory *root;
		Directory *curr;
		vector<unsigned> sizes;		// sizes of directories
	public:
		Browser() = default;
		Browser(Directory& d): curr(&d) { }
		
		// get root directory
		Directory *getRoot() {
			return root;
		}
		
		// get current directory
		Directory *getCurr() {
			return curr;
		}
		
		// set root directory
		void setRoot(Directory &r) {
			root = &r;
		}
		
		// list all in working directory
		ostream& ls(ostream &os) {
			os << "Subdirectories: ";
			curr->printSubs(os);
			os << endl;
			os << "Files: ";
			curr->printFiles(os);
			
			return os;
		}
		
		// print info about current directory
		ostream& pwd(ostream &os) {
			os << "Name: " << this->getCurr()->getName()
			<< " Size: " << this->getCurr()->getSize() << endl;
			
			return os;
		}
		
		// change directory
		void cd(string str) {
			// special cases: .. and /
			if (str == "..") {
				curr = curr->getParent();
				return;
			}
			else if (str == "/") {
				// new root directory
				static Directory d(str, NULL);
				// we are in this directory
				curr = &d;
				this->setRoot(d);
				return;
			}
			
			Directory &next = curr->subs[str];
			curr = &next;
		}
		
		// recursively search for oversized directories
		unsigned findOversized() {
			// analyze file sizes
			root->setSize();

			// search from root
			return root->searchSize();
		}
		
		// recursively search for directory sizes
		// from given directory
		void addMems(Directory *d) {	
// 			cout << "Searching " << d->getName() << endl;	
			if (d->getSize() >= this->memToUpdate()) {
				sizes.push_back(d->getSize());
			}
			
			// recursively scan subdirectories
			for (auto &p : d->subs) {
				Directory &d2 = p.second;
				addMems(&d2);
			}
		}
		
		// get amout of memory available
		// NB: Must call setSize() on root first!
		unsigned freeMemory() {
			// analyze file sizes
			
			return DISK_SPACE - root->getSize();	
		}
		
		// get amount of memory needed to update
		unsigned memToUpdate() {
			return MIN_SPACE - freeMemory();
		}
		
		unsigned minToDelete() {
			sort(sizes.begin(), sizes.end());
			return sizes[0];
		}
		
		ostream &printSizes(ostream &os) {
			for (auto elem : sizes) {
				os << elem << endl;
			}
			return os;
		}
};

// TODO: flesh these out
void processInput(Browser &, string);

int main(int argc, char *argv[]) {
	ifstream input(argv[1]);
	if (input) {
		cout << "Got file: " << argv[1] << endl;
	} else {
		cout << "Error reading file: " << argv[1] << endl;
	}
	
	// new terminal browser
	Browser b;
	
	// read terminal log
	string buffer;
	int lineNum = 1;
	while(getline(input, buffer)) {
// 		cout << "Line: " << lineNum << endl;
		processInput(b, buffer);
		++lineNum;
	}
	
	b.getRoot()->setSize();
	b.addMems(b.getRoot());
	cout << b.minToDelete() << endl;
// 	b.printSizes(cout);
	
	return 0;
}

// TODO: logic branch is too complicated: use map in directory instead?
void processInput(Browser &b, string str) {
	istringstream line(str);
	
	string first;		// e.g. $ or file size
	string command;		// e.g. cd, ls
	string name;		// file or directory name
	
	// read "$", "dir", or file size
	line >> first;
	
	// figure out what to do
	if (first == "$") {
		line >> command;	// read command
		if (command == "ls") {
			return;		// nothing else to do here
		}
		else if (command == "cd") {
			// get new directory name
			line >> name;
			// change directory
			b.cd(name);
// 			cout << "Now in: " << b.getCurr()->getName() << endl;
		} else { // did not recognize command
			cerr << "Error: " << command << " is invalid command" << endl;
		}
	}
	else if (first == "dir") {
		// get directory name
		line >> name;
		// make new directory in current directory
		Directory d(name, b.getCurr());
		b.getCurr()->putDir(d);
	} else { // saw a file size
		// get file name
		line >> name;
		// make file
		unsigned size = stoi(first);
		File f(size, name);
		// put file in current directory
		b.getCurr()->putFile(f);
	}	
}