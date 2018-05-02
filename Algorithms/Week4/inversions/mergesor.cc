#include <iostream>
#include <vector>





void
merge(std::vector<int> &a, int left, int middle, int right) {

  std::vector<int> d(right - left + 1);
  int l = left;
  int r = middle+1;
  int size = (right - left + 1);

  for(int i = 0; i < size; i++) {
    if(l > middle) {
      d[i] = a[r++];
    } else if (r > right) {
      d[i] = a[l++];
    } else if(a[r] > a[l]) {
      d[i] = a[l++];
    } else {
      d[i] = a[r++];
    }
  }
  for(int i = left, j = 0; i <= right; i++, j++) {
    a[i] = d[j];
  }

}

void
mergeSort(std::vector<int> &a, int left, int right)
{
  std::cout << "Sorting " << left <<  " " << right << "\n";
  if(left == right) {
    return;
  }
  int middle = left + (right - left)/2;
  mergeSort(a, left, middle);
  mergeSort(a, middle+1, right);
  std::cout << "Merging " << left << " " << middle << " " << right << "\n";
  merge(a, left, middle, right);
}










int main()
{
 int n;

 std::cin >> n;
 std::vector<int> nums(n);

 for(int i = 0; i < n; ++i) {
  std::cin >> nums[i] ;
 }
 
 mergeSort(nums,  0, n-1);

 for(int i = 0; i < n; ++i) {
  std::cout << nums[i] ;
 }
}
