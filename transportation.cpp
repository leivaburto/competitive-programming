/*
 * UVA 11228 Transportation system
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2169
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

vector< pair<double, ii> > EdgeList;
vector<int> rank(1005);

int cities[1005][2];

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
	int t, n, i, j, k, cont;
	double d, r, roads, railroads;
	
	scanf("%d", &t);

	for(k = 1; k <= t; k++)
	{
		scanf("%d %lf", &n, &r);

		for(i = 0; i < n; i++)
			scanf("%d %d", &cities[i][0], &cities[i][1]);

		EdgeList.clear();
		// Connect all the cities with proper edges
		for(i = 0; i < n; i++)
		{
			for(j = i+1; j < n; j++)
			{
				d = hypot((double)cities[i][0]-cities[j][0], (double)cities[i][1]-cities[j][1]);
				EdgeList.push_back(make_pair(d, ii(i, j)));
			}
		}

		// Kruskal
		initSet(n);		
		sort(EdgeList.begin(), EdgeList.end());
		roads = railroads = 0.0;
		cont = 0;
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				// Depending on the length of the edge, add its value to railroads or roads
				if(EdgeList[i].first > r)
				{
					// Every time we add a railroads we are connecting a new state
					cont++;
					railroads += EdgeList[i].first;
				}
				else
					roads += EdgeList[i].first;

				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
			}
		}
		roads = round(roads);
		railroads = round(railroads);

		printf("Case #%d: %d %d %d\n", k, cont+1, (int)roads, (int)railroads);
	}
	return 0;
}