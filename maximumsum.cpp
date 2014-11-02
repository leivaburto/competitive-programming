/*
 * UVA 108 Maximum Sum
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=44
 * DP - Straightforward Max 2D Sum
 *
 */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int A[101][101];

int main()
{
	int n, i, j, k, l, sum, maxsum;
	
	scanf("%d", &n);
	memset(A, 0, sizeof(A));

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			scanf("%d", &A[i][j]);
			// Inclusion-exclusion
			if(i > 0) A[i][j] += A[i-1][j];
			if(j > 0) A[i][j] += A[i][j-1];
			if(i > 0 && j > 0) A[i][j] -= A[i-1][j-1];
		}
	}
	// Calculate max sum for every submatrix
	maxsum = -2000000;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			for(k = i; k < n; k++)
			{
				for(l = j; l < n; l++)
				{
					sum = A[k][l];
					// Inclusion-exclusion
					if(i > 0) sum -= A[i-1][l];
					if(j > 0) sum -= A[k][j-1];
					if(i > 0 && j > 0) sum += A[i-1][j-1];
					maxsum = max(maxsum, sum);
				}
			}
		}
	}
	printf("%d\n", maxsum);
	return 0;
}