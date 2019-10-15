#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
typedef unsigned long long LL;

LL T,N,K,temp,ans,p[100005],tot,a[105],b[105];
int num;
bool f[1000005];

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	memset(f,true,sizeof (f));
	for (int t = 2;t <= 1000000;t ++)
    	if (f[t])
    		for (int k = t*2;k <= 1000000;k += t) f[k] = 0;
	tot = 0;
	fo(t,2,1000000) if (f[t]) p[++tot] = t;
	cin >> T;
	while (T --)
    {
    	cin >> N >> K;
        num = 0;
        temp = K;
        for (int i = 1;i <= tot;i ++)
        	if (temp % p[i] == 0)
        	{
        		a[++num] = p[i];
        		b[num]=0;
				while (temp % p[i] == 0)
				{
					temp /= p[i];
					b[num] ++;
				}
			}
		if (temp != 1)
		{
			a[++num] = temp;
			b[num] = 1;
		}
		ans = (LL)(1e18);
		fo(i,1,num)
		{
			temp = 0;
			LL g = a[i];
			while (1)
			{
				temp += N/g;
				if (N/a[i] >= g) g *= a[i];
				else break;
			}
			ans = min(temp/b[i],ans);
		}
		cout << ans << endl;
     }
     return 0;
}
