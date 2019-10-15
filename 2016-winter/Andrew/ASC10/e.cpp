#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 64;
const char RANK[] = "6789TJQKA";

char a[maxn][3],trump;
int n,x[maxn],y[maxn],pre[maxn],mask;
bool flag[maxn],b[maxn][maxn];

bool canCover(const char a[],const char b[])
{
    if (a[1] == b[1]) return strchr(RANK,a[0]) < strchr(RANK,b[0]);
    else return b[1] == trump;
}

bool augment(int p)
{
    for (int i = 0;i < n;i ++)
        if ((y[i] & mask) != 0 && b[p][i] && !flag[i])
        {
            flag[i] = 1;
            if (pre[i] == -1 || augment(pre[i]))
            {
                pre[i] = p;
                return 1;
            }
        }
    return 0;
}

bool hungary()
{
    bool ret = 1;
    fill(pre,pre+n,-1);
    for (int i = 0;ret && i < n;i ++)
        if ((x[i] & mask) != 0)
        {
            fill(flag,flag+n,0);
            ret &= augment(i);
        }
    return ret;
}

int cnt(int n,int a[])
{
	int ret = 0;
	for (int i = 0;i < n;i ++)
		if ((a[i] & mask) != 0) ret ++;
	return ret;
}

int main()
{
    while (scanf("%d %c",&n,&trump) != EOF)
    {
        int k = (1 << 8) - 1;
        for (int i = 0;i < n;i ++)
        {
            scanf("%s",a[i]);
            x[i] = 1 << (strchr(RANK,a[i][0]) - RANK);
            if (a[i][2] == '*') k = x[i];
        }
        for (int j = 0;j < n;j ++)
        {
            scanf("%s",a[n]);
            y[j] = 1 << (strchr(RANK,a[n][0]) - RANK);
            for (int i = 0;i < n;i ++)
                b[i][j] = canCover(a[i],a[n]);
        }
        bool ans = 1;
        for (mask = 0;ans && mask < (1 << 9);mask ++)
            if ((k & mask) != 0 && cnt(n,x) <= cnt(n,y))
                ans &= !hungary();
        puts(ans?"TAKE":"COVER");
        puts("");
    }
    return 0;
}
