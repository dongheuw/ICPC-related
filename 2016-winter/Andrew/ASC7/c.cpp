#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const char Month[13][10] = {"","January","February","March","April","May","June","July","August","September","October","November","December"};
map<string,int> M;
int T,N,TO,FROM,tot,sum[2505];
int f[110][110],opt[110][110],K[110];

bool isLeap(int y)
{
	return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

struct Date
{
	int m,d;
	bool operator<(const Date &rhs) const
	{
		if (m == rhs.m) return d < rhs.d;
		return m < rhs.m;
	}
	bool operator==(const Date &rhs) const
	{
		return m == rhs.m && d == rhs.d;
	}
}d1[110],d2[110];

void Initialize()
{
	M["January"] = 1;
	M["February"] = 2;
	M["March"] = 3;
	M["April"] = 4;
	M["May"] = 5;
	M["June"] = 6;
	M["July"] = 7;
	M["August"] = 8;
	M["September"] = 9;
	M["October"] = 10;
	M["November"] = 11;
	M["December"] = 12;
	sum[0] = 0;
	fo(i,1,2300)
		if (isLeap(i)) sum[i] = sum[i-1] + 1;
		else sum[i] = sum[i-1];
}

void Reset()
{
	scanf("%d%d",&TO,&FROM);
	scanf("%d",&N);
	fo(i,0,N-1)
	{
		string s1,s2,s3,s4,s5;
		cin >> s1 >> s2 >> s3 >> s4 >> s5;
		d1[i].m = M[s1];
		if (s2.size() == 2) d1[i].d = s2[0] - '0';
		else d1[i].d = (s2[0]-'0') * 10 + s2[1] - '0';
		if (s3 == "added") K[i] = 1;
		else K[i] = -1;
		d2[i].m = M[s4];
		if (s5.size() == 1) d2[i].d = s5[0] - '0';
		else d2[i].d = (s5[0]-'0') * 10 + s5[1] - '0';
	}
	tot = FROM - TO + 1;
	memset(f,-1,sizeof f);
}

void Work()
{
	fo(i,0,tot-1)
	{
		if (d1[0].m == 2 && d1[0].d == 29 && !isLeap(TO+i)) continue;
		if (d2[0].m == 2 && d2[0].d == 29)
		{
			if (d1[0] < d2[0]) f[0][i] = sum[FROM]-sum[TO+i-1];
			else f[0][i] = sum[FROM]-sum[TO+i];	
		} else
		{
			if (d1[0] < d2[0]) f[0][i] = FROM - (TO+i) + 1;
			else f[0][i] = FROM - (TO+i);
		}
	}
	fo(i,1,N-1)
	{
		fo(j,0,tot-1)
		{
			int temp;
			if (d1[i].m == 2 && d1[i].d == 29 && !isLeap(TO+j)) continue;
			if (d2[i].m == 2 && d2[i].d == 29)
			{
				if (d1[i] < d2[i]) temp = sum[FROM]-sum[TO+j-1];
				else temp = sum[FROM]-sum[TO+j];	
			} else
			{
				if (d1[i] < d2[i]) temp = FROM - (TO+j) + 1;
				else temp = FROM - (TO+j);
			}
			fo(k,0,j)
			{
				if (k == j && (d1[i] < d1[i-1] || d1[i] == d1[i-1])) continue;
				if (f[i-1][k] == -1) continue;
				if (f[i-1][k] + K[i]*temp > f[i][j])
				{
					f[i][j] = f[i-1][k] + K[i]*temp;
					opt[i][j] = k;
				}
			}
		}
	}
}

void print(int cur,int u)
{
	if (cur < 0) return;
	print(cur-1,opt[cur][u]);
	printf("%s %d %d, ",Month[d1[cur].m],d1[cur].d,TO+u);
	if (K[cur] == 1) printf("added ");
	else printf("removed ");
	printf("%s %d\n",Month[d2[cur].m],d2[cur].d);
}

void Print()
{
	int ans = -1, end;
	fo(i,0,tot-1)
		if (f[N-1][i] > ans) ans = f[N-1][i], end = i;
	printf("%d\n",ans);
	if (ans != -1) print(N-1,end);
	if (T > 1) puts("");
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	Initialize();
	for (scanf("%d",&T);T;T --)
	{
		Reset();
		Work();
		Print();
	}
	return 0;
}
