#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#include <string>
#include <stdexcept>

using namespace std;

struct Link {

public:
   int v1, v2;
   float w;
   Link() {
      v1 = -1;
      v2 = -1;
      w = -1;
   };
   Link(int v1, int v2, float w) {
      this->v1 = v1;
      this->v2 = v2;
      this->w = w;
   };
   Link(const Link& other) {
      v1 = other.v1;
      v2 = other.v2;
      w = other.w;
   };
   bool operator<(const Link& link2) const {
      return (w < link2.w);
   }
   bool operator>(const Link& link2) const {
      return (w > link2.w);
   }
};

ostream& operator<<(ostream&, const Link&);

class MyGraph {
private:
   Link empty; // Default Invalid Link.
   int numberOfVertices;
   int numberOfEdges;
public:
   vector< unordered_map<int, Link> > adjacency_list;
   MyGraph();
   MyGraph(int n);
   MyGraph(const MyGraph&);
   MyGraph(vector<Link>&, int n);

   bool addEdge(int a, int b, float w);
   bool addEdge(const Link& link);
   void output(ostream& os);
   pair<bool, float> weight(int a, int b);

   const Link& findHighestWeightOnPath(int a, int b) const;
   const Link& DFS(int v, const int& dest_v, vector<bool>& visited) const;

   vector<Link> Kruschal(vector<Link>& pipes);
   int findset(int i, vector<int>& parent);

   vector<Link> Prim(vector<Link>& pipes);
};

class MyHelper {
public:
   MyGraph graph;
   const MyGraph* copygraph;
   MyHelper();
   MyHelper(const MyHelper& other) {
      copygraph = &other.graph;
      //graph = other.graph;
   }
   void output_graph();
};

vector<Link> Task1(int n, vector<Link>& pipes, MyHelper& helper);
pair<bool, Link> Task2(int n, vector<Link>& pipes, Link newPipe, MyHelper helper);
