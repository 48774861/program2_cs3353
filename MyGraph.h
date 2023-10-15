#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdexcept>

using namespace std;

struct Link {

public:

   int v1, v2;
   float w;
};

ostream& operator<<(ostream&, const Link&);

class MyGraph {
private:
   vector< unordered_map<int, double> > adjacency_list;
   int numberOfVertices;
   int numberOfEdges;
public:
   MyGraph();
   MyGraph(int n);
   MyGraph(const MyGraph&);
   MyGraph(string&&);

   bool addEdge(int a, int b, float w);
   void output(ostream& os);
   pair<bool, float> weight(int a, int b);


};

class MyHelper {

public:
    MyHelper();
    int x;
};

vector<Link> Task1(int n, vector<Link>& pipes, MyHelper& helper);
pair<bool, Link> Task2(int n, vector<Link>& pipes, Link newPipe, MyHelper helper);
