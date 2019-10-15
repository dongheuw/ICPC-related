#include <bits/stdc++.h>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

int n,m,a[60][60],b[60][60];
bool done,ok;

void dfs(int x,int y)
{
	if (x > n)
	{
		bool check = 1;
		fo(i,1,n)
		{
			fo(j,i+1,n)
			{
				if (a[i][j] == 1)
				{
					bool have = 0;
					fo(k,1,m)
						if (b[i][k] && b[j][k])
						{
							have = 1;
							break;
						}
					if (!have)
					{
						check = 0;
						break;
					}
				} else
				{
					fo(k,1,m)
						if (b[i][k] && b[j][k])
						{
							check = 0;
							break;
						}
					if (!check) break;
				}
			}
			if (!check) break;
		}
		if (check) ok = 1;
		return;
	}
	b[x][y] = 1;
	if (y == m) dfs(x+1,1); else dfs(x,y+1);
	if (ok) return;
	b[x][y] = 0;
	if (y == m) dfs(x+1,1); else dfs(x,y+1);
	if (ok) return;
}

void dfs_link(int x,int y)
{
	if (x >= n)
	{
		ok = 0;
		dfs(1,1);
		if (!ok) done = 0;
		return;
	}
	a[x][y] = a[y][x] = 1;
	if (y == n) dfs_link(x+1,x+2); else dfs_link(x,y+1);
	if (!done) return;
	a[x][y] = a[y][x] = 0;
	if (y == n) dfs_link(x+1,x+2); else dfs_link(x,y+1);
	if (!done) return;
}

int main()
{
	freopen("g.in","r",stdin);
	freopen("g.out","w",stdout);
	for (n = 2;n <= 5;n ++)
	for (m = 1;m <= 50;m ++)
	if(n*m<=25)
	{
		done = 1;
		dfs_link(1,2);
		if (done)
		{
			printf("%d people use %d colors.\n",n,m);
			break;
		}
	}
	return 0;
}
