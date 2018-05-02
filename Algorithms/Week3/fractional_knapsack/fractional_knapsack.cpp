#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>

using std::vector;
using std::array;

typedef std::pair<int, double> item_info_type;

bool sortByMerit(const item_info_type &lhs, const item_info_type &rhs)
{
  return (lhs.second > rhs.second);
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  int size = values.size();
  item_info_type *items = new item_info_type[size];

  for(int i = 0; i < size ; i++) {
    item_info_type item_info;
    item_info = std::make_pair(weights[i], (double) ((double)values[i]/(double) weights[i]));
    items[i] = item_info;
  }
  std::sort(items, items+size, sortByMerit);

  for (int i = 0; i < size; i++) {
    if(capacity == 0) {
      break;
    } else if(capacity >= items[i].first) { // Use up the entire item.
      capacity = capacity - items[i]. first;
      value += items[i].first * items[i].second;
    } else {
      value += capacity * items[i].second; // use up the partial item
      break;
    }
  }

//  for(int i = 0; i < size; i++) {
//    std::cout << "Weight : " << items[i].first << " Price per kg " << items[i].second << "\n"; 
//  }
  delete[] items;
  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
