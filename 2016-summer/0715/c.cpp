#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 5000005;

char A[maxn],B[maxn],stk[maxn];
int pre[maxn],nxt[maxn];

int main()
{
    freopen("c.in","r",stdin);
    freopen("c.out","w",stdout);
    while(~scanf(" %s %s",B,A))
    {
        int lena = strlen(A), lenb = strlen(B);
        nxt[0] = nxt[1] = 0;
        for (int i = 2,j = 0;i < lenb;i ++)
        {
            while (j > 0 && B[j] != B[i-1]) j = nxt[j];
            if (B[j] == B[i-1]) j ++;
            nxt[i] = j;
        }
        for (int i = 0,j = 0,k = 0;i < lena;i ++,k ++)
        {
            stk[k] = A[i];
            while (j > 0 && A[i] != B[j]) j = nxt[j];
            if (A[i] == B[j]) j ++;
            if (j == lenb) k -= lenb, j = pre[k];
            stk[k+1] = 0, pre[k] = j;
        }
        puts(stk);
    }
    return 0;
}
