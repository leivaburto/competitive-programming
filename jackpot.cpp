/*
 * UVA 10684 The jackpot
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1625
 * DP - Straightforward Max 1D Sum
 *
 */
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int main()
{
	int n, i, sum, ans;
	while(1)
	{
		scanf("%d", &n);
		if(!n) break;
		sum = ans = 0;
		while(n--)
		{
			scanf("%d", &i);
			sum += i;
			ans = max(ans, sum);
			if(sum < 0)	sum = 0;
		}
		if(ans <= 0)
			printf("Losing streak.\n");
		else
			printf("The maximum winning streak is %d.\n", ans);
	}
	return 0;
}