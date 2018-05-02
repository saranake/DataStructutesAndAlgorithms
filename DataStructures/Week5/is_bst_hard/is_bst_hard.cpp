#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  public:
  long long key;
  int left;
  int right;
  long long min;
  long long max;

  Node() : key(0), left(-1), right(-1), min(0), max(0) {}
  Node(long long key_, int left_, int right_, long long min_, long long max_) : key(key_), left(left_), right(right_), min(min_), max(max_) {}
};

bool IsBinarySearchTreeInt(vector<Node>& tree, int i, bool *problem) {

  if(i == -1) {
    return true;
  }
  Node &n = tree[i];
  if((n.key > n.max) || (n.key < n.min)) {
    *problem = true;
  }
  if(*problem) {
    return false;
  }
  int l = n.left;
  int r = n.right;

  if(l != -1) {
    Node &left = tree[l];
    left.max = n.key -1;
    left.min = n.min;
  }

  if(r != -1) {
    Node &right = tree[r];
    right.max = n.max;
    right.min = n.key;
  }
  IsBinarySearchTreeInt(tree, l,  problem);
  IsBinarySearchTreeInt(tree, r, problem);
}

bool IsBinarySearchTree(vector<Node>& tree) {
  bool problem = false;
  tree[0].min = std::numeric_limits<long long>::min();
  tree[0].max = std::numeric_limits<long long>::max();
  IsBinarySearchTreeInt(tree, 0, &problem);
  return !problem;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    long long key;
    int left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right, std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max() ));
  }
  if ((tree.size() == 0) || IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
