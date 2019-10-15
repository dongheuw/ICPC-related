#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int Mod = (int)1e9 + 7;
const int Base = 31;
const int maxn = 205;
const int maxl = 20005; //20005

unordered_map<int,int> mp;
int T,n,f[maxn][maxl],fac[maxl];
char s[maxn][maxl];

inline int get(int id,int l,int r)
{
	int ret = f[id][r] - (long long)f[id][l-1]*fac[r-l+1]%Mod + Mod;
	if (ret >= Mod) ret -= Mod;
	return ret;
}

int main()
{
	freopen("h.in","r",stdin);
	freopen("h.out","w",stdout);
	fac[0] = 1;
	fo(i,1,20000) fac[i] = (long long)fac[i-1]*Base%Mod; //20000
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d",&n);
		fo(i,1,n) scanf("%s",s[i]+1);
		mp.clear();
		fo(i,1,n)
		{
			int len = strlen(s[i]+1);
			f[i][0] = 0;
			fo(j,1,len)
				f[i][j] = ((long long)f[i][j-1]*Base+s[i][j]-'a') % Mod;
			fo(j,1,len) mp[get(i,1,j)] ++;
		}
		int x = 0, y = 0;
		fo(i,1,n)
		{
			int len = strlen(s[i]+1);
			fo(j,1,len) mp[get(i,1,j)] --;
			fo(j,1,len)
			{
				int cur = get(i,len-j+1,len), pre = cur;
				if (!mp[cur]) continue;
				int tmp = 1, tmp2 = 1;
				for (int k = 2;k*j <= len;k ++)
				{
					int fk = get(i,len-k*j+1,len);
					cur = ((long long)cur*fac[j] + pre) % Mod;
					if (cur != fk) break;
					tmp2 = k;
					if (mp[cur]) tmp ++;
				}
				if (tmp == tmp2 && tmp == 1) continue;
				if (tmp == tmp2) tmp --;
				if (tmp*j+tmp2*j > x+y) x = tmp*j, y = tmp2*j;
			}
			fo(j,1,len) mp[get(i,1,j)] ++;
		}
		printf("%d %d\n",x,y);
	}
}
