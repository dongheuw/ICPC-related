#include <stdio.h>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <math.h>
#include <string.h>
#include <queue>
#include <string>
#include <stdlib.h>
#include <algorithm>
#define LL long long
#define _LL __int64
#define eps 1e-8
#define PI acos(-1.0)
using namespace std;

const int maxn = 50000+10;

struct node
{
  int u,v,next;
}edge[maxn*2];

int cnt,head[maxn];
int n,I,R;

int son[maxn];//每个节点的儿子节点数目，这里包含该节点本身方便计算。
LL dp[maxn];//每个根节点的子节点到该节点的距离和
LL cost[maxn];//以每个节点为根的花费

void init()
{
  cnt = 0;
  memset(head,-1,sizeof(head));
}

void add(int u, int v)
{
  edge[cnt] = (struct node){u,v,head[u]};
  head[u] = cnt++;
}

void dfs(int u, int pre)
{
  dp[u] = 0;
  son[u] = 1;
  for(int i = head[u]; i != -1; i = edge[i].next)
  {
    int v = edge[i].v;
    if(v == pre) continue;
    dfs(v,u);

    son[u] += son[v]; //儿子数目
    dp[u] += dp[v] + son[v];//u到u的各个子节点的距离之和。
  }
}

void cal(int u, int pre)
{
  if(u != 1)
    cost[u] = cost[pre]+n-son[u]-son[u];
  for(int i = head[u]; i != -1; i = edge[i].next)
  {
    int v = edge[i].v;
    if(v == pre) continue;
    cal(v,u);
  }

}

int main()
{
  freopen("b.in","r",stdin);
  freopen("b.ans","w",stdout);
  int test;
  scanf("%d",&test);
  while(test--)
  {
    scanf("%d %d %d",&n,&I,&R);
    int u,v;
    init();
    for(int i = 0; i < n-1; i++)
    {
      scanf("%d %d",&u,&v);
      add(u,v);
      add(v,u);
    }
    //假设1为根节点
    dfs(1,0);

    memset(cost, 0, sizeof(cost));
    cost[1] = dp[1];
    cal(1,0);

    LL Min = cost[1];
    for(LL i = 2; i <= n; i++)
      Min = min(Min,cost[i]);

    cout << Min*I*I*R << endl;

    bool flag = false;
    for(LL i = 1; i <= n; i++)
    {
      if(cost[i] == Min)
      {
        if(flag == false)
        {
          flag = true;
          cout << i;
        }
        else cout << " " << i;
      }
    }
    cout << endl << endl;
  }
  return 0;
}
