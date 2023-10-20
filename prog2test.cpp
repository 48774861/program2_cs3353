#include <iostream>
#include <fstream>
#include <vector>
#include "MyGraph.h"



int main()
{
   ifstream ifile("../test2_1.txt");
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

   vector<Link>  res1 = Task1(n, l, helper);

   for (int i = 0; i < res1.size(); i++)
	{
	   cout << "(" << res1[i] << "),  ";
	}
   cout << "\n";

   for (int i = 0; i < m; i++)
	{
   	   pair<bool, Link> res2 = Task2(n, l2, test[i], helper);
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
	}

}
