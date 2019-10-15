#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define x first
#define y second

using namespace std;
typedef long long LL;

const int maxn = 100005;

vector< pair<int,int> > e[maxn];
pair<int,int> a[maxn];
int N,t;
int d[maxn],q[maxn];
LL f[maxn];

struct stack
{
	int x,dep,fa,k,_t,_pos,_val;
}S[maxn];

void read(int &x)
{
	static char ch;
	x = 0;
	do ch = getchar(); while (ch < '0' || ch > '9');
	do x = x * 10 + ch - 48, ch = getchar(); while (ch >= '0' && ch <= '9');
}

void Initialize()
{
	read(N);
	fo(i,1,N-1)
	{
		int x,y,len;
		read(x), read(y), read(len);
		e[x-1].push_back(make_pair(y-1,len));
		e[y-1].push_back(make_pair(x-1,len));
	}
	fo(i,1,N-1) read(a[i].x),read(a[i].y);
}

inline double cross(int K, int J)
{
	return (double) (f[J]-f[K]) / (d[J]-d[K]);
}

void dfs_demo()
{
	int C = 1;
	S[C].fa = S[C].k = -1;
	while (C)
	{
		int x = S[C].x;
		int fa = S[C].fa;
		int dep = S[C].dep;
		int &k = S[C].k;
		int &_pos = S[C]._pos;
		int &_val = S[C]._val;
		int &_t = S[C]._t;
		if (k == -1)
		{
			d[x] = dep; 
			f[x] = a[x].x + LL(dep) * a[x].y;
			_t = t;
			if (t > 1)
			{
				int p = q[0];
				int l,r,mid;
				if (cross(q[0],q[1]) < a[x].y)
				{
					for (l = 0, r = t-2, mid = (l+r+1) >> 1;l < r;mid = (l+r+1)>>1)
						if (cross(q[mid],q[mid+1]) < a[x].y) 
							l = mid;
						else r = mid-1;
					p = q[l+1];
				}
				f[x] = min(f[x],f[p]+a[x].x + LL(a[x].y) * (dep-d[p]));
				//f[x] = min(f[x],f[p]+a[x].x) + (LL)a[x].y * (dep-d[p]);
				for (l = 1, r = t-1, mid = (l+r+1) >> 1;l < r;mid = (l+r+1)>>1)
					if (cross(q[mid-1],q[mid]) < cross(q[mid-1],x))  l = mid;
					else r = mid-1;
				if (cross(q[l-1],q[l]) > cross(q[l-1],x)) l --;

				_pos = l+1, _val = q[_pos];
				t = l+2, q[t-1] = x;
			}
			else
			{
				_pos = t, _val = q[_pos];
				q[t++] = x;
			}
			k ++;
		} else 
		{
			if (k < e[x].size())
			{
				if (e[x][k].x != fa) 
				{
					S[++C].x = e[x][k].x;
					S[C].fa = x;
					S[C].dep = dep + e[x][k].y;
					S[C].k = -1;
				}
				k ++;
				continue;
			} else 
			{
				t = _t;
				q[_pos] = _val;
				C --;
			}
		}
	}
}

void Work()
{
	dfs_demo();
	fo(i,1,N-2) printf("%lld ",f[i]);
	printf("%lld\n",f[N-1]);
}

int main()
{
	freopen("harbingers.in","r",stdin);
	freopen("harbingers.out","w",stdout);
	Initialize();
	Work();
	return 0;
}
