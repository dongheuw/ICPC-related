#include <cstdio>
#include <cstring>

struct Ans
{
    int x,y,l,r,t,b,s;
}tmp,ans;

char a[150][150],b[50][50];
int m1,n1,m2,n2,c[50],l[50],r[50];
bool flag;

int main()
{
    while (scanf("%d%d",&m1,&n1) != EOF)
    {
        memset(a,'#',sizeof a);
        for (int i = 0;i < m1;i ++) scanf("%s",a[50+i]+50);
        scanf("%d%d",&m2,&n2);
        for (int i = 0;i < m2;i ++) scanf("%s",b[i]);
        flag = 0;
        ans.s = 0;
        for (tmp.x = -m2 + 1;tmp.x < m1;tmp.x ++)
        {
            for (tmp.y = -n2 + 1;tmp.y < n1;tmp.y ++)
            {
                memset(c,0,sizeof c);
                for (int i = 0;i < m2;i ++)
                {
                    for (int j = 0;j < n2;j ++)
                        if (a[50+i+tmp.x][50+j+tmp.y] != b[i][j]) c[j] = 0;
                        else c[j] ++;
                    for (int j = 0;j < n2;j ++)
                    {
                        int k = j - 1;
                        while (k >= 0 && c[k] >= c[j]) k = l[k];
                        l[j] = k;
                    }
                    for (int j = n2 - 1;j >= 0;j --)
                    {
                        int k = j + 1;
                        while (k < n2 && c[k] >= c[j]) k = r[k];
                        r[j] = k;
                    }
                    for (int j = 0;j < n2;j ++)
                    {
                        tmp.l = l[j] + 1;
                        tmp.r = r[j];
                        tmp.t = i - c[j] + 1;
                        tmp.b = i + 1;
                        tmp.s = (tmp.r-tmp.l) * (tmp.b-tmp.t);
                        if (tmp.s > ans.s) ans = tmp;
                        else if (tmp.s == ans.s) flag = 1;
                    }
                }
            }
        }
        if (ans.s == 0) puts("0 0");
        else
        {
            printf("%d %d\n",ans.b-ans.t,ans.r-ans.l);
            printf("%d %d\n",ans.x+ans.t+1,ans.y+ans.l+1);
            printf("%d %d\n",ans.t+1,ans.l+1);
        }
    }
    return 0;
}
