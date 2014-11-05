/*
 * UVA 10048 Audiophobia
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=989
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
typedef vector<ii> vii; 

vector< pair<double, ii> > EdgeList;
vector<int> rank(105);
vector<vii> AdjList;

int numSets, dfs_num[105];

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
	weight = -1;
	for(i = 0; i < (int)AdjList[u].size(); i++)
	{
		if(dfs_num[AdjList[u][i].first] == 0)
		{
			// Stop if we got to vertex v
			if(AdjList[u][i].first == v)
				return AdjList[u][i].second;
			else
			{
				// Save the max
				x = dfs(AdjList[u][i].first, v);
				if(x != -1)
					weight = max(weight, max(x, AdjList[u][i].second));
			}
		}
	}
	return weight;
}

int main()
{
	int c, s, q, u, v, d, i, maxweight, cases = 0;
	while(1)
	{
		scanf("%d %d %d", &c, &s, &q);

		if(!c && !s && !q) break;

		EdgeList.clear();

		for(i = 0; i < s; i++)
		{
			scanf("%d %d %d", &u, &v, &d);
			EdgeList.push_back(make_pair(d, ii(u, v)));
		}

		AdjList.assign(c+1, vii());

		// Kruskal
		initSet(c);
		sort(EdgeList.begin(), EdgeList.end());
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
				// Save edge in MST
				AdjList[EdgeList[i].second.first].push_back(ii(EdgeList[i].second.second, EdgeList[i].first));
				AdjList[EdgeList[i].second.second].push_back(ii(EdgeList[i].second.first, EdgeList[i].first));
			}
		}

		if(cases) printf("\n");
		printf("Case #%d\n", ++cases);

		// DFS on MST tree (from u to v) for each query
		for(i = 0; i < q; i++)
		{
			scanf("%d %d", &u, &v);

			memset(dfs_num, 0, sizeof(dfs_num));
			maxweight = dfs(u, v);

			if(maxweight == -1)
				printf("no path\n");
			else
				printf("%d\n", maxweight);
		}
	}
	return 0;
}