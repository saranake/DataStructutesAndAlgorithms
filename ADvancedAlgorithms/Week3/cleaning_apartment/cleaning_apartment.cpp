#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

struct Edge {
    int from;
    int to;
};


struct ConvertHampathToSat {
    int numVertices;
    vector<Edge> edges;
    vector<vector<int>> adjList;
    bool debug = false;

    ConvertHampathToSat(int n, int m) :
        numVertices(n),
        edges(m),
        adjList(n+1, vector<int>(1))
    {  }

    bool adj(int n1, int n2) {
     for(int i = 0; i < adjList[n1].size(); i++) {
       if(adjList[n1][i] == n2) {
         if(debug) {
           std::cout << n1 << " and " << n2 << " are adjacent\n";
         }
         return true;
       }
     }
     return false;
    }

    int getVar(int pos, int n) {
      return numVertices * (pos - 1) + n;
    }

    std::string getVar(bool asString, int pos, int n) {
      char var[100];
      if(asString) {
        snprintf(var, 100, "%d => X[%d,%d]", getVar(pos, n), pos, n); 
        std::string str = var ;
        return str;
      } else {
        snprintf(var, 100, "%d", getVar(pos, n)); 
        std::string str = var ;
        return str;
      }
    }

    /* number of clauses = numVertices */
    void eachVertexBelongsToPath() {
      for(int i = 1 ; i <= numVertices; i++) {
        for(int pos = 1 ; pos <= numVertices; pos++) {
          std::cout << getVar(debug, pos, i) << " ";
        }
        std::cout << "0\n";
      }
      if(debug) {
        std::cout << "End Rule 1\n";
      }
    }

    /* number of clauses = numVertices * (numVertices * (numVertices -1)) / 2; */
    void noNodeAppearsTwiceOnThePath() {
      for(int i = 1; i <= numVertices; i++) {
       for(int pos1 = 1; pos1 < numVertices; pos1++) {
         for(int pos2 = pos1+1; pos2 <= numVertices; pos2++)
           std::cout << "-" << getVar(debug, pos1, i) << " -" << getVar(debug, pos2, i) << " 0\n";
         }
      }
      if(debug) {
        std::cout << "End Rule 2\n";
      }
    }

    /* number of clauses = numVertices */
    void eachPositionOnThePathIsOccupied() {
      for(int pos = 1 ; pos <= numVertices ; pos++) {
        for(int i = 1; i <= numVertices; i++) {
          if(i <= (numVertices-1)) {
            std::cout << getVar(debug, pos, i) << " ";
          } else {
            std::cout << getVar(debug, pos, i) << " 0\n";
          }
        }
      }
      if(debug) {
        std::cout << "End Rule 3\n";
      }
    }

    /* number of clauses = numVertices * (numVertices * (numVertices -1)) / 2; */
    void noTwoNodesCanOccupySamePosition() {
      for(int pos = 1; pos <= numVertices; pos++) {
        for(int i = 1; i < numVertices; i++) {
          for(int j = i+1; j <= numVertices; j++) {
            if(i != j) {
              std::cout << "-" << getVar(debug, pos, i) << " -" << getVar(debug, pos, j) << " 0\n";
            }
          }
        }
      }
      if(debug) {
        std::cout << "End Rule 4\n";
      }
    }

    /* number of clauses = computeClausesOonlyAllowSuccessiveVerticesConnectedByEdge() */
    void onlyAllowSuccessiveVerticesConnectedByEdge() {
      for(int pos = 1; pos < numVertices; pos++) {
        for(int i = 1; i < numVertices; i++) {
           for(int j = i + 1; j <= numVertices; j++) {
             if(!adj(i, j)) {
                std::cout << "-" << getVar(debug, pos, i) << " -" << getVar(debug, pos+1, j) << " 0\n";
                std::cout << "-" << getVar(debug, pos, j) << " -" << getVar(debug, pos+1, i) << " 0\n";
             }
           }
        }
      }
      if(debug) {
        std::cout << "End Rule 5\n";
      }
    }

    int computeClausesOnlyAllowSuccessiveVerticesConnectedByEdge() {
      int clauses = 0;
      for(int i = 1; i < numVertices; i++) {
         for(int j = 1 + i; j <= numVertices; j++) {
           if(!adj(i, j)) {
              clauses += 2;
           }
         }
      }
      return clauses * (numVertices - 1);
    }

    int numClauses() {
      int rule1 =  numVertices;
      int rule2 = numVertices * (numVertices * (numVertices -1)) / 2;
      int rule3 = rule1;
      int rule4 = rule2;
      int rule5 = computeClausesOnlyAllowSuccessiveVerticesConnectedByEdge();
      
  //    std::cout << "rule1 = rule3 = " << rule1 << " rule2 == rule4 = " << rule2;
   //   std::cout << " rule5 = " << rule5 << "\n";
      return rule1 + rule2 + rule3 + rule4 + rule5; 
    }

    void printEquisatisfiableSatFormula() {
        for(int i = 0; i < edges.size(); i++) {
          int to = edges[i].to;
          int from = edges[i].from;
          adjList[to].push_back(from);
          adjList[from].push_back(to);
        }
        if(debug) {
          cout << "p cnf " << numVertices*numVertices << " " << numClauses() << endl;
         } else {
          cout << numClauses() << " " << numVertices*numVertices << endl;
         }
        eachVertexBelongsToPath();
        noNodeAppearsTwiceOnThePath();
        eachPositionOnThePathIsOccupied();
        noTwoNodesCanOccupySamePosition();
        onlyAllowSuccessiveVerticesConnectedByEdge();

        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
        // cout << "3 2" << endl;
        // cout << "1 2 0" << endl;
        // cout << "-1 -2 0" << endl;
        // cout << "1 -2 0" << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
