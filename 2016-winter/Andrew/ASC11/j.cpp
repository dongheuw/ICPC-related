#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

int n,q,p,x,m[12],l[12];
vector<char> vs,vt;
map<vector<char>,string> s,t,tmp;

int main()
{
	while (scanf("%d%d%d",&n,&q,&p) != EOF)
	{
		vs.resize(n);
		vt.resize(n);
		for (int i = 0;i < n;i ++)
		{
			scanf("%d",&x);
			vs[i] = x - 1;
		}
		for (int i = 0;i < n;i ++)
		{
			scanf("%d",&x);
			vt[i] = x - 1;
		}
		for (int i = 0;i < p;i ++)
		{
			scanf("%d%d",&l[i],&m[i]);
			l[i] = n - l[i];
			m[i] = l[i] - m[i];
		}

		s.clear();
		s[vs] = "";
		for (int i = 0;i < q / 2;i ++)
		{
			tmp.clear();
			for (map<vector<char>,string>::iterator j = s.begin();j != s.end();j ++)
				for (int k = 0;k < p;k ++)
				{
					vector<char> v = j->first;
					rotate(v.begin(),v.begin()+m[k],v.begin()+l[k]);
					tmp[v] = j->second + (char)('1'+k);
				}
			s.swap(tmp);
		}

		t.clear();
		t[vt] = "";
		for (int i = 0;i < p;i ++) m[i] = l[i] - m[i];
		for (int i = 0;i < (q + 1) / 2;i ++)
		{
			tmp.clear();
			for (map<vector<char>,string>::iterator j = t.begin();j != t.end();j ++)
				for (int k = 0;k < p;k ++)
				{
					vector<char> v = j->first;
					rotate(v.begin(),v.begin() + m[k],v.begin() + l[k]);
					tmp[v] = j->second + (char)('1' + k);
				}
			t.swap(tmp);
		}
		string ans = "";
		for (map<vector<char>,string>::iterator i = s.begin();i != s.end();i ++)
			if (t.find(i->first) != t.end())
				ans = i->second+string(t[i->first].rbegin(),t[i->first].rend());
		if (ans == "") puts("Impossible");
		else for (int i = 0;i < q;i ++) printf(i==q-1?"%c\n":"%c ",ans[i]);
	}
	return 0;
}
