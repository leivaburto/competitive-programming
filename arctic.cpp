/*
 * UVA 10369 Arctic Network
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1310
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
vector<int> rank(505);

int outposts[505][2], numSets;

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
	int n, s, p, i, j;
	double d, last;
	
	scanf("%d", &n);

	while(n--)
	{
		scanf("%d %d", &s, &p);

		for(i = 0; i < p; i++)
			scanf("%d %d", &outposts[i][0], &outposts[i][1]);

		EdgeList.clear();
		// Connect all the outposts with proper edges
		for(i = 0; i < p; i++)
		{
			for(j = i+1; j < p; j++)
			{
				d = hypot((double)outposts[i][0]-outposts[j][0], (double)outposts[i][1]-outposts[j][1]);
				EdgeList.push_back(make_pair(d, ii(i, j)));
			}
		}

		// Kruskal until we reach the desired number of components (one component for each satellital transmission)
		initSet(p);		
		sort(EdgeList.begin(), EdgeList.end());
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				last = EdgeList[i].first;
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
			}
			if(numDisjointSets() == s)
				break;
		}

		printf("%.2lf\n", last);
	}
	return 0;
}