/*
 * UVA 534 Frogger
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=475
 * Minimax
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
typedef pair<int, double> id;
typedef vector<id> vid; 

vector< pair<double, ii> > EdgeList;
vector<int> rank(205);
vector<vid> AdjList;

int stones[205][2], numSets, dfs_num[205];

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

double dfs(int u, int v)
{
	int i;
	double x, weight = -1.0;
	dfs_num[u] = 1;
	for(i = 0; i < (int)AdjList[u].size(); i++)
	{
		if(dfs_num[AdjList[u][i].first] == 0)
		{
			// Stop if we got to vertex v
			if(AdjList[u][i].first == v)
				return AdjList[u][i].second;
			else
			{
				// Save the max (the values are negative so we are actually getting the min)
				x = dfs(AdjList[u][i].first, v);
				if(x != -1.0)
					weight = max(weight, max(x, AdjList[u][i].second));
			}
		}
	}
	return weight;
}

int main()
{
	int n, s, p, i, j, cases = 0;
	double d, minimax;

	while(1)
	{
		scanf("%d", &n);

		if(!n) break;

		for(i = 0; i < n; i++)
			scanf("%d %d", &stones[i][0], &stones[i][1]);

		EdgeList.clear();

		// Connect all the stones with edges
		for(i = 0; i < n; i++)
		{
			for(j = i+1; j < n; j++)
			{
				d = hypot((double)stones[i][0]-stones[j][0], (double)stones[i][1]-stones[j][1]);
				EdgeList.push_back(make_pair(d, ii(i, j)));
			}
		}

		AdjList.assign(n+1, vid());

		// Kruskal
		initSet(n);
		sort(EdgeList.begin(), EdgeList.end());
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
				// Add edge to MST
				AdjList[EdgeList[i].second.first].push_back(id(EdgeList[i].second.second, EdgeList[i].first));
				AdjList[EdgeList[i].second.second].push_back(id(EdgeList[i].second.first, EdgeList[i].first));
			}
		}

		printf("Scenario #%d\n", ++cases);

		// DFS on MST from 0 to 1 (first and second stones)
		memset(dfs_num, 0, sizeof(dfs_num));
		minimax = dfs(0, 1);
		
		printf("Frog Distance = %.3lf\n\n", minimax);
	}
	return 0;
}