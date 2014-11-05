/*
 * UVA 11926 Multitasking
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3077
 * Boolean arrays (or bitsets)
 *
 */
#include <iostream>
#include <string.h>
#define MAX 1000000
using namespace std;
int main()
{
	bool calendar[MAX+10], left[MAX+10], right[MAX+10], conflict;
	int n, m, s, e, r, i, j;
	cin >> n >> m;
	while(1)
	{
		if(!n && !m) break;
		memset(calendar, 0, sizeof(calendar));
		memset(left, 0, sizeof(left));
		memset(right, 0, sizeof(right));
		conflict = false;
		for(i = 0; i < n; i++)
		{
			// start end
			cin >> s >> e;
			if(!conflict)
			{
				for(j = s; j <= e; j++)
				{
					// Check for overlaps
					if(!calendar[j])
					{
						calendar[j] = 1;
						// Map each border to the corresponding category (left border, right border)
						if(j == s) left[j] = 1;
						if(j == e) right[j] = 1;
					}
					else
					{
						// If the overlap occurred with a contrary border, then everything should be ok
						// Otherwise, there is a conflict
						// (It's ok for a left border to overlap with a right border from other interval
						// but no with a left border, because that will mean that the later interval is inside
						// the first one)
						if(j == s && !right[j]) conflict = true;
						if(j == e && !left[j]) conflict = true;
					}
					if(conflict) break;
				}
			}
		}
		for(i = 0; i < m; i++)
		{
			// start end repetition_intervals
			cin >> s >> e >> r;
			if(!conflict)
			{
				while(s <= MAX)
				{
					for(j = s; j <= e; j++)
					{
						if(j > MAX)
							break;
						// Same as before (overlaps, borders, etc)
						if(!calendar[j])
						{
							calendar[j] = 1;
							if(j == s) left[j] = 1;
							if(j == e) right[j] = 1;
						}
						else
						{
							if(j == s && !right[j]) conflict = true;
							if(j == e && !left[j]) conflict = true;
						}
						if(conflict) break;
					}
					s += r;
					e += r;
				}
			}
		}
		if(conflict)
			cout << "CONFLICT" << endl;
		else
			cout << "NO CONFLICT" << endl;
		cin >> n >> m;
	}
	return 0;
}