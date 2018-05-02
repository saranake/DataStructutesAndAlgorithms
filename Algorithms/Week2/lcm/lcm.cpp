#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}


long long lcm_fast (int a, int b) {

  long long prod = (long long) a * (long long) b;
  while ( !((a == 0) || (b == 0) || (a == 1) || (b == 1)) ) {
    int tempb;
    tempb = b;
    b = a;
    a = tempb%a;
  }

  if((a == 1) || (b == 1)) {
    return prod ;
  }

  if((a == 0) || (b == 0)) {
    return prod / ((long long) a + (long long) b);
  }
}


int main() {
  int a, b;
  std::cin >> a >> b;
//  std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
