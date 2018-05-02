#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

typedef vector<vector<int> > memMatrix;

int min3(int a, int b , int c)
{

  if(a <= b) {
    if(a <= c) {
      return a;
    }
  } else if(b <= c) {
    return b;
  } else {
    return c;
  }
}

int edit_distance(const string &str1, const string &str2, memMatrix &mem) {

  int numRows = str1.length() + 1;
  int numCols = str2.length() + 1;

  // initialize elements of 0th column */
  for(int i = 0; i < numRows; i++) {
    mem[i][0] = i;
  }

  // initialize elements of 0th row */
  for(int j = 0; j < numCols; j++) {
    mem[0][j] = j;
  }


  for(int i = 1; i < numRows; i++) {
     for(int j = 1; j < numCols; j++) {

       // Copy
       if(str1[i-1] == str2[j-1]) {
         mem[i][j] = mem[i-1][j-1];
       } else { // delete/replace/insert
         mem[i][j] =  1 + min3(mem[i-1][j], mem[i-1][j-1], mem[i][j-1]);
       }

     }
  }
  return mem[numRows-1][numCols-1];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;

  memMatrix mem;

  mem.resize(str1.length() + 1);

  for(int i = 0; i < str1.length() + 1; i++) {
    mem[i].resize(str2.length() + 1);
  }

  std::cout << edit_distance(str1, str2, mem) << std::endl;
  return 0;
}
