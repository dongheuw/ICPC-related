#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

typedef long long LL;

int K,N,num[35],used[35],lnk[35][35],fxd[35],cnt[35];
int a[29][10] = {
	{},
	{1,2},
	{3,4,5,6,7},
	{8,9,10,11,12,13},
	{14,15,16,17,18},
	{19,20,21,22,23,24},
	{25,26,27,28,29},
	{30,31},
	{3,8},
	{1,4,9,14,19},
	{2,5,10,15,20,25},
	{6,11,16,21,26},
	{7,12,17,22,27,30},
	{13,18,23,28,31},
	{24,29},
	{19,25},
	{8,14,20,26,30},
	{3,9,15,21,27,31},
	{4,10,16,22,28},
	{1,5,11,17,23,29},
	{2,6,12,18,24},
	{7,13},
	{1,2,4,5,6,10,11},
	{3,4,8,9,10,14,15},
	{6,7,11,12,13,17,18},
	{14,15,19,20,21,25,26},
	{17,18,22,23,24,28,29},
	{10,11,15,16,17,21,22},
	{21,22,26,27,28,30,31}};

void cge(int x,int v)
{
	fo(i,1,cnt[x]) used[lnk[x][i]] ^= (1 << (v-1));
}

void dfs(int x)
{
	if (x == 32) {N --; return;}
	if (fxd[x]) {dfs(x+1); return;}
	int status = 0;
	fo(i,1,cnt[x]) status |= used[lnk[x][i]];
	fo(i,1,K)
	{
		if (!(status&(1<<(i-1))))
		{
			num[x] = i;
			cge(x,i);
			dfs(x+1);
			cge(x,i);
			if (N == 0) return;
		}
	}
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d",&K,&N);
	fo(j,1,28)
		fo(i,0,9)
		{
			if (a[j][i] == 0) break;
			cnt[a[j][i]] ++;
			lnk[a[j][i]][cnt[a[j][i]]] = j;
		}
	fo(i,1,31) scanf("%d",&num[i]);
	fo(i,1,31) if (num[i]){fxd[i] = 1; cge(i,num[i]);}
	dfs(1);
	if (N > 0) puts("No way");
	else 
	{
		puts("Found");
		fo(i,1,30) printf("%d ",num[i]);
		printf("%d\n",num[31]);
	}
	return 0;
}
