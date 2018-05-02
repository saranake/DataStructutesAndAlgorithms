#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTreeInt(const vector<Node>& tree, int i, bool *first, int *num, bool *problem) {
  if(*problem) {
    return false;
  }
  const Node &n = tree[i];
  if(n.left != -1 ) {
    int l = n.left;
    IsBinarySearchTreeInt(tree, l, first, num, problem );
  }
  int key = n.key;
  if(*first) {
    *first = false;
  } else {
    if(*num > key) {
      *problem = true;
    }
  }
  *num = key;
  if(n.right != -1 ) {
    int r = n.right;
    IsBinarySearchTreeInt(tree, r, first, num, problem);
  }
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  bool first = true;
  bool problem = false;
  int num = 0;
  IsBinarySearchTreeInt(tree, 0, &first, &num, &problem);
  return !problem;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if ((tree.size() == 0) || IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
