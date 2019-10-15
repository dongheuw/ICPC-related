#include <cstdio>
#include <cstring>

int T,n,m,i,j,last;
char s[100005],p[5005],cur[5005];

int main()
{
    for (scanf("%d",&T);T;T --)
    {
        scanf("%d%d",&n,&m);
        scanf("%s%s",s+1,p+1);
        for (i = 1;i <= n-m+1;i ++)
        {
            cur[1] = p[1];
            last = -1;
            for (j = 1;j <= m;j ++)
                if (s[i+j-1] != cur[j])
                {
                    if (last == j-1 || j == m || s[i+j-1] != p[j+1]) break;
                    cur[j] = p[j+1];
                    cur[j+1] = p[j];
                    last = j;
                } else cur[j+1] = p[j+1];
            printf("%d",j > m);
        }
        for (i = n-m+2;i <= n;i ++) printf("0");
        printf("\n");
    }
    return 0;
}
