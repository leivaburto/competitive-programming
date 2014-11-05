/*
 * UVA 1160 X-Plosives
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3601
 * Union-Find
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
int rank[100005];

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

int isSameSet(int i, int j)
{
	return (findSet(i) == findSet(j));
}

void unionSet(int i, int j)
{
	rank[findSet(i)] = findSet(j);
}

int main()
{
	int x, y, refusals;
	while(scanf("%d", &x) == 1)
	{
		initSet(100000);
		refusals = 0;
		while(1)
		{
			if(x != -1)
			{
				scanf("%d", &y);
				// Union-find
				// If we receive a request for joining two elements that are
				// in the same set it means we are closing a cycle, and that
				// will produce an explosion. Refuse such requests.
				if(!isSameSet(x, y))
					unionSet(x, y);
				else
					refusals++;
				scanf("%d", &x);
			}
			else break;
		}
		printf("%d\n", refusals);
	}
	return 0;
}