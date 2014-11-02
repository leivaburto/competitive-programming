/*
 * UVA 11450 Wedding shopping
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2445
 * DP - Bottom up
 *
 */
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

// dp[number of garments][amount of money]
bool dp[21][201];
int garments[21][21], models[21];

int main()
{
	int n, m, c, i, j, k, ans;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d %d", &m, &c);
		memset(dp, 0, sizeof(dp));
		memset(garments, -1, sizeof(garments));
		memset(models, 0, sizeof(models));
		for(i = 0; i < c; i++)
		{
			scanf("%d", &models[i]);
			for(j = 0; j < models[i]; j++)
				scanf("%d", &garments[i][j]);
			
		}
		// Models that can be bought from the first garment with the inital amount of money
		for(i = 0; i < models[0]; i++)
			if((m - garments[0][i]) >= 0)
				dp[0][m - garments[0][i]] = 1;

		// We choose models from next garments based on previous decisions
		for(i = 1; i < c; i++)
			for(j = 0; j <= m; j++)
				if(dp[i-1][j])
					// Check models that can be bought with one of the previous amounts of money
					// by taking this garments' models and substracting its price
					for(k = 0; k < models[i]; k++)
						if((j - garments[i][k]) >= 0)
							dp[i][j - garments[i][k]] = 1;

		ans = -1;
		// Get minimum money left (max money spent)
		for(i = 0; i <= m; i++)
			if(dp[c-1][i])
			{
				ans = m-i;
				break;
			}

		if(ans == -1)
			printf("no solution\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}