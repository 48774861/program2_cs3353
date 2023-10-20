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

// Forms the graph from a file.  Assumes there are no repeat edges in the file.
MyGraph::MyGraph(vector<Link>& pipes, int n)
{
   adjacency_list.resize(n + 1);
   numberOfVertices = n;
   numberOfEdges = pipes.size();

   for (auto& pipe : pipes) {
      adjacency_list.at(pipe.v1).insert(std::make_pair(pipe.v2, pipe));
      adjacency_list.at(pipe.v2).insert(std::make_pair(pipe.v1, pipe));
	}
}

// Adds an edge if it is not already found in the adjacency list.
// Checks for if the vertices are out of range.
bool MyGraph::addEdge(int a, int b, float w)
{
   if(a <= 0 || a > numberOfVertices || b <= 0 || b > numberOfVertices) {
      return false;
   }
   if(adjacency_list.at(a).find(b) == adjacency_list.at(a).end()) {
      Link link(a, b, w);
      adjacency_list.at(a).insert(std::make_pair(b, link));
      adjacency_list.at(b).insert(std::make_pair(a, link));
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

   for(int v1 = 0; v1 < int(adjacency_list.size()); v1++) {
      // Prints all edges with the smaller vertex before the larger vertex.
      for(auto& edge : adjacency_list.at(v1)) {
         if(edge.first > v1) {
            os << "\n" << edge.second;
         }
      }
   }

}

// Gets the weight for an edge from a to b.
// Returns false if at least one vertex is out of bounds or if there is not an edge with those vertices.
pair<bool, float> MyGraph::weight(int a, int b)
{
   if(a <= 0 || a > numberOfVertices || b <= 0 || b > numberOfVertices) {
      return std::make_pair(false, -69420);
   }
   if(adjacency_list.at(a).find(b) == adjacency_list.at(a).end()) {
      return std::make_pair(false, -69420);
   }
   return std::make_pair(true, adjacency_list.at(a).at(b).w);
}

vector<Link> MyGraph::Kruschal(vector<Link>& pipes)
{
   // priority_queue<Link> ordered_edges;
   // for(auto& element : pipes) {
   //    ordered_edges.insert(element);
   // }

   // vector<int> parent;
   // vector<int> num(n + 1, 0);
   // for(int i = 0; i < n + 1; i++) {
   //    parent.push_back(i);
   // }

   // //helper.graph is the minimum spanning tree.
   // std::vector<Link> finalMinimumSpanningTree;
   // helper.graph = MyGraph(n + 1);
   // while(finalMinimumSpanningTree.size() < n - 1) {
   //    Link& min_edge = ordered_edges.top();

   //    ordered_edges.pop();
   // }

   // return ordered_edges;
   return pipes;
}

MyHelper::MyHelper()
{
}
void MyHelper::output_graph() {
   graph->output(std::cout);
}

vector<Link> Task1(int n, vector<Link>& pipes, MyHelper& helper)
{
   //MyGraph graph(pipes, n);
   //helper.buildGraph(pipes, n);
   MyGraph minimum_spanning_tree(n);
   return minimum_spanning_tree.Kruschal(pipes);

}

pair<bool, Link> Task2(int n, vector<Link>& pipes, Link newPipe, MyHelper helper) //Make MyHelper pass by value later!
{
   // Properly tested for the given input file (Change helper.graph to the minimum spanning tree later).
   Link& l1 = helper.graph->findHighestWeightOnPath(newPipe.v1, newPipe.v2);
   pair<bool, Link> sol;
   if (l1.w > newPipe.w) {
      sol.first = true;
      sol.second = l1;
   } else {
      sol.first = false;
   }
   return sol;
}

Link& MyGraph::DFS(int v, const int& dest_v, vector<bool>& visited) {
   visited.at(v) = true;
   for(auto i = adjacency_list.at(v).begin(); i != adjacency_list.at(v).end(); i++) {
      if(i->first == dest_v) {
         return i->second;
      }
      if(!visited.at(i->first)) {
         Link& highest_weight_yet = DFS(i->first, dest_v, visited);
         if(highest_weight_yet.v1 != -1)
            return (highest_weight_yet.w > i->second.w) ? highest_weight_yet : i->second;
      }
   }
   return empty;
}

Link& MyGraph::findHighestWeightOnPath(int a, int b) {
   vector<bool> visited(numberOfVertices + 1, false);
   return DFS(a, b, visited);
}
