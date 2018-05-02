#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using std::vector;

typedef std::pair<int, int> cost;

int optimal_sequence(int n, std::map<int, cost> &costs ) {

  for(int i = 2; i <= n; i++) {
    costs[i].first = costs[i - 1].first + 1;
    costs[i].second = 1;
    if(i%2 == 0) {
      if(costs[i/2].first + 1 < costs[i].first) {
        costs[i].second = 2;
      } 
      costs[i].first = std::min(costs[i/2].first + 1, costs[i].first);
    }
    if(i%3 == 0) {
      if(costs[i/3].first + 1 < costs[i].first) {
        costs[i].second = 3;
      } 
      costs[i].first = std::min(costs[i/3].first + 1, costs[i].first);
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  std::map<int, cost> costs;
  std::vector<int> seq;
  costs[0].first = 0;
  costs[1].first = 0;
  optimal_sequence(n, costs);
  std::cout << costs[n].first << std::endl;

  seq.push_back(n);
  for(int i = costs[n].first; i > 0 ; i--) {
    if(costs[n].second == 1) {
      n--;
    } else if (costs[n].second == 2) {
      n = n / 2;
    } else {
      n = n / 3;
    }
    seq.push_back(n);
  }

  for(int i = seq.size() - 1; i >=0 ; i --) {
    std::cout << seq[i] << ' ' ;
  }
  
//  for (std::map<int,cost>::iterator it=costs.begin(); it!=costs.end(); ++it) {
//    std::cout << it->first << " => " << it->second.first << '\n';
//  }
  std::cout << std::endl;
}
