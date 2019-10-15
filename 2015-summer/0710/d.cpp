#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 2000005;

char a[maxn],b[maxn],c[maxn];
int nex[maxn],exa[maxn],exb[maxn];
int N,M,pos = -1;

void getnex(char *s)
{
    int len = strlen(s),cur = 0;
    nex[0] = len;
    while (cur < len && s[cur] == s[cur+1]) cur ++;
    nex[1] = cur;cur = 1;
    for(int k = 2;k < len;k ++)
    {
        int p = cur + nex[cur] - 1, L = nex[k-cur];
        if(k + L -1 >= p)
        {
            int j = (p-k+1) > 0 ? (p-k+1):0;
            while (k + j < len && s[k+j] == s[j]) j ++;
            nex[k] = j;
            cur = k;
        } else nex[k] = L;
    }
}

void extkmp(char *a,char *b,int *ex)
{
    getnex(b);
    int l1 = strlen(a), l2 = strlen(b), cur = 0;
    while (cur < min(l1,l2) && a[cur] == b[cur]) cur ++;
    ex[0] = cur; cur = 0;
    for(int k = 1;k < l1;k++)
    {
        int p = cur + ex[cur] - 1,L = nex[k-cur];
        if(k + L -1 >= p)
        {
            int j = (p-k+1) > 0 ? (p-k+1) : 0;
            while(k + j < l1 && j < l2 && a[k+j] == b[j]) j ++;
            ex[k] = j;
            cur = k;
        } else ex[k] = L;
    }
}

int MinRepresent(char *s)
{
    int i = 0,j = 1,k = 0,len = strlen(s);
    int t;
    while (i < len && j < len && k < len)
    {
        t = s[(i+k)%len] - s[(j+k)%len];
        if (t == 0) k ++;
        else
        {
            if (t > 0) i += k + 1;
            else j += k + 1;
            if (i == j) j ++;
            k = 0;
        }
    }
    return min(i,j);
}

void Print()
{
    puts(c);
    for(int i = 0,j = pos;i < N;i++,j = (j+1)%N) putchar(a[j]);
    printf("\n");
}

void Work()
{
    extkmp(a,c,exa);

    reverse(a,a+2*N);
    reverse(c,c+M);
    extkmp(a,c,exb);

    reverse(exb,exb+2*N);
    reverse(c,c+M);
    reverse(a,a+2*N);

    fo(i,0,N-1)
        if (exa[i] == M || exa[i] + exb[i+M-1] == M-1)
        {
            if (pos == -1) pos = i;
            else if (min(i,N-i-1) < min(pos,N-pos-1)) pos = i;
        }
}

void Initialize()
{
    scanf("%d%d",&N,&M);
    scanf("%s%s",a,b);
    int start = MinRepresent(b);
    for(int i = 0,j = start;i < M;i ++,j = (j+1)%M) c[i] = b[j];
    c[M] = 0;
    for(int i = N;i < 2*N;i ++) a[i] = a[i-N];
    a[2*N] = 0;
}


int main()
{
    freopen("d.in","r",stdin);
    freopen("d.out","w",stdout);
    Initialize();
    Work();
    Print();
    return 0;
}
