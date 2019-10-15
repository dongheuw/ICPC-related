#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
const int maxn = 2005;

int n,sig[maxn],a[maxn];

bool DemoQueue()
{
    queue<int> q;
    fo(i,0,n-1)
    {
        if (sig[i] == 1) q.push(a[i]);
        else
        {
            if (q.empty()) return 0;
            int v = q.front();  q.pop();
            if (a[i] != v) return 0;
        }
    }
    return 1;

}

bool DemoPriority()
{
    priority_queue<int > q;
    fo(i,0,n-1)
    {
        if (sig[i] == 1) q.push(a[i]);
        else
        {
            if (q.empty()) return 0;
            int v = q.top();  q.pop();
            if (a[i] != v) return 0;
        }
    }
    return 1;
}

bool DemoStack()
{
    stack<int> s;
    fo(i,0,n-1)
    {
        if (sig[i] == 1) s.push(a[i]);
        else
        {
            if (s.empty()) return 0;
            int v = s.top(); s.pop();
            if (a[i] != v) return 0;
        }
    }
    return 1;
}

int main()
{
    freopen("i.in","r",stdin);
    freopen("i.out","w",stdout);
    while (scanf("%d",&n) != EOF)
    {
        fo(i,0,n-1) scanf("%d%d",&sig[i],&a[i]);
        bool st = DemoStack(), qu = DemoQueue(), pr = DemoPriority();
        if (!st && !qu && !pr) printf("impossible\n");
        else if ((!st&&qu&&pr) || (!qu&&st&&pr) || (!pr&&qu&&st) || (pr&&qu&&st)) printf("not sure\n");
        else if (st) printf("stack\n");
        else if (qu) printf("queue\n");
        else if (pr) printf("priority queue\n");

    }
    return 0;
}
