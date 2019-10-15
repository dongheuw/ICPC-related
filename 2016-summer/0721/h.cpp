#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MaxN = 1007;
const int MaxM = 500007;

typedef pair<int,int> pir;

int T,n,m,x[MaxN],lup,ldown,sa,sb;
pir up[MaxM],down[MaxM],tmp;

inline int BinSdown(int d)
{
	int le,ri,mi; le = 1; ri = ldown;
	while(le<=ri)
	{
		mi = (le+ri)>>1;
		if(down[mi].first<d) le = mi+1;
		else ri = mi-1;
	}
	return down[le].second;
}

inline int BinSup(int d)
{
	int le,ri,mi; le = 1; ri = lup;
	while(le<=ri)
	{
		mi = (le+ri)>>1;
		if(up[mi].first<=d) le = mi+1;
		else ri = mi-1;
	}
	return up[le-1].second;
}

int main()
{
	freopen("1008.in","r",stdin);
	freopen("H.out","w",stdout);

	int i,j,a,b,l,r;

	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++)
			scanf("%d",x+i);
		lup = ldown = 0;
		for(i=1;i<=n;i++)
		{
			tmp.first = tmp.second = 0;
			for(j=i;j<=n;j++)
			{
				if(j&1) tmp.first += x[j];
				else tmp.second += x[j];
				if((i&1) && (j&1)) down[++ldown] = tmp;
				if((i&1) + (j&1) ==0 ) up[++lup] = tmp;
			}
		}
		sort(up+1,up+1+lup);
		sort(down+1,down+1+ldown);

		for(i=j=1;i<=lup;i++)
			if(up[i].first==up[j].first) up[j].second = up[i].second;
			else up[++j] = up[i];
		lup = 0;
		for(i=1;i<=j;i++)
		{
			if(up[lup].second<up[i].second)
				up[++lup] = up[i];
			//printf("%d %d  %d\n",up[i].first,up[i].second,lup);
		}

		for(i=j=1;i<=ldown;i++)
			if(down[i].first!=down[j].first)
				down[++j] = down[i];
		ldown = 0;
		for(i=1;i<=j;i++)
		{
			while(ldown>0)
				if(down[ldown].second>=down[i].second) ldown--;
				else break;
			down[++ldown] = down[i];
		}

		sa = down[ldown].first;
		sb = up[lup].second;
		/*
		for(i=1;i<=lup;i++) printf("%d %d\n",up[i].first,up[i].second);
		printf("\n");
		for(i=1;i<=ldown;i++) printf("%d %d\n",down[i].first,down[i].second);
		printf("\n");
		*/
		for(i=1;i<=m;i++)
		{
			scanf("%d%d",&a,&b);
			if(a>sa||b>sb) printf("0");
			else
			{
				l = BinSdown(a); r = BinSup(a);
				//printf("%d %d\n",l,r);
				if(l<=b&&b<=r) printf("1");
				else printf("0");
			}
			//printf("\n");
		}
		printf("\n");
	}
	return 0;
}
