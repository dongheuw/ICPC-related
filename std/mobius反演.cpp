#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
typedef long long LL;
typedef pair<int,int> PI;

const int maxn = (int)1e5 + 5;
int Q,mx,f[maxn],miu[maxn];
PI a[maxn];

struct T
{
	int N,M,K,id;
	void read() {scanf("%d%d%d",&N,&M,&K);mx = max(mx,max(N,M));}
}in[maxn];

inline bool cmpk(const T &a,const T &b)
{
	return a.K < b.K;
}

void EulerSelect()
{
	static int prime[maxn],p[maxn],s[maxn];
	static bool notprime[maxn];
	int tot = 0;
	miu[1] = 1;
	fo(i,2,mx)
	{
		if (!notprime[i]) prime[++tot] = i, s[i] = i, p[i] = i, miu[i] = -1;
		fo(j,1,tot)
		{
			if (i * prime[j] > mx) break;
			notprime[i*prime[j]] = 1;
			s[i*prime[j]] = prime[j];
			if (i % prime[j] == 0)
			{
				p[i*prime[j]] = p[i] * prime[j];
				miu[i*prime[j]] = 0;
				break;
			}
			p[i*prime[j]] = prime[j];
			miu[i*prime[j]] = miu[i] * miu[prime[j]];
		}
	}
	a[1] = PI(f[1]=1,1);
	fo(i,2,mx)
	{
		if (i == p[i]) f[i] = ((LL)p[i]*s[i]-1)/(s[i]-1);
		else f[i] = f[i/p[i]] * f[p[i]];
		a[i]= PI(f[i],i);
	}
}

int C[maxn];
inline void Insert(int x,int v)
{
	for (;x <= mx;x += x&(-x)) C[x] += v;
}

inline int Query(int x)
{
	int ret = 0;
	for (;x;x -= x&(-x)) ret += C[x];
	return ret;
}

void Initialize()
{
	scanf("%d",&Q);
	fo(i,1,Q) in[i].read(), in[i].id = i; 
	EulerSelect();
	sort(a+1,a+1+mx);
	sort(in+1,in+1+Q,cmpk);
}

int ANS[maxn];
void Work()
{
	int last = 0;
	fo(i,1,Q)
	{
		for (int j = last+1;;j ++)
		{
			if (a[j].first > in[i].K) break;
			last = j;
			fo(k,1,mx)
				if (a[j].second * k <= mx)
					Insert(a[j].second*k,a[j].first*miu[k]);
				else break;
		}
		int ans = 0, N = in[i].N, M = in[i].M;
		for (int j = 1;j <= N && j <= M;)
		{
			int _j = min(N/(N/j),M/(M/j));
			ans += (N/j)*(M/j) * (Query(_j) - Query(j-1));
			j = _j + 1;
		}
		ans = ans & ((1ll<<31)-1); 
		if (ans < 0) ans += 1ll<<31;
		ANS[in[i].id] = ans;
	}
	fo(i,1,Q) printf("%d\n",ANS[i]);
}

int main()
{
	freopen("table.in","r",stdin);
	freopen("table.out","w",stdout);
	Initialize();
	Work();
	return 0;
}
