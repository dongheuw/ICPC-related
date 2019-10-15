#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 2000005;
char A[maxn],B[maxn];
int N,ans,nextA[maxn],nextB[maxn],extA[maxn],extB[maxn],f[maxn];
vector<int> p[maxn];

void Calc_next(char *s,int *next)
{
	next[0] = N;
	int pos,prev,j=-1;
	for (int i = 1;i < N;i ++,j --)
		if (j < 0 || i+next[i-prev] >= pos)
		{
			if (j < 0) j = 0, pos = i;
			while (pos < N && s[pos] == s[j]) pos ++,j ++;
			next[i] = j, prev = i;
		} else next[i] = next[i-prev];
}

void Extended_KMP(char *T,char *s,int *next,int *ext)
{
	Calc_next(T,next);
	int pos,prev,j=-1;
	for (int i = 0;i < N;i ++,j --)
		if (j < 0 || i+next[i-prev] >= pos)
		{
			if (j < 0) j = 0, pos = i;
			while (pos < N && j < N && s[pos] == T[j]) pos ++,j ++;
			ext[i] = j, prev = i;
		} else ext[i] = next[i-prev];
}

int Get(int x)
{
	int y = x,t;
	for (;y != f[y];y = f[y]);
	while (x != y) t = f[x], f[x] = y, x = t;
	return y;
}

int main()
{
	scanf("%d%s%s",&N,A,B);
	Extended_KMP(A,B,nextA,extB);
	Extended_KMP(B,A,nextB,extA);
	fo(i,0,N-1) f[i] = i, p[extB[i]].push_back(i);
	fo(i,0,N-1)
	{
		int j = Get(extA[i]);
		if (extB[j] >= i) ans = max(ans,i+j);
		for (vector<int>::iterator j = p[i].begin();j != p[i].end();j ++) f[*j] = Get(*j-1);
	}
	printf("%d\n",ans);
	return 0;
}
