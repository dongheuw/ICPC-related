#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

long long n;

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	cin >> n;
	for (long long i = 1;i <= n;i ++)
	{
		if (i == 1) cout << 2 << endl;
		else cout << i*(i+1)*(i+1)-(i-1) << endl;
	}
	return 0;
}
