#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

const int maxn = 100005;

int len,q;
long long fac[maxn],c[maxn][2];
char s[maxn],op[20];

inline int lowbit(int x){return x & -x;}

void Modify(int x,long long val,int id)
{
    for (;x <= len;x += lowbit(x))
        c[x][id] += val;
}

long long Query(int x,int id)
{
    long long ret = 0;
    for (;x;x -= lowbit(x)) ret += c[x][id];
    return ret;
}

int main()
{
    fac[0] = 1;
    fo(i,1,maxn) fac[i] = fac[i-1] * 27;
    while (scanf("%s",s) != EOF)
    {
        len = strlen(s);
        memset(c,0,sizeof c);
        fo(i,0,len-1)
        {
            Modify(i+1,(s[i]-'a'+1)*fac[i],0);
            Modify(i+1,(s[len-i-1]-'a'+1)*fac[i],1);
        }
        for (scanf("%d",&q);q;q --)
        {
            scanf("%s",op);
            if (op[0] == 'c')
            {
                int x; char ch;
                scanf("%d %c",&x,&ch);
                Modify(x,(ch-s[x-1])*fac[x-1],0);
                Modify(len-x+1,(ch-s[x-1])*fac[len-x],1);
                s[x-1] = ch;
            }
            else
            {
                int L,R;
                scanf("%d%d",&L,&R);
                long long a = (Query(R,0)-Query(L-1,0)) * fac[len-R];
                long long b = (Query(len-L+1,1)-Query(len-R,1)) * fac[L-1];
                if (a == b) puts("Yes"); else puts("No");
            }
        }
    }
    return 0;
}
