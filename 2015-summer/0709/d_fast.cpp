#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

char a[6][10];
int n,list[105][2],row[6][4][2] = {{{1,5},{2,4},{3,3},{4,2}},{{2,2},{2,4},{2,6},{2,8}},{{1,5},{2,6},{3,7},{4,8}},{{4,2},{4,4},{4,6},{4,8}},
{{2,2},{3,3},{4,4},{5,5}},{{2,8},{3,7},{4,6},{5,5}}};
bool done,used[13];

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
	if (a[list[x][0]][list[x][1]] != 0) dfs(x+1);
	if (done) return;

	char temp[6][10];
	fo(i,1,5) fo(j,1,9) temp[i][j] = a[i][j];

	fo(i,1,12)
	{
		if (used[i]) continue;
		a[list[x][0]][list[x][1]] = 64 + i;
		used[i] = 1;
		bool good = 1;
		fo(k,0,5)
		{
			int cnt = 0, p = 0, sum = 0;
			fo(j,0,3)
				if (a[row[k][j][0]][row[k][j][1]] != 0) cnt ++, sum += a[row[k][j][0]][row[k][j][1]];
				else p = j;
			if (cnt == 3)
			{ 
				if (282 - sum >= 65 && 282 - sum <= 90 && !used[282-sum-64])
				{
					a[row[k][p][0]][row[k][p][1]] = 282 - sum;
					used[282-sum-64] = 1;
				}
				else
				{
					good = 0;
					break;
				}
			}
		}
		if (good) dfs(x+1);
		if (done) return;
		fo(i,1,12) used[i] = 0;
		fo(i,1,5) fo(j,1,9)
		{
			a[i][j] = temp[i][j];
			used[a[i][j]-64] = 1;
		}
	}
}

int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
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
