#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 100;
int n,c[maxn],opt[10][5];
vector<int> v[maxn],w[6];

bool cmp(int a,int b){ return c[a] < c[b]; }

int main()
{
	while (scanf("%d",&n) != EOF)
	{
		for (int i = 1;i <= 4;i ++) w[i].clear();
		int t,a,b;
		for (int i = 0;i < n;i ++)
		{
			scanf("%d%d",&t,&c[i]);
			v[i].resize(t);
			w[t].push_back(i);
			for (int j = 0;j < t;j ++) scanf("%d",&v[i][j]);
		}
		for (int i = 1;i <= 4;i ++) sort(w[i].rbegin(),w[i].rend(),cmp);
		t = a = b = 0;
		for (unsigned i = 0,ti = 0;i <= w[4].size();i ++)
		{
			for (unsigned j = 0,tj = ti;j <= w[3].size() && i + j <= 9;j ++)
			{
				vector<int> w2(w[2]);
				int tk = tj;
				if (i < (int)w[4].size()) w2.push_back(w[4][i]);
				if (j < (int)w[3].size()) w2.push_back(w[3][j]);
				sort(w2.rbegin(),w2.rend(),cmp);
				for (unsigned k = 0;k < w2.size() && k < 2 * (9 - i - j);k ++) tk += 2 * c[w2[k]];
				if (t < tk) a = i, b = j, t = tk;
				if (j < (int)w[3].size()) tj += 6 * c[w[3][j]];
			}
			if (i < (int)w[4].size()) ti += 12 * c[w[4][i]];
		}
		fill(opt[0],opt[9],0);
		for (int i = 0;i < a;i ++)
		{
			copy(v[w[4][i]].begin(),v[w[4][i]].end(),opt[i]);
			v[w[4][i]].clear();
		}
		if (a < (int)w[4].size()) w[2].push_back(w[4][a]);
		for (int i = 0;i < b;i ++)
		{
			copy(v[w[3][i]].begin(),v[w[3][i]].end(),opt[a + i]);
			v[w[3][i]].clear();
		}
		if (b < (int)w[3].size()) w[2].push_back(w[3][b]);
		sort(w[2].rbegin(),w[2].rend(),cmp);
		for (unsigned i = 0;i < w[2].size() && i < 2*(9-a-b);i ++)
		{
			copy(v[w[2][i]].begin(),v[w[2][i]].begin()+2,opt[a+b+i/2]+i%2*2);
			v[w[2][i]].erase(v[w[2][i]].begin(),v[w[2][i]].begin()+2);
		}
		for (int i = 1;i < n;i ++)
			v[0].insert(v[0].end(),v[i].begin(),v[i].end());
		for (int i = 0;i < 9;i ++)
			for (int j = 0;j < 4;j ++)
				if (opt[i][j] == 0 && !v[0].empty())
				{
					opt[i][j] = v[0].back();
					v[0].pop_back();
				}
		printf("%d\n",t);
		for (int i = 0;i < 9;i ++)
			printf("%d %d %d %d\n",opt[i][0],opt[i][1],opt[i][2],opt[i][3]);
		printf("\n");
	}
	return 0;
}
