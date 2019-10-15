#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

vector<bool> a[2][3],d,t,x,y;

void trim(vector<bool> &a)
{
	while (!(a.empty() || a.back())) a.pop_back();
}

bool read(vector<bool> &a)
{
	int n;
	if (scanf("%d",&n) == EOF) return 0;
	a.resize(n+1);
	for (vector<bool>::reverse_iterator it = a.rbegin();it != a.rend();++ it)
	{
		scanf("%d",&n);
		*it = (n != 0);
	}
	return 1;
}

void write(vector<bool> &a)
{
	if (a.empty()) puts("-1");
	else
	{
		printf("%d ",(int)a.size()-1);
		for (vector<bool>::const_reverse_iterator it = a.rbegin();it != a.rend();++ it)
			puts(*it?" 1":" 0");
		printf("\n");
	}
}

vector<bool> operator+(const vector<bool> &a,const vector<bool> &b)
{
	if (a.size() < b.size()) return b + a;
	vector<bool> ret(a);
	for (unsigned i = 0;i < b.size();i ++)
		ret[i] = ret[i] ^ b[i];
	trim(ret);
	return ret;
}

vector<bool> operator-(const vector<bool> &a,const vector<bool> &b){ return a + b; }

vector<bool> operator*(const vector<bool> &a,const vector<bool> &b)
{
	vector<bool> ret;
	if (a.size() == 0 || b.size() == 0) return ret;
	ret.resize(a.size()+b.size() - 1);
	for (unsigned i = 0;i < a.size();i ++)
		if (a[i])
			for (unsigned j = 0;j < b.size();j ++)
				ret[i+j] = ret[i+j] ^ b[j];
	return ret;
}

void divmod(vector<bool> &a,vector<bool> &b)
{
	vector<bool> ret;
	for (int i = (int)a.size()-1;i >= (int)b.size()-1;i --)
		if (a[i])
		{
			for (int j = 0;j < (int)b.size();j ++)
				a[i-j] = a[i-j] ^ b[(int)b.size()-1-j];
			ret.push_back(true);
		} else ret.push_back(0);
	reverse(ret.begin(),ret.end());
	trim(a);
	a.swap(ret);
	b.swap(ret);
}

vector<bool> extGcd(vector<bool> a,vector<bool> b,vector<bool> &x,vector<bool> &y)
{
	vector<bool> g;
	if (b.size() == 0)
	{
		g = a;
		x.resize(1);
		x[0] = 1;
		y.clear();
	} else
	{
		g = b;
		divmod(a,b);
		g = extGcd(g,b,y,x);
		y = y - a * x;
	}
	return g;
}

int main()
{
	bool flag;
	while (1)
	{
		for (int i = 0;i < 2;i ++)
			for (int j = 0;j < 3;j ++)
				if (!read(a[i][j])) return 0;
		flag = 0;
		d = a[0][0] * a[1][1] - a[1][0] * a[0][1];
		x = a[0][2] * a[1][1] - a[1][2] * a[0][1];
		y = a[0][0] * a[1][2] - a[1][0] * a[0][2];
		if (!d.empty())
		{
			t = d;
			divmod(x,t);
			divmod(y,d);
			if (!(t.empty() && d.empty())) flag = 1;
		} else if (!(x.empty() && y.empty())) flag = 1;
		else if (a[0][2].empty() && a[1][2].empty())
			x.clear(), y.clear();
		else
			for (int i = 0;i < 2;i ++)
			{
				if (a[i][0].empty() && a[i][1].empty())
				{
					if (a[i][2].empty()) continue;
					else flag = true;
				} else
				{
					d = extGcd(a[i][0],a[i][1],x,y);
					t = a[i][2];
					divmod(t,d);
					if (d.empty()) x = x * t, y = y * t;
					else flag = 1;
				}
				break;
			}
		if (flag) puts("No solution");
		else write(x), write(y);		
		puts("");
	}
}
