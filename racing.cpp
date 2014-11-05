/*
 * UVA 1234 Racing
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3675
 * Max Spanning Tree
 *
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> ii;

vector< pair<int, ii> > EdgeList;
vector<int> rank(10005);

void initSet(int n)
{
	int i;
	for(i = 1; i <= n; i++)
		rank[i] = i;
}

int findSet(int i)
{
	return (rank[i] == i) ? i : (rank[i] = findSet(rank[i]));
}

void unionSet(int i, int j)
{
	rank[findSet(i)] = findSet(j);
}

int isSameSet(int i, int j)
{
	return (findSet(i) == findSet(j));
}

int main()
{
	int c, n, m, w, i, j, total, cont;

	scanf("%d", &c);
	
	while(c--)
	{
		scanf("%d %d", &n, &m);

		total = 0;
		EdgeList.clear();

		while(m--)
		{
			scanf("%d %d %d", &i, &j, &w);
			// Insert opposite values (-w) in order to run Kruskal and get Max Spanning Tree 
			EdgeList.push_back(make_pair(-w, ii(i, j)));
			// Save the original cost of all the roads
			total += w;
		}

		// Kruskal
		initSet(n);		
		sort(EdgeList.begin(), EdgeList.end());
		cont = 0;
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				// Substract the value of the MST edges (the values are negative, so adding them will do it)
				total += EdgeList[i].first;
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
				cont++;
			}
			if(cont == n-1)
				break;
		}
		// The answer is the value of edges that are NOT in the Max Spanning Tree
		printf("%d\n", total);
	}
	return 0;
}