/*
 * UVA 10264 The Most Potent Corner
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1205
 * Bitmask
 *
 */
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;
int main()
{
	// 2^14 = 16384, so 17000 is enough
	int n, i, j, neighbour, weights[17000], potencies[17000], num_corners, max_sum;
	while(cin >> n)
	{
		memset(weights, 0, sizeof(weights));
		memset(potencies, 0, sizeof(potencies));
		// N dimensions => 2^N corners
		num_corners = pow(2, n);
		for(i = 0; i < num_corners; i++)
			cin >> weights[i];
		// For each corner, sum its neighbours' weights
		for(i = 0; i < num_corners; i++)
		{
			potencies[i] = 0;
			// corner 'i' has n neighbours, each one of them is determined by flipping one bit at the time
			// to be clear, draw a 3 dimensional cube and check for (0,0,0) or (1,1,0) neighbours
			for(j = 0; j < n; j++)
			{
				neighbour = i ^ (1 << j);
				potencies[i] += weights[neighbour];
			}
		}
		// Iterate and get max sum
		max_sum = 0;
		for(i = 0; i < num_corners; i++)
		{
			for(j = 0; j < n; j++)
			{
				neighbour = i ^ (1 << j);
				max_sum = max(max_sum, potencies[i] + potencies[neighbour]);
			}
		}
		cout << max_sum << endl;
	}
	return 0;
}