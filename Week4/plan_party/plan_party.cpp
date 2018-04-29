#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <assert.h>

#include <sys/resource.h>


struct Vertex {
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;

Graph ReadTree() {
    int vertices_count;
    std::cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        std::cin >> tree[i].weight;

    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

int getRoot(const Graph &gr)
{
  if (gr.size() == 1) {
    return 0;
  }
  for(int i = 0; i < gr.size(); i++) {
    if(gr[i].children.size() == 1) {
      return i;
    }
  }
  assert(true);
  std::cout << "Something terrible happened\n";
  return 0;
}

bool 
isLeaf(const Vertex &v, int parent) {
  if((v.children.size() == 1) && (v.children[0] == parent)) {
    return true;
  } else {
    return false;
  }
}

long long dfs(const Graph &tree, int vertex, int parent, std::vector<long long> &D) {
    if(D[vertex] == std::numeric_limits<long long>::max()) {
      if(isLeaf(tree[vertex], parent)) {
        D[vertex] = tree[vertex].weight;
      } else {
        long long D0 = 0;
        for (int child : tree[vertex].children) {
          if (child != parent) {
            D0 = D0 + dfs(tree, child, vertex, D);
          }
        }
        long long D1 = tree[vertex].weight;
        for (int child : tree[vertex].children) {
          if (child != parent) {
            for (int grandchild : tree[child].children) {
              if (grandchild != vertex) {
                D1 = D1 + dfs(tree, grandchild, child, D);
              }
            }
          }
        }
        D[vertex] =  std::max(D0, D1);
     }
   }
   return D[vertex];
}

long long MaxWeightIndependentTreeSubset(const Graph &tree) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
    if(size == 1) {
      return tree[0].weight;
    }
    int root = getRoot(tree);
    std::vector<long long> D(size, std::numeric_limits<long long>::max());
    int funF = dfs(tree, root, -1, D);
    return funF;
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
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
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

    // Here begins the solution
    Graph tree = ReadTree();
    long long weight = MaxWeightIndependentTreeSubset(tree);
    std::cout << weight << std::endl;
    return 0;
}
