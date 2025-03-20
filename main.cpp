#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>

// define color codes
#define RESET   "\033[0m"
#define WHITE   "\033[37m"
#define RED     "\033[31m"

using namespace std;

class btn { // binary tree node class
public:
  int value;
  int color; // 0 -> black, 1 -> red
  btn* left;
  btn* right;
  btn* parent;

  // constructor requires setting its value
  btn(int val) {
    value = val;
    left = nullptr;
    right = nullptr;
    color = 0;
    parent = nullptr;
  }

  // destructor
  ~btn() {

  }

  btn* getParent() {
    return parent;
  }

  void setParent(btn* node) {
    parent = node;
  }

  int getColor() {
    return color;
  }

  void setColor(int newColor) {
    color = newColor;
  }

  // set left child
  void setLeft(btn* node) {
    left = node;
  }

  // set right child
  void setRight(btn* node) {
    right = node;
  }

  // get left
  btn* getLeft() {
    return left;
  }

  // get the right child
  btn* getRight() {
    return right;
  }

  // get the char value
  int getValue() {
    return value;
  }
};

// prototypes
void add(btn* &head, btn* current, btn* added);
void print(btn* current, int depth);
void cases(btn* current);

int main() {
  btn* head = new btn(0); // head of the tree
  
  while (true) {
    char cmd[8];
    cin.getline(cmd, 8);
    
    if (strcmp(cmd, "ADD") == 0) { // add command
      cout << "through file (f) or manually (m)? ";
      char fm[2];
      cin.getline(fm, 2);
      if (strcmp(fm, "m") == 0) { // manually add numbers to the tree
	int num;
	cout << "add num: ";
	cin >> num;
	btn* added = new btn(num);
	add(head, head, added);
      }
      else if (strcmp(fm, "f") == 0) { // add through file
	// prepare the tree using file
	ifstream file("nums.txt");
	if (file.is_open()) {
	  string line;
	  while (getline(file, line)) {
	    stringstream ss(line);
	    string word;
	    while (ss >> word) { // string stream helps with the splitting by spaces
	      int num = stoi(word); // convert the string to int
	      btn* added = new btn(num);
	      add(head, head, added);
	    }
	  }
	  file.close();
	} else { // files not there
	  cout << "Unable to open file";
	}
      }
    }
    else if (strcmp(cmd, "PRINT") == 0) { // print command
      print(head, 0);
    }
  }

  return 0;
}

void add(btn* &head, btn* current, btn* added) {
  if (head->getValue() == 0) { // empty
    added->setColor(0); // set the heads color to black
    head = added;
    return;
  }

  if (current->getValue() < added->getValue()) { // value is bigger so go right
    if (current->getRight() == nullptr) {
      added->setColor(1); // set the new node to red
      added->setParent(current); // set parent value
      current->setRight(added);
      cases(added);
      return;
    }
    add(head, current->getRight(), added); // recurse right
  }
  
  if (current->getValue() > added->getValue()) { // value is less so go left
    if (current->getLeft() == nullptr) {
      added->setColor(1); // set the new node to red
      added->setParent(current); // set parent value
      current->setLeft(added);
      cases(added);
      return;
    }
    add(head, current->getLeft(), added); // recurse left
  }
}

void print(btn* current, int depth) {
  if (current == nullptr || current->getValue() == 0) { // stop
    return;
  }
  print(current->getRight(), depth + 1); // sideways tree so print rights
  for (int i = 0; i < depth; i++) { // add spaces based off the depth
    cout << "  ";
  }

  // print the value
  if (current->getColor() == 0) { // black node
    cout << WHITE << current->getValue() << RESET << endl;
  }
  else { // red node
    cout << RED << current->getValue() << RESET << endl;
  }
  print(current->getLeft(), depth + 1); // then print lefts
}

void cases(btn* current) {
  if (current->getParent()->getParent() != nullptr) {
    // ase 3
    if (current->getColor() == 1 && current->getParent()->getParent()->getColor() == 0 && current->getParent()->getParent()->getLeft()->getColor() == 1 && current->getParent()->getParent()->getRight()->getColor() == 1) { // node is red, parent is red, uncle is red, grandparent is black
      current->getParent()->getParent()->getLeft()->setColor(0);
      current->getParent()->getParent()->getRight()->setColor(0);
      current->getParent()->getParent()->setColor(1);
    }
  }
}
