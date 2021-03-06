#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include <cmath>

using namespace std;
bool debug = true;

typedef vector<vector<double>> matrix;

void printTableau(matrix &tableau, int numRows, int numColumns) {
  if(!debug) {
    return;
  }

   cout << "-------------------------------------\n";
   for(int i = 0; i < numRows; i++) {
     for(int j = 0; j < numColumns; j++) {
        // printf("% -10.1f", tableau[i][j]);
        printf("%-5.1f ", tableau[i][j]);
     }
     cout << "\n";
   }
}

bool DOUBLE_EQ(double a, double b)
{
    return abs(a - b)  <  std::numeric_limits<double>::epsilon(); 
}

bool DOUBLE_EQZ(double a)
{
    // bool z =  abs(a) <= (std::numeric_limits<double>::epsilon() * abs(a));
    // return z;
    return (fpclassify(a) == FP_ZERO);
}

bool DOUBLE_LT(double a, double b)
{
    return (b - a)  >  std::numeric_limits<double>::epsilon(); 
}

bool DOUBLE_GT(double a, double b)
{
    return (a - b)  >  std::numeric_limits<double>::epsilon(); 
}

int getPivotColumn(vector<double> &c, int numVars) {
  int min = std::numeric_limits<int>::max();
  int i;
  int pivotColumn = -1;

  for(i = 0; i < numVars; i++) {
    if(DOUBLE_GT(c[i], 0) || DOUBLE_EQZ(c[i])) {
      continue;
    }
    if(DOUBLE_LT(c[i],  min)) {
      pivotColumn = i;
      min = c[i];
    }
  }
  return pivotColumn;
}

int getPivotRow(matrix &tablue, int pivotColumn, int numEquations, int bColumn ) {

  double min_r = std::numeric_limits<double>::max();
  int pivotRow = -1;
  for(int i = 0; i < numEquations; i++) {
  
    double p = tablue[i][pivotColumn];
    if(DOUBLE_GT(p, 0)) {
      double r = tablue[i][bColumn]/p;
      if(DOUBLE_LT(r, min_r)) {
        min_r = r;
        pivotRow = i;
      }
    }
  }
  return pivotRow;
}



bool isUnbounded(matrix &tablue, int pivotColumn, int numEquations) {

  bool unbounded = true;
  for(int i = 0; i < numEquations; i++) {
    double p = tablue[i][pivotColumn];
    if(DOUBLE_GT(p, 0)) {
      unbounded = false;
      break;
    }
  }
  return unbounded;
}

bool isFinalTableau(vector<double> c, int numVariables) {
  bool final = true;

  for(int i = 0; i < numVariables; i++) {
    if(DOUBLE_LT(c[i], 0)) {
      final = false;
      break;
    }
  }
  return final;
}

void
pivot(matrix &tableau, int pivotColumn, int pivotRow, int numRows, int numColumns)
{
  double p = tableau[pivotRow][pivotColumn];

  for(int i = 0; i < numColumns; i++) {
    tableau[pivotRow][i] = tableau[pivotRow][i] / p;
  }

  for(int j = 0; j < numRows; j++) {
    if(j == pivotRow) {
      continue;
    }
    double e = tableau[j][pivotColumn];
    for(int i = 0; i < numColumns; i++) {
      tableau[j][i] = tableau[j][i] +
                      (-e * tableau[pivotRow][i]) ;
    }
  }
}


bool
getSolution(matrix &tableau, int numEqns, int numVars, int bColumn, vector<double> &solution)
{

  for(int i = 0; i < numEqns; i++) {
   if(DOUBLE_LT(tableau[i][bColumn],0)) {
      return false;
    } 
  }

  for(int j = 0; j < numVars; j++) {
    int numOnes = 0;
    int onePos = -1;
    for(int i = 0; i < numEqns; i++) {
      if(DOUBLE_EQZ(tableau[i][j]) || DOUBLE_EQ(tableau[i][j], 1)) {
        if(DOUBLE_EQ(tableau[i][j], 1)) {
          numOnes++;
          onePos = i;
          if(numOnes > 1) {
            break;
          }
        }
      } else {
        numOnes = -1;
        break;
      }
    }
    if(numOnes == 1) {
      solution[j] = tableau[onePos][bColumn];
    }
  }
  return true;
}

bool negativeEntriesInBColumn(matrix &tableau, int bColumn, int numEq) {
  for(int i = 0; i < numEq; i++) {
    if(DOUBLE_EQZ(tableau[i][bColumn])) {
      continue;
    }
    if(DOUBLE_LT(tableau[i][bColumn], 0.0)) {
      return true;
    } 
  }
  return false;
}

int rowWithMostNegativeEntry(matrix &tableau, int bColumn, int numEq) {
  
  int row = -1;
  for(int i = 0; i < numEq; i++) {
    if(DOUBLE_EQZ(tableau[i][bColumn])) {
      continue;
    }
    if(DOUBLE_LT(tableau[i][bColumn], 0.0)) {
      if((row == -1) ||
         DOUBLE_LT(tableau[i][bColumn], tableau[row][bColumn])) {
        row = i;
      }
    } 
  }
  printf("Row with most -ve entry = %d row, val = %f\n", row, tableau[row][bColumn]);
  return row;
}


