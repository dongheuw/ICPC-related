#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
 
typedef long long LL;
char s[75];
int T,len;
LL f[75][10][2];
 
LL DFS(int pos,int pre,int up,bool lim)
{
    if (pos == len) return 1;
    LL &cur = f[pos][pre][up];
    if (!lim && cur != -1) return cur;
    LL ret = 0;
    int d = lim ? s[pos] - '0' : 9;
    fo(i,0,d)
    {
        if (up)
        {
            if (i >= pre) ret += DFS (pos+1,i,up,lim&&(i==d));
            else ret += DFS (pos+1,i,0,lim&&(i==d));
        } else if (i <= pre) ret += DFS (pos+1,i,0,lim&&(i==d));
    }
    if (!lim) cur = ret;
    return ret;
}
 
int main()
{
    freopen("e.in","r",stdin);
    freopen("e.out","w",stdout);
    for (scanf("%d",&T);T;T --)
    {
        scanf ("%s",s);
        len = strlen(s);
        int flag = -1;
        fo(i,1,len-1)
        {
            if (s[i] < s[i-1]) flag = 0;
            if (flag == 0 && s[i] > s[i-1])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1) puts ("-1");
        else
        {
            memset(f,255,sizeof f);
            printf("%lld\n",DFS(0,0,1,1)-1);
        }
    }
    return 0;
}
