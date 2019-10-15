#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxlen = 1005;

int N,M,K,brick[11],scheme[21][21],p[11];
bool v[maxlen];

vector<int> block;
map< vector<int>,int > rec;

void putschemerow(int r,int c,int b)
{
	int zz[27] = {0};
	fo(i,c,c+b-1)
	{
		if (r > 0) zz[scheme[r-1][c]] = 1;
		if (r + 1 < N) zz[scheme[r+1][c]] = 1;
	}
	if (c + b < M) zz[scheme[r][c+b]] = 1;
	if (c > 0) zz[scheme[r][c-1]] = 1;
	fo(i,1,25)
		if (zz[i] == 0)
		{
			fo(j,c,c+b-1) scheme[r][j] = i;
			break;
		}
}

void putschemecol(int r,int c,int b)
{
	int zz[27] = {0};
	fo(i,r,r+b-1)
	{
		if (c > 0) zz[scheme[i][c-1]] = 1;
		if (c + 1 < M) zz[scheme[i][c+1]] = 1;
	}
	if (r > 0) zz[scheme[r-1][c]] = 1;
	if (r + b < N) zz[scheme[r+b][c]] = 1;
	fo(i,1,25)
		if (zz[i] == 0)
		{
			fo(j,r,r+b-1) scheme[j][c] = i;
			break;
		}
}

void fill(vector<int> &t,int r)
{
	t.clear();
	t.push_back(r);
	for (;r < N && p[r];r ++) t.push_back(p[r]);
}

bool dfs(int r)
{
	for (;r < N && p[r] == ((1<<M)-1);r ++);
	if (r >= N) return 1;
	vector<int> tmp;
	fill(tmp,r);
	if (rec[tmp]) return 0;

	int z = (~p[r]) & ((1<<M)-1);
	int cs = __builtin_ctz(z);
	int cn = 0;
	for (int i = 1 << cs;i & z;i <<= 1, cn ++);
	int rn = N - r;
	for (int i = 0;i < block.size();i ++)
	{
		int b = block[i];
		if (b <= cn)
		{
			p[r] |= (((1<<b)-1) << cs);
			if (dfs(r))
			{
				putschemerow(r,cs,b);
				return 1;
			}
			fill(tmp,r);
			rec[tmp] = 1;
			p[r] ^= (((1<<b)-1) << cs);
		}
		if (b <= rn)
		{
			for (int j = r;j < r + b;j ++) p[j] |= (1 << cs);
			if (dfs(r))
			{
				putschemecol(r,cs,b);
				return 1;
			}
			fill(tmp,r);
			for (int j = r;j < r + b;j ++) p[j] ^= (1 << cs);
		}
	}
	return 0;
}

void Initialize()
{
	scanf("%d%d%d",&N,&M,&K);
	fo(i,0,K-1) scanf("%d",&brick[i]);
	sort(brick,brick+K);
	v[0] = 1;
	fo(i,0,K-1)
	{
		if (!v[brick[i]])
		{
			fo(j,0,1000-brick[i])
				if (v[j]) v[j+brick[i]] = 1;
		} else brick[i] = 0;
	}
	fo(i,0,K-1)
		if (brick[i] && brick[i] <= max(N,M)) block.push_back(brick[i]);
}

void Work()
{
	bool r = 0;
	if (N > M) swap(N,M), r = 1;
	fo(i,0,19)
		fo(j,0,19) scheme[i][j] = 26;
	if (dfs(0))
	{
		puts("YES");
		if (!r)
			fo(i,0,N-1)
			{
				fo(j,0,M-1) printf("%c",96+scheme[i][j]);
				printf("\n");
			}
		else
			fo(i,0,M-1)
			{
				fo(j,0,N-1) printf("%c",96+scheme[j][i]);
				printf("\n");
			}
	} else puts("NO");
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	Initialize();
	Work();
	return 0;
}
