#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    int height;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
      height = -1;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  int r;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0) {
      nodes[child_index].setParent(&nodes[parent_index]);
    } else {
      r = child_index;
    }
    nodes[child_index].key = child_index;
  }

  std::queue<Node *> nodeQ;

  nodeQ.push(&nodes[r]);
  nodes[r].height = 1;

  int maxHeight = 0;
  Node *p ;
  while(!nodeQ.empty()) {
    p = nodeQ.front();
    nodeQ.pop();
    for(std::vector<Node *>::iterator it = p->children.begin(); it != p->children.end(); it++) {
      Node *c = *it;
      c->height = p->height+1;
      nodeQ.push(c);
    }
  }

  std::cout << p->height << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
