#include <iostream>
#include <vector>



void
merge(std::vector<long long> &a, long long left, long long mid, long long right, long long &inversions) {

  std::vector<long long> d(right - left + 1);
  long long i = left;
  long long j = mid;
  long long k = 0;

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
    d[k++] = a[j++];
  }

  for(long long i = left, j = 0; i <= right; i++, j++) {
    a[i] = d[j];
  }
}

void
mergeSort(std::vector<long long> &a, long long left, long long right, long long &inversions)
{
  if(right > left) {
   long long middle =  (right + left)/2;
   mergeSort(a, left, middle, inversions);
   mergeSort(a, middle+1, right, inversions);
   merge(a, left, middle+1, right, inversions);
  }
}


int main()
{
 long long n;

 std::cin >> n;
 std::vector<long long> nums(n);
 long long inversions = 0;

 for(long long i = 0; i < n; ++i) {
  std::cin >> nums[i] ;
 }
 
 mergeSort(nums,  0, n-1, inversions);

 std::cout << inversions << std::endl;
}
