#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int n,m,k,v;
map< int,vector<int> > rec;

int main()
{
    while (scanf("%d%d",&n,&m) == 2)
    {
        rec.clear();
        fo(i,1,n)
        {
            int x;
            scanf("%d",&x);
            rec[x].push_back(i);
        }
        fo(i,1,m)
        {
           scanf("%d%d",&k,&v);
           if (rec[v].size() < k) printf("0\n");
           else printf("%d\n",rec[v][k-1]);
        }
    }
    return 0;

}
