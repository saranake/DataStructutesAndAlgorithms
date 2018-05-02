#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
typedef vector<vector<int> > TwoDArr;

int optimal_weight(TwoDArr &mem, const vector<int> &w, int W) {
  int current_weight = 0;

  /* fill 0th column with zeros */
  
  for(int i = 0; i < w.size(); i++) {
    mem[i][0] = 0;
  }

  /* initialize 0th row */

  for(int i = 1; i <= W; i++) {
    if(i < w[0]) {
      mem[0][i] = 0;
    } else {
      mem[0][i] = w[0];
    }
  }

  /* Now fill rewst of the rows */
  for(int i = 1; i < w.size(); i++) {
    for(int j = 1; j <= W ; j++) {
      if(w[i] > j) {
        mem[i][j] = mem[i-1][j];
      } else {
        int resIndex = j - w[i];
        int resVal = mem[i-1][resIndex]; 
        if((resVal + w[i]) > mem[i-1][j]) {
          mem[i][j] = resVal + w[i];
        } else {
          mem[i][j] =  mem[i-1][j];
        }
      }
    }
  }
  return mem[w.size()-1][W];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  TwoDArr memMatrix;

  memMatrix.resize(n);
  for(int i = 0; i < n ; i ++) {
    memMatrix[i].resize(W + 1);
  }
  for(int i = 0; i < w.size(); i++) {
    for(int j = 0; j <= W; j++) {
      memMatrix[i][j] = 0;
    }
  }
  std::sort(w.begin(), w.end());
  std::cout << optimal_weight(memMatrix, w, W) << '\n';
}
