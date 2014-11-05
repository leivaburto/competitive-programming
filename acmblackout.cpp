/*
 * UVA 10600 ACM Contest and blackout
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1541
 * Second best MST
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

vector< pair<int, ii> > EdgeList, FlaggedEdges;
vector<int> rank(305);

int numSets;

void initSet(int n)
{
	int i;
	for(i = 0; i <= n; i++)
		rank[i] = i;
	numSets = n;
}

int findSet(int i)
{
	return (rank[i] == i) ? i : (rank[i] = findSet(rank[i]));
}

int isSameSet(int i, int j)
{
	return (findSet(i) == findSet(j));
}

void unionSet(int i, int j)
{
	if(!isSameSet(i, j)) numSets--;
	rank[findSet(i)] = findSet(j);
}

int numDisjointSets()
{
	return numSets;
}

int main()
{
	int t, n, m, a, b, c, mst, best, second, cont, i, j;
	bool possible;
	
	scanf("%d", &t);

	while(t--)
	{
		scanf("%d %d", &n, &m);

		EdgeList.clear();
		FlaggedEdges.clear();

		// If we have n-1 edges, we don't have much choice
		(m == n-1) ? possible = 0: possible = 1;

		while(m--)
		{
			scanf("%d %d %d", &a, &b, &c);
			EdgeList.push_back(make_pair(c, ii(a, b)));
		}

		// Kruskal
		initSet(n);		
		sort(EdgeList.begin(), EdgeList.end());
		cont = mst = 0;
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				cont++;
				mst += EdgeList[i].first;
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
				// Save all the edges that we are adding to MST
				FlaggedEdges.push_back(make_pair(EdgeList[i].first, ii(EdgeList[i].second.first, EdgeList[i].second.second)));
			}
			if(cont == n-1)	break;
		}

		best = second = mst;

		if(possible)
		{
			// For every vertex in the MST (saved in FlaggedEdges), consider it as flagged and run Kruskal again
			// without the flagged vertex
			for(j = 0; j < FlaggedEdges.size(); j++)
			{
				initSet(n);
				cont = mst = 0;
				for(i = 0; i < EdgeList.size(); i++)
				{
					if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
					{
						if(EdgeList[i].second.first != FlaggedEdges[j].second.first || EdgeList[i].second.second != FlaggedEdges[j].second.second)
						{
							cont++;
							mst += EdgeList[i].first;
							unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
						}
					}
					if(cont == n-1)	break;
				}
				// After flagging a vertex we might end up with a forest. Do NOT consider that value
				if(numDisjointSets() == 1)
				{
					if(!j) second = mst;
					second = min(second, mst);
				}
			}
		}

		printf("%d %d\n", best, second);
	}
	return 0;
}