/*
 * UVA 507 Jill Rides Again
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=448
 * DP - Max 1D Sum (and get the interval of that max sum)
 *
 */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	int b, s, i, k, r, max, max_i, max_j, sum, current_i, current_diff, max_diff;
	scanf("%d", &b);
	for(k = 1; k <= b; k++)
	{
		scanf("%d", &s);
		max_i = max_j = current_i = 1;
		max = sum = 0;
		for(i = 1; i <= s-1; i++)
		{
			// We are given the value of going from i to i+1
			scanf("%d", &r);
			sum += r;
			if(sum > max)
			{
				// Current_i : setted in the first iteration. 
				// [max_i, max_j] is the max sum interval
				max_i = current_i;
				max_j = i+1;
				max = sum;
			}
			else if(sum == max)
			{
				// If we have two max sums, we take the longest one
				current_diff = i+1 - current_i;
				max_diff = max_j - max_i;
				if(current_diff > max_diff)
				{
					max_i = current_i;
					max_j = i+1;
					max = sum;
				}
				else if(current_diff == max_diff)
				{
					// If we have two max longest intervals, we take the one that started first
					if(current_i < max_i)
					{
						max_i = current_i;
						max_j = i+1;
						max = sum;
					}
				}
			}
			// If we get to 0, we reset the start index of the interval to i+1
			if(sum < 0)
			{
				sum = 0;
				current_i = i+1;
			}
		}

		if(max <= 0)
			printf("Route %d has no nice parts\n", k);
		else
			printf("The nicest part of route %d is between stops %d and %d\n", k, max_i, max_j);
	}
	return 0;
}