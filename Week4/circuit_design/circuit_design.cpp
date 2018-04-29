#include <bits/stdc++.h>
using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <set>
#include <algorithm>



void reverseGraph(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &rGraph)
{
  for(int i = 0; i < graph.size(); i++) {
    std::vector<int> &adj = graph[i];
    for(int j = 0; j < adj.size(); j++) {
     int node = adj[j];
     std::vector<int> &rAdj  = rGraph[node];
     rAdj.push_back(i);
    }
  }
}

void dfs(std::vector<std::vector<int>> &graph, int node, 
         std::vector<std::pair<int, int>> &finishTimes, int &time, std::set<int> &visited) {

   if(visited.find(node) != visited.end()) {
     return;
   }
   visited.insert(node);
   time++;
   // std::vector<int> &adj = graph[node];
   for(int i = 0; i < graph[node].size(); i++) {
     int child = graph[node][i];
     dfs(graph, child, finishTimes, time, visited);
   }
   finishTimes.push_back(std::make_pair(time++, node));
}

void
extractSccAtNode(std::vector<std::vector<int>> &graph, int node,
                 std::set<int> &visited, std::vector<int> &scc)
{
  if(visited.find(node) != visited.end()) {
    return;
  }
  visited.insert(node);
  scc.push_back(node);
  for(int i = 0; i <graph[node].size(); i++) {
    int child = graph[node][i];
    extractSccAtNode(graph, child, visited, scc);
  }
}

#if 0

void printGraph(std::vector<std::vector<int>> &graph)
{
  for(int i = 0; i < graph.size() ; i++) {
    std::cout << i << " ";
    std::vector<int> &adj = graph[i];
    for(int j = 0; j < adj.size(); j++) {
      std::cout << adj[j] << " ";
    }
   std::cout << "\n";
  }
}

void printFinishTimes(std::vector<std::pair<int, int>> &finishTimes) {
{
  std::cout << "Finish Times\n";
  for(int i = 0; i < finishTimes.size(); i++)
    std::cout << finishTimes[i].second << " " << finishTimes[i].first << std::endl;
  }
}
#endif

void printScc(std::vector<std::vector<int>> &scc)
{
  std::cout << "Total numbers of SCCS = " << scc.size() << "\n";
  for(int i = 0; i < scc.size(); i++) {
    for(int j = 0; j < scc[i].size(); j++) {
      std::cout << scc[i][j] << " ";
    }
    std::cout << "\n";
  }
}

bool checkSat(std::vector<std::vector<int>> &scc)
{
  for(int i = 0; i < scc.size(); i++) {
    for(int j = 0; j < scc[i].size() -1; j++) {
      int lit = scc[i][j];
      if(lit & 0x1) {
        continue; 
      }
      if(scc[i][j+1] == lit + 1) {
        return false;
      }
    }
  }
  return true;
}

void getAssignments(std::vector<std::vector<int>> &scc,
     std::vector<int> &assignments)
{
  std::set<int> added;
  for(int i = scc.size() - 1;  i >= 0; i --) {
    for(int j = 0; j < scc[i].size(); j++) {
      int node = scc[i][j] / 2;
      if(added.find(node) != added.end()) {
        continue;
      }
      added.insert(node);
      if(scc[i][j] & 0x1 ) {
        assignments[node] = 0;
      } else {
        assignments[node] = 1;
      }
    }
  }
}


void getScc(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &scc)
{
  std::vector<std::pair<int, int>> finishTimes;
  std::set<int> visited;
  int time = 0;

  struct compareByFTimes {
   bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b)
   {
    return (a.first >= b.first);
   }
  };   
  compareByFTimes c;


  for(int i = 0; i < graph.size(); i++) {
    if(visited.find(i) != visited.end()) {
      continue;
    }
    dfs(graph, i, finishTimes, time, visited);
  }

  std::sort (finishTimes.begin(), finishTimes.end(), c);  
#if 0
  printFinishTimes(finishTimes);
#endif

  std::vector<std::vector<int>> rGraph(graph.size(), std::vector<int>());
  reverseGraph(graph, rGraph);
#if 0
  std::cout << "Reversed Graph\n";
  printGraph(rGraph);
#endif

  visited.erase(visited.begin(), visited.end());

  int sccNum = 0;
  for(int i = 0; i < finishTimes.size(); i++) {
    int node = finishTimes[i].second;
    if(visited.find(node) == visited.end()) {
      extractSccAtNode(rGraph, node, visited, scc[sccNum]);
      std::sort (scc[sccNum].begin(), scc[sccNum].end());  
      sccNum++;
    }
  }
  scc.resize(sccNum);
#if 0
  printScc(scc);
#endif
}



int getNodeNum(int var) {
  if(var < 0) {
    return (-2 * var) - 1;
  } else {
    return (2 * var) - 2;
  }
}

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    if(n == 0) {
      std::cout << "UNSATISFIABLE\n";
      return 0;
    }
    std::vector<std::vector<int>> graph(2 * n, std::vector<int>());
    for (int i = 0; i < m; ++i) {
        int firstVar, secondVar;
        cin >> firstVar >> secondVar;
        
        int n1 = getNodeNum(-firstVar);
        int n2 = getNodeNum(secondVar);
        std::vector<int> &adjList = graph[n1];
        adjList.push_back(n2);

        int n3 = getNodeNum(-secondVar);
        int n4 = getNodeNum(firstVar);

        std::vector<int> &adjList1 = graph[n3];
        adjList1.push_back(n4);
    }
#if 0
    std::cout << "Graph\n";
    printGraph(graph);
#endif
    std::vector<std::vector<int>> scc(n*2, std::vector<int>());
    getScc(graph, scc);
    if(checkSat(scc)) {
      std::cout << "SATISFIABLE\n";
      std::vector<int> assignments(n);
      getAssignments(scc, assignments);
      for(int i = 0; i < n; i++) {
        if(assignments[i]) {
          std::cout << i+1 << " ";
        } else {
          std::cout << -(i+1) << " ";
        }
      }

      std::cout << "\n";
    } else {
      std::cout << "UNSATISFIABLE\n";
    }
    return 0;
}
