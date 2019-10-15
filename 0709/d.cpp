#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

char a[6][10];
int n,list[105][2];
bool done,used[13],bz[100][100];

void dfs(int x)
{
	if (done) return;
	if (int(a[1][5]) + a[2][4] + a[3][3] + a[4][2] > 282) return;
	if (int(a[2][2]) + a[2][4] + a[2][6] + a[2][8] > 282) return;
	if (int(a[1][5]) + a[2][6] + a[3][7] + a[4][8] > 282) return;
	if (int(a[4][2]) + a[4][4] + a[4][6] + a[4][8] > 282) return;
	if (int(a[2][2]) + a[3][3] + a[4][4] + a[5][5] > 282) return;
	if (int(a[2][8]) + a[3][7] + a[4][6] + a[5][5] > 282) return;
	if (x > n)
	{
		bool ok = 1;
		if (int(a[1][5]) + a[2][4] + a[3][3] + a[4][2] != 282) ok = 0;
		if (int(a[2][2]) + a[2][4] + a[2][6] + a[2][8] != 282) ok = 0;
		if (int(a[1][5]) + a[2][6] + a[3][7] + a[4][8] != 282) ok = 0;
		if (int(a[4][2]) + a[4][4] + a[4][6] + a[4][8] != 282) ok = 0;
		if (int(a[2][2]) + a[3][3] + a[4][4] + a[5][5] != 282) ok = 0;
		if (int(a[2][8]) + a[3][7] + a[4][6] + a[5][5] != 282) ok = 0;
		if (ok) done = 1;
		return;
	}
	fo(i,1,12)
	{
		if (used[i]) continue;
		a[list[x][0]][list[x][1]] = 64 + i;
		used[i] = 1;
		dfs(x+1);
		if (done) return;
		used[i] = 0;
		a[list[x][0]][list[x][1]] = 0;
	}
}

int main()
{
	//freopen("d.in","r",stdin);
	//freopen("d.out","w",stdout);
	memset(a, 0, sizeof(a));
	fo(i,1,5) scanf("%s",a[i]+1);
	fo(i,1,5)
		fo(j,1,9)
			if (a[i][j] == 'x')
			{
				list[++n][0] = i;
				list[n][1] = j;
				a[i][j] = 0;
			} else if (a[i][j] == '.') a[i][j] = 0;
			else used[a[i][j]-64] = 1;
	done = 0;
	dfs(1);
	fo(i,1,5)
		fo(j,1,9) if (a[i][j] == 0) a[i][j] = '.';
	fo(i,1,5) printf("%s\n",a[i]+1);
	return 0;
}
