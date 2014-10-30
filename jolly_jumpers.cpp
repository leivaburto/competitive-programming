/*
 * UVA 10038 Jolly Jumpers
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=979
 * Boolean mapping of the differences
 *
 */
#include <iostream>
#include <string.h>
using namespace std;
int main ()
{
	int N, x1, x2, i, diff;
	bool jolly[3001], flag_jolly;
	while(cin >> N)
	{
		memset(jolly, 0, sizeof jolly);
		flag_jolly = true;
		cin >> x1;
		for(i = 0; i < N-1; i++)
		{
			cin >> x2;
			diff = x2 - x1;
			// Abs
			if(diff < 0) diff *= -1;
			// Check if exists or out of range
			if(jolly[diff]) flag_jolly = false;
			if(diff > N-1) flag_jolly = false;
			jolly[diff] = 1;
			x1 = x2;
		}
		if(flag_jolly)
			cout << "Jolly" << endl;
		else
			cout << "Not jolly" << endl;
	}
	return 0;
}