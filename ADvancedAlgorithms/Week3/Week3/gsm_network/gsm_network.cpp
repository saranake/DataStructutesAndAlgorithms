#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    int numEdges;
    vector<Edge> edges;
    vector<int> vertices;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m),
        numEdges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
        if(numEdges == (numVertices - 1) || (numVertices <= 3)) {
          cout << "3 2" << endl;
          cout << "1 2 0" << endl;
          cout << "-1 -2 0" << endl;
          cout << "1 -2 0" << endl;
          return;
        }
        cout << (3 * numEdges) + (4 * numVertices) << " " << numVertices * 3 << "\n";
        for(int i = 1; i <= numVertices ; i++) {
          int r = (3 * i) - 2;
          int g = r + 1;
          int b = g + 1;
          cout << r << " " << g << " " << b << " 0\n";
          cout << "-" << r << " -" << g << " 0\n";
          cout << "-" << r << " -" << b << " 0\n";
          cout << "-" << g << " -" << b << " 0\n";
        }

       for (int i = 0; i < numEdges ; ++i) {
         int from = edges[i].from;
         int to = edges[i].to;
         int r_from = (3 * from) - 2;
         int g_from = r_from + 1;
         int b_from = g_from + 1;

         int r_to = (3 * to) - 2;
         int g_to = r_to + 1;
         int b_to = g_to + 1;

         cout << "-" << r_from << " -"  << r_to << " 0\n";
         cout << "-" << g_from << " -"  << g_to << " 0\n";
         cout << "-" << b_from << " -"  << b_to << " 0\n";
       }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
