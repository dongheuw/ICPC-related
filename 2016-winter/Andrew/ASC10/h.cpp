#include <cstdio>
#include <cstring>
#include <algorithm>

int n;
char f[61][61][61][100];

void add(char *x,char *y)
{
    for (int i = 0;i < 99;i ++)
    {
        x[i] += y[i];
        x[i+1] += x[i]/10;
        x[i] %= 10;
    }
}

int main()
{
    memset(f,0,sizeof f);
    f[0][0][0][0] = 1;
    for (int A = 1;A <= 60;A ++)
        for (int B = 0;B <= A;B ++)
            for (int C = 0;C <= B;C ++)
            {
                if (A > B) add(f[A][B][C],f[A-1][B][C]);
                if (B > C) add(f[A][B][C],f[A][B-1][C]);
                if (C > 0) add(f[A][B][C],f[A][B][C-1]);
            }
    while (scanf("%d",&n) != EOF)
    {
        int i = 99;
        while (f[n][n][n][i] == 0) i --;
        while (i >= 0) printf("%d",f[n][n][n][i--]);
        printf("\n\n");
    }
    return 0;
}
  
