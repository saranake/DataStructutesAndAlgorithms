#include <iostream>
#include <vector>
#include <math.h>

using std::vector;

vector<int> optimal_summands(int n) {
  
  vector<int> summands;

  int l = 1;
  int m = n;

  while (m > 2 * l) {
   summands. push_back(l);
   m = m - l;
   l = l + 1;
  }
  summands.push_back(m);
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
