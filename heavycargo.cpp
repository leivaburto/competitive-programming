/*
 * UVA 544 Heavy Cargo
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=485
 * Maximin
 *
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<string, int> Mtype;

Mtype cities;
vector< pair<double, ii> > EdgeList;
vector<int> rank(205);
vector<vii> AdjList;

int numSets, dfs_num[205];

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

int dfs(int u, int v)
{
	int i, x, weight;
	dfs_num[u] = 1;
	weight = -100005;
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
				if(x != -100005)
					weight = max(weight, max(x, AdjList[u][i].second));
			}
		}
	}
	return weight;
}

int main()
{
	int n, r, d, i, minweight, cases = 0, cont, k;
	string u, v;
	while(1)
	{
		scanf("%d %d", &n, &r);

		if(!n && !r) break;

		EdgeList.clear();
		cities.clear();
		k = 0;

		for(i = 0; i < r; i++)
		{
			cin >> u >> v >> d;
			
			if(cities.find(u) == cities.end())
				cities.insert( Mtype::value_type(u, ++k) );
			if(cities.find(v) == cities.end())
				cities.insert( Mtype::value_type(v, ++k) );
			// Insert opposite values (-d) in order to run Kruskal and get Max Spanning Tree 
			EdgeList.push_back(make_pair(-d, ii(cities[u], cities[v])));
		}
		cin >> u >> v;

		AdjList.assign(n+1, vii());

		// Kruskal
		initSet(n);
		sort(EdgeList.begin(), EdgeList.end());
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
				// Add to tree
				AdjList[EdgeList[i].second.first].push_back(ii(EdgeList[i].second.second, EdgeList[i].first));
				AdjList[EdgeList[i].second.second].push_back(ii(EdgeList[i].second.first, EdgeList[i].first));
			}
		}

		printf("Scenario #%d\n", ++cases);

		// DFS on MST, from u to v
		memset(dfs_num, 0, sizeof(dfs_num));
		minweight = dfs(cities[u], cities[v]);

		// As we saved the neg. value, now we must print the opposite
		printf("%d tons\n\n", -minweight);
	}
	return 0;
}