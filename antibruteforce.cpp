/*
 * UVA 01235 Anti Brute Force Lock
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3676
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
vector<int> rank(501);

// Union-Find operations
void initSet(int n)
{
	int i;
	for(i = 0; i < n; i++)
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

// Calculate how many rolls are from one configuration to another
int total_rolls(char *key1, char *key2)
{
	int i, a, b, rolls = 0;
	for(i = 0; i < 4; i++)
	{
		a = key1[i] - '0';
		b = key2[i] - '0';
		// The minimun between the difference of the digits or
		// the minimun between going the other way around with one or another
		// Ex. 9 and 2
		// Could be 9-2 = 7 rolls
		// Or turn the first digit up to cero (10-9 = 1 rolls up to cero) plus from cero to 2 => 1+2 = 3
		// Or turn the second digit up to cero (10-2 = 8) plus from cero to 9 => 8+9 = 17
		// min(7, min(3, 17))
		// min(7, 3)
		// 3
		rolls += min(abs(a - b), min(a + (10 - b), b + (10 - a)));
	}
	return rolls;
}

int main()
{
	int t, n, i, j, total, rolls;
	char keys[501][5], origin[5] = { "0000" };

	scanf("%d", &t);
	
	while(t--)
	{
		scanf("%d", &n);

		total = 99999999;
		EdgeList.clear();

		// Read the initial configurations and calculate their differences
		// with the initial state 0000 and we save the minimum
		for(i = 0; i < n; i++)
		{
			scanf("%s", keys[i]);
			total = min(total, total_rolls(keys[i], origin));
		}

		// Calculate the distance of going from every configuration to any other configuration
		// Remember that we have a magic JUMP button that can turn the digits into any of the unlocked keys
		// So we can conveniently JUMP into the closest configuration if we want to
		for(i = 0; i < n; i++)
		{
			for(j = i+1; j < n; j++)
			{
				rolls = total_rolls(keys[i], keys[j]);
				if(rolls > 0)
					EdgeList.push_back(make_pair(rolls, ii(i, j)));
			}
		}

		// KEEP CALM and Kruskal
		initSet(n);		
		sort(EdgeList.begin(), EdgeList.end());

		for(i = 0; i < EdgeList.size(); i++)
		{
			if(!isSameSet(EdgeList[i].second.first, EdgeList[i].second.second))
			{
				total += EdgeList[i].first;
				unionSet(EdgeList[i].second.first, EdgeList[i].second.second);
			}
		}

		// The answer is the weight of the MST that connects the configurations
		printf("%d\n", total);
	}
	return 0;
}