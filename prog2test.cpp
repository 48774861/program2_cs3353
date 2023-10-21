#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "MyGraph.h"
using namespace std::chrono;



int main()
{
   ifstream ifile("../kruskal_worst_case.txt");
   int n, e;
   vector<float> satcost;

   ifile >> n >> e;

   vector<Link> l, l2;
   for (int i = 0; i < e; i++)
	{
	   Link s;
	   ifile >> s.v1 >> s.v2 >> s.w;
	   l.push_back(s);
	   l2.push_back(s);
	}
   int m;
   ifile >> m;
   vector<Link> test;
   for (int i = 0; i < m; i++)
	{
	   Link s;
	   ifile >> s.v1 >> s.v2 >> s.w;
	   test.push_back(s);
	}

   MyHelper helper;

   auto start1 = high_resolution_clock::now();
   vector<Link>  res1 = Task1(n, l, helper);
   auto end1 = high_resolution_clock::now();
   auto elapsed1 = duration_cast<microseconds>(end1 - start1);
   cout << "Time Duration of Task 1: " << elapsed1.count() << "\n";

   for (int i = 0; i < res1.size(); i++)
	{
	   cout << "(" << res1[i] << "),  ";
	}
   cout << "\n";

   for (int i = 0; i < m; i++)
	{
		auto start2 = high_resolution_clock::now();
   	   pair<bool, Link> res2 = Task2(n, l2, test[i], helper);
	   auto end2 = high_resolution_clock::now();
		auto elapsed2 = duration_cast<microseconds>(end2 - start2);

	   cout << "(" << test[i] << ") : ";
	   if (res2.first)
		{
		   cout << "replaced edge: " <<  "(" << res2.second << ") ";
		}
	   else
		{
		   cout << "not replaced";
		}
	  cout << endl;
	  cout << "Time Duration of Task 2: " << elapsed2.count() << "\n";
	}

}
