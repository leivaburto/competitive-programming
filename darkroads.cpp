/*
 * UVA 11632 Dark Roads
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2678
 * MST
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
vector<int> rank(200005);

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
	int n, m, z, x, y, total, mst, cont, i;
	
	while(1)
	{
		scanf("%d %d", &m, &n);

		if(!m && !n) break;

		total = 0;
		EdgeList.clear();

		while(n--)
		{
			scanf("%d %d %d", &x, &y, &z);
			EdgeList.push_back(make_pair(z, ii(x, y)));
			// Save the original cost of all the roads
			total += z;
		}

		// Kruskal
		initSet(m);		
		sort(EdgeList.begin(), EdgeList.end());
		cont = 0;
		mst = 0;
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				mst += EdgeList[i].first;
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
				cont++;
			}
			if(cont == m-1)
				break;
		}

		// We've saved the difference between the original value and the min. value
		printf("%d\n", total-mst);
	}
	return 0;
}