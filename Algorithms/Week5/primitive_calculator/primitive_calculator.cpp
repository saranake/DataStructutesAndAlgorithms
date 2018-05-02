#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using std::vector;

typedef std::pair<int, int> cost;

int optimal_sequence(int n, std::map<int, cost> &costs ) {

  if(costs.find(n) != costs.end()) {
    return costs[n].first;
  }

  int nb2 = std::numeric_limits<int>::max();
  int nb3 = std::numeric_limits<int>::max();
  int nm1 = std::numeric_limits<int>::max();

  if(n % 2 == 0) {
    nb2 = optimal_sequence(n/2, costs) + 1;
  }
  if(n % 3 == 0) {
    nb3 = optimal_sequence(n/3, costs) + 1;
  }
  if(nb2 == std::numeric_limits<int>::max() ||  
     nb3 == std::numeric_limits<int>::max()) {
    nm1 = optimal_sequence(n - 1, costs) + 1;
  }

  if(nb2 <= nb3 && nb2 <= nm1) {
     costs[n].first = nb2;
     costs[n].second = 2;
  } else if (nb3 <= nb2 && nb3 <= nm1) {
     costs[n].first = nb3;
     costs[n].second = 3;
  } else {
     costs[n].first = nm1;
     costs[n].second = 1;
  }
  assert ((costs[n].first <= nb2) && (costs[n].first <= nb3) && 
          (costs[n].first <= nm1));
  assert(costs[n].first != std::numeric_limits<int>::max());
  return costs[n].first;
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
