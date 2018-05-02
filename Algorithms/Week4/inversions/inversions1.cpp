#include <iostream>
#include <vector>



void
merge(std::vector<int> &a, int left, int mid, int right, int &inversions) {

  std::vector<int> d(right - left + 1);
  int i = left;
  int j = mid;
  int k = 0;

  while ((i <= mid -1) && (j <= right)) {
    if(a[i] <= a[j]) {
      d[k++] = a[i++];
    } else {
      d[k++] = a[j++];
      inversions = inversions + (mid - i);
    }
  }

  while (i <= mid - 1) {
    d[k++] = a[i++];
  }

  while (j <= right) {
    d[k++] = a[i++];
  }

  for(int i = left, j = 0; i <= right; i++, j++) {
    a[i] = d[j];
  }
}

void
mergeSort(std::vector<int> &a, int left, int right, int &inversions)
{
  if(left == right) {
    return;
  }
  int middle =  (right + left)/2;
  mergeSort(a, left, middle, inversions);
  mergeSort(a, middle+1, right, inversions);
  merge(a, left, middle+1, right, inversions);
}


int main()
{
 int n;

 std::cin >> n;
 std::vector<int> nums(n);
 int inversions = 0;

 for(int i = 0; i < n; ++i) {
  std::cin >> nums[i] ;
 }
 
 mergeSort(nums,  0, n-1, inversions);

 for(int i = 0; i < n; ++i) {
  std::cout << nums[i] ;
 }
 std::cout << "\n";
 std::cout << inversions << std::endl;
}
