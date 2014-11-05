/*
 * UVA 1216 The Bug Sensor Problem
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3657
 * Min Spanning Forest
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

vector< pair<double, ii> > EdgeList;
int rank[10005];

int sensors[10005][2], numSets;

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
	int w, receivers, x, y, i, j, cont;
	double d, last;
	
	scanf("%d", &w);

	while(w--)
	{
		scanf("%d", &receivers);

		cont = 0;
		while(1)
		{
			scanf("%d", &x);
			if(x != -1)
			{
				scanf("%d", &y);
				sensors[cont][0] = x;
				sensors[cont][1] = y;
				cont++;
			}
			else
				break;
		}

		EdgeList.clear();

		// Connect all the sensors with proper edges
		for(i = 0; i < cont; i++)
		{
			for(j = i+1; j < cont; j++)
			{
				d = hypot((double)sensors[i][0]-sensors[j][0], (double)sensors[i][1]-sensors[j][1]);
				EdgeList.push_back(make_pair(d, ii(i, j)));
			}
		}

		// Kruskal until we reach the desired numbers of components (one component for each receiver)
		initSet(cont);		
		sort(EdgeList.begin(), EdgeList.end());
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
				if(numDisjointSets() == receivers)
				{
					last = EdgeList[i].first;
					break;
				}
			}
		}
		printf("%d\n", (int)ceil(last));
	}
	return 0;
}