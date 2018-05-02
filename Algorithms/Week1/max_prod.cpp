#include <iostream>
#include <vector>


long long
maxPairWiseProduct(int n, const std::vector<int> &nums)
{
  int maxIndex = 0;
  int max = -1;
  int nextMax = -1;

  max = nums[maxIndex];
  for(int i = 1; i < n; i++) {
    if(nums[i] > max) {
      max = nums[i];
      maxIndex = i;
    }
  }

  for(int i = 0; i < n; i++) {
    if(i == maxIndex) {
      continue;
    }
    if(nums[i] > nextMax) {
      nextMax = nums[i];
    }
  }
  return ((long long) (max) * (long) (long) nextMax);
}

int
main() {
  long long maxPairProd;
  int size;
  std::cin >> size;
  std::vector<int> numbers(size);
  for (int i ; i < size; i++) {
    std::cin >> numbers[i]; 
  }
  maxPairProd = maxPairWiseProduct(size, numbers);
  std::cout << maxPairProd << "\n";
  return 0;
}
