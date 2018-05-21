#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <queue>

using std::vector;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };
    bool debug = 0;

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n, bool debug_): graph(n), debug(debug_) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, capacity};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void print_edge(int index) {
       Edge &ef = edges[index];
       std::cout << "\tForward " << ef.from+1 << "=>" << ef.to+1 << "(" << ef.flow << ")\n";
       Edge &eb = edges[index ^ 1];
       std::cout << "\t\tBackward " << eb.from+1 << "=>" << eb.to+1 << "(" << eb.flow <<  ")\n";
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow -= flow;
        edges[id ^ 1].flow += flow;
    }



   void get_augmenting_path(int from, int to, std::vector<int> &path, int &min_cap) {
      std::map<int, int > nodeToEdge;
      std::queue<int> que;
      bool reached = false;

      que.push(from);

      while(!que.empty()) {
        int n = que.front();
        que.pop();

        for(int i = 0; i < graph[n].size(); i++) {
          int eIndex = graph[n][i];
          Edge &e = edges[eIndex];
          if(e.flow == 0) {
            continue;
          }

          if(nodeToEdge.find(e.to) != nodeToEdge.end()) {
            continue;
          }

          if(e.to == to) {
            path.push_back(eIndex);
            nodeToEdge[e.to] = eIndex;
            reached = true;
            break;
          } else {
            nodeToEdge[e.to] = eIndex;
            que.push(e.to);
          }
        }
        if(reached) {
          break;
        }
      }

      min_cap = 0;
      if(path.size()) {

         int edge_from = edges[path[0]].from;
         int edge_to = edges[path[0]].to;
         min_cap = edges[path[0]].flow;
   
         while (edge_from != from) {
           int eIndex = nodeToEdge[edge_from];
           Edge e = edges[eIndex];
           path.push_back(eIndex);
           edge_from = e.from;
           if(e.flow < min_cap) {
             min_cap = e.flow;
           }
         }
      }
      if(debug) {
         std::cout << "Shorttest path of length : " << path.size() << "\n";
         for (int i = 0; i < path.size(); i++) {
           print_edge(path[i]);
         }
         std::cout << "Min cap : " << min_cap << "\n";
      }
   }

bool augment_flow(std::vector<int> path, int min_path) {

   if(path.size() == 0) {
     return false;
   }
   for (int i = 0; i < path.size(); i++) {
      add_flow(path[i], min_path);
   }
   if(debug) {
      std::cout << "Augmented Path : " << path.size() << "\n";
      for (int i = 0; i < path.size(); i++) {
         print_edge(path[i]);
      }
   }
   return true;
}

int max_flow(int from, int to) {
    int flow = 0;
    bool augmented;
    do {
      std::vector<int> path;
      int min_cap;
      get_augmenting_path(from, to, path, min_cap);
      augmented = augment_flow(path, min_cap);
    } while (augmented);

    for(int i = 0; i < graph[from].size(); i++) {
        int eIndex = graph[from][i];
        if(eIndex%2 == 0) {
          Edge &e = edges[eIndex ^ 1];
          flow = flow + e.flow;
        }
    }
    return flow;
}
};

FlowGraph read_data(bool debug) {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count, debug);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

int max_flow(FlowGraph& graph, int from, int to) {
    return graph.max_flow(from, to);
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data(argc > 1 ? true : false );


    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
