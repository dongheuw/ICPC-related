#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 5005;
int n,a[maxn],c[maxn],v;
map<int,int> M;
vector<int> ans;

int main()
{
	while (scanf("%d",&n) != EOF)
	{
		ans.clear();
		M.clear();
		fo(i,0,n-1)
		{
			scanf("%d",&v);
			a[i] = -1;
			if (M.count(v)) a[M[v]] = i, c[i] = M[v];
			else c[i] = -1;
			M[v] = i;
		}
		for (int i = 0;i < n;)
		{
			int j = i + 1;
			while (j < n && c[j] == -1) j ++;
			if (j == n) break;
			else if (a[j] != -1) c[a[j]] = -1;
			int k = j + 1;
			while (k < n && c[k] == -1) k ++;
			if (k == n) break;
			else if (a[k] != -1) c[a[k]] = -1;
			ans.push_back(c[j]), ans.push_back(j);
			ans.push_back(c[k]), ans.push_back(k);
			for (;i <= k;i ++)
				if (a[i] != -1) c[a[i]] = -1;
		}
		sort(ans.begin(),ans.end());
		printf("%lu\n",ans.size()/4);
		for (unsigned i = 0;i < ans.size();i += 4)
			printf("%d %d %d %d\n",ans[i]+1,ans[i+1]+1,ans[i+2]+1,ans[i+3]+1);
		puts("");
	}

	return 0;
}
