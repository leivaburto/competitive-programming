/*
 * UVA 11710 Expensive Subway
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2757
 * MST and number of components
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
typedef map<string, int> Mtype;

Mtype stations; 
vector< pair<int, ii> > EdgeList;
vector<int> rank(405);
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
	int s, c, w, i, cont, total;
	string u, v;
	
	while(1)
	{
		scanf("%d %d", &s, &c);

		if(!s && !c) break;

		EdgeList.clear();
		stations.clear();

		for(i = 0; i < s; i++)
		{
			cin >> u;
			stations.insert( Mtype::value_type(u, i) );
		}

		for(i = 0; i < c; i++)
		{
			cin >> u >> v >> w;
			EdgeList.push_back(make_pair(w, ii(stations[u], stations[v])));
		}
		cin >> u;

		// Kruskal
		initSet(s);		
		sort(EdgeList.begin(), EdgeList.end());
		cont = 0;
		total = 0;
		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				total += EdgeList[i].first;
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
				cont++;
			}
			if(cont == s-1)
				break;
		}
		// If we have a forest after running MST, print Impossible
		if(numSets > 1)
			printf("Impossible\n");
		else
			printf("%d\n", total);
	}
	return 0;
}