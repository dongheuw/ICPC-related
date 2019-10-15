#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 160;

bool x[maxn*3][maxn],y[maxn*3],z[maxn];
int m,n;

struct BP : vector<bool>
{
	bool operator[](int i) const
	{
		return 0 <= i && i < (int)size() ? BP::operator[](i) : 0;
	}
}a,b,c;

void trim(BP &a)
{
	while (!(a.empty() || a.back())) a.pop_back();
}

bool solve(int m,int n,bool a[maxn*3][maxn],bool  b[maxn*3],bool y[maxn])
{
	static int p[maxn*3];
	int r = 0,c = 0;
	while (r < m && c < n)
	{
		int rr = -1;
		for (int i = r;i < m;i ++)
			if (a[i][c])
			{
				rr = i;
				break;
			}
		if (rr != -1)
		{
			for (int j = c;j < n;j ++) swap(a[r][j],a[rr][j]);
			swap(b[r],b[rr]);
			for (int i = r + 1;i < m;i ++)
				if (a[i][c])
				{
					a[i][c] = 0;
					for (int j = c + 1;j < n;j ++)
						if (a[r][j]) a[i][j] = !a[i][j];
					if (b[r]) b[i] = !b[i];
				}
			p[r] = c;
			r ++;
		}
		c ++;
	}
	for (int i = r;i < m;i ++) if (b[i]) return 0;
	c = n - 1;
	for (int i = r - 1;i >= 0;i --)
	{
		while (c > p[i]) y[c--] = 0;
		y[c] = b[i];
		for (int j = n - 1;j > c;j --)
			y[c] ^= a[i][j] && y[j];
		c --;

	}
	while (c >= 0) y[c--] = 0;
	return 1;
}

bool read(BP &a)
{
	int n;
	if (scanf("%d",&n) == EOF) return 0;
	a.resize(n+1);
	for (BP::reverse_iterator it = a.rbegin();it != a.rend();++ it)
	{
		scanf("%d",&n);
		*it = (n != 0);
	}
	return 1;
}

void write(BP &a)
{
	if (a.empty()) puts("-1");
	else
	{
		printf("%d ",(int)a.size()-1);
		for (BP::const_reverse_iterator it = a.rbegin();it != a.rend();++ it)
			puts(*it ? " 1" : " 0");
		printf("\n");
	}
}

int main()
{
	while (read(a) && read(b) && read(c))
	{
		n = max(a.size(),max(b.size(),c.size()));
		m = 3*n;
		for (int i = 0;i <= m;i ++)
		{
			for (int j = 0;j <= n;j ++)
				x[i][j] = a[i - 2*j] ^ b[i - j];
			y[i] = c[i];
		}
		if (solve(m+1,n+1,x,y,z))
		{
			BP ans;
			ans.insert(ans.end(),z,z + n + 1);
			trim(ans);
			write(ans);
		} else puts("no solution");
		puts("");
	}
}
