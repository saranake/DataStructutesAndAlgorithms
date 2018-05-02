#include <iostream>

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_fastt (int a, int b) {

  while ( !((a == 0) || (b == 0) || (a == 1) || (b == 1)) ) {
    int tempb;
    tempb = b;
    b = a;
    a = tempb%a; 
  }

  if((a == 1) || (b == 1)) {
    return 1;
  }

  if((a == 0) || (b == 0)) {
    return a + b;
  }
}

int main() {
  int a, b;
  int gcd_fast;
  std::cin >> a >> b;
  gcd_fast = gcd_fastt(a, b);
  std::cout << gcd_fast << std::endl;
  return 0;
}
