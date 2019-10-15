#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int T,cas,a[15];

int main()
{
    scanf("%d",&T);
    while (T --)
    {
        scanf("%d",&cas);
        fo(i,0,9) scanf("%d",&a[i]);
        sort(a,a+10);
        printf("%d %d\n",cas,a[7]);
    }
    return 0;
}
