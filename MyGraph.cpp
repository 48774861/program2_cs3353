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
bool MyGraph::addEdge(const Link& link)
{
   if(link.v1 <= 0 || link.v1 > numberOfVertices || link.v2 <= 0 || link.v2 > numberOfVertices) {
      return false;
   }
   if(adjacency_list.at(link.v1).find(link.v2) == adjacency_list.at(link.v1).end()) {
      adjacency_list.at(link.v1).insert(std::make_pair(link.v2, link));
      adjacency_list.at(link.v2).insert(std::make_pair(link.v1, link));
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
            os << "\n" << v1 << " " << edge.first << " " << edge.second.w;
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

vector<Link> MyGraph::Kruskal(vector<Link>& pipes)
{
   // Sorts the edges in from least to greatest weight.
   std::sort(pipes.begin(), pipes.end());

   vector<int> parent; // Vector showing the parent of each point.
   vector<int> num(numberOfVertices + 1, 0); // Vector holding the heights of each root's tree.
   for(int i = 0; i < numberOfVertices + 1; i++) {
      parent.push_back(i);
   }

   std::vector<Link> finalMinimumSpanningTree;
   int i = 0;
   while(finalMinimumSpanningTree.size() < numberOfVertices - 1) {
      const Link& min_edge = pipes.at(i);

      // Find the root of the tree that each vertex of the minimum edge.
      int root_v1 = findset(min_edge.v1, parent);
      int root_v2 = findset(min_edge.v2, parent);

      // If the roots are different (i.e. the vertices are in different trees),
      // Add the minimum edge to the minimum spanning tree and merge the trees together.
      if (root_v1 != root_v2) {
         finalMinimumSpanningTree.push_back(min_edge);
         addEdge(min_edge);
         // Merge Trees is here.
         if (num.at(root_v1) > num.at(root_v2)) {
            parent.at(root_v2) = root_v1;
            num.at(root_v1) += num.at(root_v2);
         } else { // If num.at(root_v1) < num.at(root_v2)
            parent.at(root_v1) = root_v2;
            num.at(root_v2) += num.at(root_v1);
         }
      }
      
      i++;
   }

   return finalMinimumSpanningTree;
}
int MyGraph::findset(int i, vector<int>& parent)
{
   // Find the root which is when a parent of a point is itself.
   int root = i;
   while (root != parent.at(root)) {
      root = parent.at(root);
   }
   // Make each of the points in the path point to the parent.
   int j = parent.at(i);
   while (j != root) {
      parent.at(i) = root;
      i = j;
      j = parent.at(i);
   }
   return root;
}

MyHelper::MyHelper()
{
}
void MyHelper::output_graph() {
   graph.output(std::cout);
}

vector<Link> Task1(int n, vector<Link>& pipes, MyHelper& helper)
{
   helper.graph = MyGraph(n);
   return helper.graph.Kruskal(pipes); // Builds helper.graph as the Minimum Spanning Tree using Kruskal's Algorithm.
}

pair<bool, Link> Task2(int n, vector<Link>& pipes, Link newPipe, MyHelper helper)
{
   // Find the only path between the two points in new Pipe in the current MST.
   // Gets the edge with the highest weight on that path.
   const Link& l1 = helper.copygraph->findHighestWeightOnPath(newPipe.v1, newPipe.v2);
   // If you find a link with greater weight than the new Pipe, you should add the new Pipe.
   // If not, you should not add the new Pipe.
   return (l1.w > newPipe.w) ? std::make_pair(true, l1) : std::make_pair(false, Link());
}

// Depth First Search Algorithm that finds the path between two points in the graph (assuming it is a MST) and returns the edge of the highest weight in that path.
const Link& MyGraph::DFS(int v, const int& dest_v, vector<bool>& visited) const {

   visited.at(v) = true;

   // Examine each edge starting from the current vertex we are at and going to an unvisited vertex.
   for(auto i = adjacency_list.at(v).begin(); i != adjacency_list.at(v).end(); i++) {

      // If there current edge we are examining goes to the our Final Destination Vertex, 
      // return the weight of that edge.
      if(i->first == dest_v) {
         return i->second;
      }

      if(!visited.at(i->first)) {
         const Link& highest_weight_yet = DFS(i->first, dest_v, visited); // Continues along the current path.
         
         // If the current edge is on our intended path, the highest_weight_yet will have the highest weight we have found on the path to the final destination.
         // If so, return the current edge's weight if it is higher than the heighest weight we have found.
         if(highest_weight_yet.v1 != -1)
            return (highest_weight_yet.w > i->second.w) ? highest_weight_yet : i->second;
      }
   }
   return empty; // We have reached the end of the current path, so return a Link with v1 = -1.
}

const Link& MyGraph::findHighestWeightOnPath(int a, int b) const {
   vector<bool> visited(numberOfVertices + 1, false); // Vector that tracks whether a point has been visited or not.
   return DFS(a, b, visited);
}
