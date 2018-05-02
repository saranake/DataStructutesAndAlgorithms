#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

#define LEFT(i)  (2 * i + 1)
#define RIGHT(i)  (LEFT(i) + 1)

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;
  int size_;

  void PushDown(int i) {
    int minIndex = i;
    
    int left = LEFT(i);
    if((left < size_) && data_[minIndex] > data_[left]) {
      minIndex = left;
    } 
    int right = RIGHT(i);
    if((right < size_) && data_[minIndex] > data_[right]) {
      minIndex = right;
    } 
    if(minIndex == i) {
      return;
    } else {
      /* swaps_.push_back(make_pair(data_[i], data_[minIndex])); */
      swaps_.push_back(make_pair(i, minIndex));
      int t = data_[minIndex];
      data_[minIndex] = data_[i];
      data_[i] = t;
      PushDown(minIndex);
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    for(int i = size_/2; i >= 0; i--) {
      PushDown(i);
    }

  }

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    size_ = n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
