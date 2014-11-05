/*
 * UVA 12356 Army Buddies
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3778
 * 1D Array. Fast solution is required 
 *
 */
#include <cstdio>
#include <cstring>
#define MAX 100000
using namespace std;

int main()
{
	int s, b, l, r, left, right, soldiers_left[MAX+3], soldiers_right[MAX+3];
	scanf("%d %d", &s, &b);
	while(s && b)
	{
		// Initial state: All soldiers have '0' as their buddies, except for the first and last one.
		memset(soldiers_left, 0, sizeof(soldiers_left));
		memset(soldiers_right, 0, sizeof(soldiers_right));
		soldiers_left[1] = -1;
		soldiers_right[s] = -1;

		while(b--)
		{
			// Do NOT dare to use 'cin'
			scanf("%d %d", &l, &r);

			// The KEY here is to make a constant call in order too check for buddies
			
			// If the buddy is '0' it means that this soldier is with initial state,
			// and that means that its buddies are l-1 and r+1 (contiguos soldiers)
			// Otherwise get the actual buddies from left and right arrays
			(soldiers_left[l] == 0) ? left = l-1: left = soldiers_left[l];
			(soldiers_right[r] == 0) ? right = r+1: right = soldiers_right[r];
			
			if(left == -1)
				printf("* ");
			else
			{
				printf("%d ", left);
				// Update the buddies after the [L, R] soldiers are killed
				soldiers_right[left] = right;
			}

			if(right == -1)
				printf("*\n");
			else
			{
				printf("%d\n", right);
				// Update the buddies after the [L, R] soldiers are killed
				soldiers_left[right] = left;
			}
		}
		printf("-\n");
		scanf("%d %d", &s, &b);
	}
	return 0;
}