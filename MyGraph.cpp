#include <iostream>
#include "MyGraph.h"


ostream& operator<<(ostream& os, const Link& l)
{
   os << l.v1 << " " << l.v2 << " " << l.w;
   return os;
}

MyGraph::MyGraph()
{
   numberOfVertices = 0;
   numberOfEdges = 0;
}

MyGraph::MyGraph(int n)
{
   adjacency_list.resize(n + 1);
   numberOfVertices = n;
   numberOfEdges = 0;
}

MyGraph::MyGraph(const MyGraph& graph2)
{
   this->adjacency_list = graph2.adjacency_list;
   this->numberOfVertices = graph2.numberOfVertices;
   this->numberOfEdges = graph2.numberOfEdges;
}

// Forms the graph from a file.  Assumes there are no repeat edges in the file or edges that point to themselves.
MyGraph::MyGraph(string&& fileName)
{
   // Executes in the build file, so you need to go one layer out.
   ifstream ifile("../" + fileName);
   if(!ifile.is_open()) {
      throw std::invalid_argument("File cannot be opened!");
   }
   // Resets the input file to the beginning.
   ifile.clear();
   ifile.seekg(0, std::ios::beg);

   int n, e;
   ifile >> n >> e;

   adjacency_list.resize(n + 1);
   numberOfVertices = n;
   numberOfEdges = e;

   int v1, v2;
   double weight;
   for (int i = 0; i < e; i++) {
	   ifile >> v1 >> v2 >> weight;
      adjacency_list.at(v1).insert(std::make_pair(v2, weight));
      adjacency_list.at(v2).insert(std::make_pair(v1, weight));
	}
   ifile.close();
}

// Adds an edge if it is not already found in the adjacency list.  Still can add edges that point to themselves.
// Checks for if the vertices are out of range.
bool MyGraph::addEdge(int a, int b, float w)
{
   if(!(a < 0 || a > adjacency_list.size() || adjacency_list.at(a).find(b) == adjacency_list.at(a).end())) {
      adjacency_list.at(a).insert(std::make_pair(b, w));
      adjacency_list.at(b).insert(std::make_pair(a, w));
      numberOfEdges++;
      return true;
   }
   return false;
}

void MyGraph::output(ostream& os)
{
   if(adjacency_list.size() <= 0) {
      throw std::invalid_argument("Adjacency List is Empty!");
   }
   // It works with a Time Complexity of O(2e) because it goes through the edges twice.
   // Must get the number of vertices from the variable because actual size of vector is +1 because vertices start numbering from 0.
   os << numberOfVertices;

   for(int v1 = 0; v1 < adjacency_list.size(); v1++) {
      // Prints all edges with the smaller vertex before the larger vertex.
      for(auto& edge : adjacency_list.at(v1)) {
         if(edge.first > v1) {
            os << "\n" << v1 << " " << edge.first << " " << edge.second;
         }
      }
   }

}

// Gets the weight for an edge from a to b.
// Returns false if at least one vertex is out of bounds or if there is not an edge with those vertices.
pair<bool, float> MyGraph::weight(int a, int b)
{
   if((a < 0) || a > adjacency_list.size() || adjacency_list.at(a).find(b) == adjacency_list.at(a).end()) {
      return std::make_pair(false, -69420);
   }
   return std::make_pair(true, adjacency_list.at(a).at(b));
}

MyHelper::MyHelper()
{
}

vector<Link> Task1(int n, vector<Link>& pipes, MyHelper& helper)
{
   vector<Link> res = pipes;
   return res;
}

pair<bool, Link> Task2(int n, vector<Link>& pipes, Link newPipe, MyHelper helper)
{
  Link l1;
  pair<bool, Link> sol;
  sol.first = true;
  sol.second = newPipe;
  return sol;
}
