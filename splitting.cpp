/*
 * UVA 11933 Splitting Numbers
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3084
 * Bit manipulation
 *
 */
#include <iostream>
using namespace std;
int main()
{
	int n, a, b, i;
	bool flag;
	cin >> n;
	while(n)
	{
		flag = true;
		a = b = 0;
		// We are not going any further than 32 bits
		for(i = 0; i < 32; i++)
		{
			if(n & (1 << i))
			{
				// Depending of the value of 'flag', the corresponding bit will be for 'a' or 'b'
				(flag) ? a ^= (1 << i): b ^= (1 << i);
				flag = !flag;
			}
		}
		cout << a << " " << b << endl;
		cin >> n;
	}
	return 0;
}