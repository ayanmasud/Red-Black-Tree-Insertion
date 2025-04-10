/* Red Black Tree Insertion: self-balancing binary tree which has red or black nodes
   Author: Ayan Masud
   Date: 4/10/2025
 */

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
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }

  // get parent
  btn* getParent() {
    return parent;
  }

  // set parent
  void setParent(btn* node) {
    parent = node;
  }

  // get color
  int getColor() {
    return color;
  }

  // set color
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
void cases(btn* &head, btn* node);
void rotateLeft(btn* &head, btn* node);
void rotateRight(btn* &head, btn* node);

int main() {
  // instructions
  cout << "'ADD' to add a number" << endl;
  cout << "'PRINT' to print the tree" << endl;
  cout << "'QUIT' to leave" << endl;

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
        cin.ignore();
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
    else if (strcmp(cmd, "QUIT") == 0) { // quit command
      break;
    }
  }

  return 0;
}

// add a node to the tree
void add(btn* &head, btn* current, btn* added) {
  if (head->getValue() == 0) { // empty
    added->setColor(0); // set the heads color to black
    head = added;
    return;
  }

  if (added->getValue() < current->getValue()) { // value is bigger so go right
    if (current->getLeft() == nullptr) {
      added->setColor(1); // set the new node to red
      added->setParent(current); // set parent value
      current->setLeft(added);
      cases(head, added); // check cases
    } 
    else {
      add(head, current->getLeft(), added); // recurse right
    }
  } 
  else if (added->getValue() > current->getValue()) { // value is less so go left
    if (current->getRight() == nullptr) {
      added->setColor(1); // set the new node to red
      added->setParent(current); // set parent value
      current->setRight(added);
      cases(head, added); // check cases
    } 
    else {
      add(head, current->getRight(), added); // recurse left
    }
  }
}

// print the red black tree
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

// p -> parent
// x -> node we are rotating on
// y -> child that will replace x at the top
// a, b, c -> the children

// rotate counterclockwise
void rotateLeft(btn* &head, btn* x) {
  btn* p = x->getParent();
  btn* y = x->getRight(); // new root of this subtree
  btn* b = y->getLeft();  // this subtree moves under x

  // Reconnect the parent
  if (p == nullptr) {
    head = y; // y becomes the new root
    y->setParent(nullptr);
  } 
  else {
    if (p->getLeft() == x) {
      p->setLeft(y);
    } 
    else {
      p->setRight(y);
    }
    y->setParent(p);
  }

  // Rebuild subtree
  y->setLeft(x);
  x->setParent(y);

  x->setRight(b);
  if (b != nullptr) {
    b->setParent(x);
  }
}

// rotate clockwise
void rotateRight(btn* &head, btn* x) {
  btn* p = x->getParent();
  btn* y = x->getLeft();   // new root of this subtree
  btn* b = y->getRight();  // this subtree moves under x

  // Reconnect the parent
  if (p == nullptr) {
    head = y; // y becomes the new root
    y->setParent(nullptr);
  } 
  else {
    if (p->getLeft() == x) {
      p->setLeft(y);
    } 
    else {
      p->setRight(y);
    }
    y->setParent(p);
  }

  // Rebuild subtree
  y->setRight(x);
  x->setParent(y);

  x->setLeft(b);
  if (b != nullptr) {
    b->setParent(x);
  }
}

// check the cases for individual nodes
void cases(btn* &head, btn* node) {
  // case 1: first node is root
  if (node->getParent() == nullptr) {
    node->setColor(0);
    head = node;
    return;
  }

  // case 2: parent is black, so do nothing
  if (node->getParent()->getColor() == 0) {
    return;
  }

  // make sure grandparent exists cause if it doesn't, no point in trying the next cases
  if (node->getParent()->getParent() == nullptr) {
    return;
  }

  // store the uncle to a variable
  btn* uncle = nullptr;
  if (node->getParent() == node->getParent()->getParent()->getLeft()) { // if nodes parent is the left of grandparent
    uncle = node->getParent()->getParent()->getRight(); // uncle is right of grandparent
  } else { // if nodes parent is the right of grandparent
    uncle = node->getParent()->getParent()->getLeft(); // uncle is left of grandparent
  }

  // case 3: parent and uncle are red
  if (uncle != nullptr && uncle->getColor() == 1) {
    node->getParent()->setColor(0);
    uncle->setColor(0);
    node->getParent()->getParent()->setColor(1);
    cases(head, node->getParent()->getParent()); // recursion on grandparent because the grandparent turning red might change things up
    return;
  }

  // case 4
  if (uncle == nullptr || uncle->getColor() == 0) { // uncle is black
    if (node->getParent() == node->getParent()->getParent()->getLeft()) { // parent is left of grandparent
      if (node == node->getParent()->getRight()) { // node is right child of parent
	rotateLeft(head, node->getParent()); // rotate to convert to line case
	node = node->getLeft(); // parent is now node
      }
      // case 5: node is left child of left parent
      node->getParent()->getParent()->setColor(1); // after rotation this makes sense
      rotateRight(head, node->getParent()->getParent());
    } 
    else { // parent is right of grandparent
      if (node == node->getParent()->getLeft()) { // node is left child of parent
	rotateRight(head, node->getParent());
	node = node->getRight(); // parent is now node
      }
      // case 5: node is right child of right parent
      node->getParent()->getParent()->setColor(1); // after rotation this makes sense
      rotateLeft(head, node->getParent()->getParent());
    }
  }

  node->getParent()->setColor(0); // ensure black parent after rotation
}
