#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool compare(string n1, string n2) {

  if(n1 == n2) {
    return true;
  }

  int l1 = n1.length();
  int l2 = n2.length();
  int i1, i2;
  
  for(i1 = 0 , i2 = 0; (i1 < l1) && (i2 < l2); i1++, i2++) {
    if(n1[i1] > n2[i2]) {
      return true;
    } else if( n2[i2] > n1[i1]) {
      return false;
    }
  }

  if(i1 == l1) {
    return true;
  } else if (i2 == l2) {
    return false;
  }
  return true;
}

string largest_number(vector<string> a) {
  //write your code here
  std::sort(a.begin(), a.end(),  compare);
  std::stringstream ret;
  for (size_t i = 0; i < a.size(); i++) {
    ret << a[i];
  }
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
    std::cout << a[i];
  }
  std::cout << "\n";
  std::cout << largest_number(a);
}
