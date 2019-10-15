#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
typedef unsigned long long LL;

LL N,K,temp,ans,tot;
LL p[10000005],a[10005],b[10005];
int T,num;
bool f[10000005];

int main()
{
	freopen("g.in","r",stdin);
	freopen("g.out","w",stdout);
	memset(f,true,sizeof (f));
	for (int t = 2;t <= 10000000;t ++)
    	if (f[t]) for (int k = t*2;k <= 10000000;k += t) f[k] = 0;
	fo(t,2,10000000) if (f[t]) p[++tot] = t;
	scanf("%d",&T);
	fo(cs,1,T)
    {
    	cin >> N >> K;
    	if (K == 1) 
    	{
    		printf("Case %d: inf\n",cs);
    		continue;
    	}
        num = 0;
        temp = K;
        for (int i = 1;i <= tot;i ++)
        	if (temp % p[i] == 0)
        	{
        		a[++num] = p[i], b[num] = 0;
				while (temp % p[i] == 0) temp /= p[i], b[num] ++;
			}
		if (temp != 1) a[++num] = temp, b[num] = 1;
		ans = -1;
		fo(i,1,num)
		{
			temp = 0;
			LL g = a[i];
			while (1)
			{
				temp += N/g;
				if (N / a[i] >= g) g *= a[i]; else break;
			}
			if (ans == -1) ans = temp/b[i]; else ans = min(temp/b[i],ans);
		}
		cout << "Case " << cs << ": " << ans << endl;
     }
     return 0;
}
