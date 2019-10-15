#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>

using namespace std;

const int maxn = 65;

int n;
long long c[maxn][maxn];
char buf[maxn];

long long gcd(long long a,long long b)
{
	return b == 0 ? a : gcd(b,a % b);
}

struct Fraction
{
	long long num,den;
	Fraction(long long n = 0,long long d = 1):num(n),den(d)
	{
		long long g = gcd(num,den);
		num /= g;
		den /= g;
	}
}frac;

bool operator<(const Fraction &a,const Fraction &b)
{
	return a.num * b.den < a.den * b.num;
}

Fraction operator*(const Fraction &a,const Fraction &b)
{
	return Fraction(a.num*b.num,a.den*b.den);
}

int main()
{
	for (int i = 0;i < maxn;i ++)
	{
		c[i][0] = c[i][i] = 1;
		for (int j = 1;j < i;j ++)
			c[i][j] = c[i-1][j-1] + c[i-1][j];
	}
	while (scanf("%d%s",&n,buf) != EOF)
	{
		map<char,int> mp;
		for (int i = 0;buf[i] != '\0';i ++) mp[buf[i]] ++;
		vector<int> v; v.clear();
		int m = 0;
		for (map<char,int>::iterator i = mp.begin();i != mp.end();i ++)
			v.push_back(i->second), m += i->second;
		sort(v.begin(),v.end());
		Fraction fmin(1,c[n][m]);
		for (int i = 1;i <= n - m;i ++)
			fmin = fmin * Fraction(v.front()+i,i);
		Fraction fmax(1,c[n][m]);
		priority_queue< pair<Fraction,int> > q;
		for (vector<int>::iterator i = v.begin();i != v.end();i ++)
			q.push(make_pair(Fraction(*i+1,1),*i));
		for (int i = 1;i <= n - m;i ++)
		{
			pair<Fraction,int> p = q.top(); q.pop();
			fmax = fmax * p.first;
			int t = p.second / (p.first.num-p.first.den);
			p.first = Fraction(p.first.num*t+1,p.first.den*t+1);
			q.push(p);
		}
		printf("%lld/%lld\n%lld/%lld\n\n",fmax.num,fmax.den,fmin.num,fmin.den);
	}
	return 0;
}
