#include <iostream>
#include "MyGraph.h"


ostream& operator<<(ostream& os, const Link& l)
{
   os << l.v1 << " " << l.v2 << " " << l.w;
   return os;
}

MyGraph::MyGraph()
{

}

MyGraph::MyGraph(const MyGraph&)
{

}

bool MyGraph::addEdge(int a, int b, float w)
{
   return true;
}

void MyGraph::output(ostream& os)
{
}

pair<bool, float> MyGraph::weight(int a, int b)
{
   pair<bool, float> res;
   return res;

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
