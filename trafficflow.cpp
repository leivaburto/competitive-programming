/*
 * UVA 10842 Traffic Flow
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1783
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
vector<int> rank(105);

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
	int t, k, n, m, u, v, c, cont, i, last;
	
	scanf("%d", &t);

	for(k = 1; k <= t; k++)
	{
		scanf("%d %d", &n, &m);

		EdgeList.clear();

		while(m--)
		{
			scanf("%d %d %d", &u, &v, &c);
			// Insert opposite values (-d) in order to run Kruskal and get Max Spanning Tree 
			EdgeList.push_back(make_pair(-c, ii(u, v)));
		}

		// Kruskal
		initSet(n);		
		sort(EdgeList.begin(), EdgeList.end());
		cont = 0;
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
				cont++;
			}
			if(cont == n-1)
			{
				// The last edge added in a Max Spanning Tree is the min. capacity remaining road
				last = -EdgeList[i].first;
				break;
			}
		}

		printf("Case #%d: %d\n", k, last);
	}
	return 0;
}