#include <iostream>

int get_change(int m) {
  //write your code here
  int tens = m/10;
  int rem = m%10;
  int fives = rem/5;
  int ones = rem%5;

  return tens + fives + ones;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
