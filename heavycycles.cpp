/*
 * UVA 11747 Heavy Cycle Edges
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2847
 * MST and cycles
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
vector<int> rank(1005);
vector<int> cycles;

void initSet(int n)
{
	int i;
	for(i = 0; i <= n; i++)
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
	int n, m, u, v, w, i;
	
	while(1)
	{
		scanf("%d %d", &n, &m);

		if(!n && !m) break;

		EdgeList.clear();

		while(m--)
		{
			scanf("%d %d %d", &u, &v, &w);
			EdgeList.push_back(make_pair(w, ii(u, v)));
		}

		// Kruska
		initSet(n);		
		sort(EdgeList.begin(), EdgeList.end());
		cycles.clear();
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
			else
				// If we have an edge that is forming a cycle (connecting the same set)
				// then it's a heavy cycle edge
				cycles.push_back(EdgeList[i].first);
		}

		if(cycles.size())
		{
			sort(cycles.begin(), cycles.end());
			for(i = 0; i < cycles.size(); i++)
			{
				if(i) printf(" ");
				printf("%d", cycles[i]);
			}
			printf("\n");
		}
		else
			printf("forest\n");
	}
	return 0;
}