#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 13;

int n,tot,lim;
string str[maxn],cf[maxn],tmp;
vector< pair<string,double> > data[maxn];
char t[15],s[10005];
map<string,int> id,L,R;
double xs[maxn][maxn],cs[maxn][maxn],a[maxn][maxn],ans[maxn][maxn];

void Initialize()
{
	n = 0;
	while (scanf("%s",t) != EOF)
	{
		str[n] = (string)t;
		if (id.find(t) == id.end()) id[t] = tot ++;
		scanf("%s",t); gets(s);
		int len = strlen(s);
		bool Turn = 0;
		xs[n][n] = 100;
		fo(i,1,len-1)
		{
			int j;
			if (Turn)
			{
				int num = 0;
				for (j = i;s[j] != ' ' && j < len;j ++) num = num * 10 + s[j] - 48;
				data[n].push_back(make_pair(tmp,num));
			} else
			{
				tmp.clear();
				for (j = i;s[j] != ' ' && j < len;j ++) tmp += s[j];
				if (id.find(tmp) == id.end()) id[tmp] = tot ++;
			}
			i = j;
			Turn ^= 1;
		}
		n ++;
	}
	R = id;
	fo(i,0,n-1)
		if (R.find(str[i]) != R.end()) R.erase(str[i]);
	for (map<string,int>::iterator it = R.begin();it != R.end();it ++)
		it->second = lim, cf[lim] = it->first, lim ++;
	fo(i,0,n-1) L[str[i]] = i;
	fo(i,0,n-1)
		for (unsigned j = 0;j < data[i].size();j ++)
			if (R.find(data[i][j].first) != R.end())
				cs[i][R[data[i][j].first]] += data[i][j].second;
			else xs[i][L[data[i][j].first]] -= data[i][j].second;
}

void Work()
{
	fo(v,0,n-1)
		fo(x,0,lim-1)
			fo(p,0,n-1)
			{
				xs[p][n] = cs[p][x];
				memcpy(a,xs,sizeof a);
				fo(i,0,n-1)
				{
					int r = i;
					fo(j,i+1,n-1) if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
					if (r != i) fo(j,0,n) swap(a[r][j],a[i][j]);
					for (int j = n;j >= i;j --)
					fo(k,i+1,n-1) a[k][j] -= a[k][i] / a[i][i] * a[i][j];
				}
				for (int i = n-1;i >= 0;i --)
				{
					fo(j,i+1,n-1) a[i][n] -= a[j][n] * a[i][j];
					a[i][n] /= a[i][i];
				}
				fo(i,0,n-1) ans[i][x] = a[i][n];
			}
}

void Print()
{
	fo(i,0,n-1)
	{
		printf("%s :",str[i].c_str());
		fo(j,0,lim-1) printf(" %s %.4f",cf[j].c_str(),ans[i][j]*100);
		printf("\n");
	}
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	Initialize();
	Work();
	Print();
	return 0;
}