bool allEntriesInPivotRowNonNegative(matrix &tableau, int pivotRow, int numColumns)
{
  for(int i = 0; i < numColumns; i++) {
    if(DOUBLE_EQZ(tableau[pivotRow][i])) {
      continue;
    }
    if(DOUBLE_LT(tableau[pivotRow][i], 0)) {
      return false;
    } 
  }
  return true;
}

int getPivotColumnGT(matrix &tableau, int pivotRow, double bval, int numColumns) {

  double max_r = std::numeric_limits<double>::min();
  int pivotCol = -1;
  for(int i = 0; i < numColumns; i++) {
  
    double p = tableau[pivotRow][i];
    if(DOUBLE_EQZ(p)) {
      continue;
    }
    if(DOUBLE_LT(p, 0)) {
      double r = bval/p;
      if(DOUBLE_GT(r, max_r)) {
        max_r = r;
        pivotCol = i;
      }
    }
  }
  return pivotCol;
}


pair<int, vector<double>> allocate_ads(
    int n, /* number of inequalities */
    int m, /* number of variables */
    matrix A, 
    vector<double> b, 
    vector<double> c) {

  /* Determine the number of rows and columns of a tableau */
  int numColumns = m /* number of variables */ +
                   n /* number of slack variables, one for each constraints */ +
                   1; /* for b value */
  int numRows = n /* number of inequalities */ +
                1; /* cost vector */
  matrix tableau(numRows, vector<double>(numColumns));

  /* construct initial tableau */

  for(int i = 0; i < numRows - 1; i++) {
    /* Fill A matrix */
    for(int j = 0; j < m; j++) {
      tableau[i][j] = A[i][j];
    }
    /* Add slack matrix */
    for(int j = m; j < numColumns - 1; j++) {
      if(j == m + i) {
        tableau[i][j] = 1;
      } else {
        tableau[i][j] = 0;
      }
    }
    /* Add b entry */
    tableau[i][numColumns-1] = b[i];
  }

  for(int j = 0; j < numColumns; j++) {
    if(j < m) {
      tableau[numRows - 1][j] = -c[j];
     } else {
      tableau[numRows - 1][j] = 0;
     }
  }

  /* Are there constraints of the form >= */
  while (negativeEntriesInBColumn(tableau, numColumns -1, n)) { 
    printTableau(tableau, numRows, numColumns);
    int pivotRow = rowWithMostNegativeEntry(tableau, numColumns -1, n);
    if(debug) {
      printf("Pivot Row : %d\n", pivotRow);
    }
    if(allEntriesInPivotRowNonNegative(tableau, pivotRow, numColumns -1)) {
       printTableau(tableau, numRows, numColumns);
       return {-1, vector<double>(m, 0)};
    }
    int pivotColumn = getPivotColumnGT(tableau, pivotRow, tableau[pivotRow][numColumns-1], numColumns -1);
    if(debug) {
      printf("Most -ve B : %f\n", tableau[pivotRow][numColumns-1]);
      printf("Pivot Column : %d\n", pivotColumn);
    }
    pivot(tableau, pivotColumn, pivotRow, numRows, numColumns);
  };

  if(debug) {
    printf("Staring phase II\n");
  }
  
  bool unbounded = false;
  do {

    printTableau(tableau, numRows, numColumns);
    bool final = isFinalTableau(tableau[numRows - 1], numColumns - 1);
    if(debug) {
      printf("Is Final : %s\n", final ? "true": "false");
    }
    if(final) {
      break;
    }

    int pivotColumn = getPivotColumn(tableau[numRows - 1], numColumns - 1);
    if(debug) {
      printf("Pivot Column : %d\n", pivotColumn);
    }

    unbounded = isUnbounded(tableau, pivotColumn, numRows - 1);
    if(debug) {
      printf("Is Unbounded : %s\n", unbounded ? "true": "false");
    }
    if(unbounded) {
      printTableau(tableau, numRows, numColumns);
      break;
    }

    int pivotRow = getPivotRow(tableau, pivotColumn, n, numColumns-1);
    if(debug) {
      printf("Pivot Row : %d\n", pivotRow);
    }

    pivot(tableau, pivotColumn, pivotRow, numRows, numColumns);
  } while (true);

  if(unbounded) {
   return {1, vector<double>(m, 0)};
  }

  vector<double> solution(m, 0);
  
  bool feseable = getSolution(tableau, n, m, numColumns -1, solution);
  if(feseable) {
    return {0, solution};
  }

  return {-1, vector<double>(m, 0)};
}

int main(){
  int n, m;
  cin >> n >> m;
  matrix A(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<double>> ans = allocate_ads(n, m, A, b, c);

  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;      
  }
  return 0;
}
