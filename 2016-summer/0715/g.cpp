#include <bits/stdc++.h>
using namespace std;
const int mmax  = 2010;
const int inf = 0x3fffffff;

struct node
{
    int flow;
    int en;
    int next;
}E[100*mmax];
int p[mmax];
int num;
void init()
{
    memset(p,-1,sizeof p);
    num=0;
}
void add(int st,int en,int flow)
{
    E[num].en=en;
    E[num].flow=flow;
    E[num].next=p[st];
    p[st]=num++;
    E[num].en=st;
    E[num].flow=0;
    E[num].next=p[en];
    p[en]=num++;
}

int d[mmax];
int cur[mmax];
bool vis[mmax];
bool bfs(int st,int en)
{
    memset(vis,0,sizeof vis);
    d[st]=0;
    vis[st]=1;
    queue<int>q;
    q.push(st);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        for(int i=p[x]; i+1; i=E[i].next)
        {
            int v=E[i].en;
            if(!vis[v]&&E[i].flow)
            {
                vis[v]=1;
                d[v]=d[x]+1;
                q.push(v);
            }
        }
    }
    return vis[en];
}
int dfs(int st,int en,int  flow)
{
    if(st==en||flow==0)
        return flow;
    int f=0,dd;
    for(int &i=cur[st]; i+1;i=E[i].next)
    {
        int v=E[i].en;
        if(d[st]+1==d[v]&&(dd=dfs(v,en,min(flow,E[i].flow)))>0)
        {
            E[i].flow-=dd;
            E[i^1].flow+=dd;
            flow-=dd;
            f+=dd;
            if(flow==0)
                break;
        }
    }
    return f;
}
int dinic(int st,int en,int n)
{
    int flow=0;
    while(bfs(st,en))
    {
        for(int i=0;i<=n;i++)
            cur[i]=p[i];
        flow+=dfs(st,en,inf);
    }
    return flow;
}

vector<int>e[mmax];
int fg[mmax];
int w[mmax];
void dfs(int u)
{
    int SZ=e[u].size();
    for(int i=0;i<SZ;i++)
    {
        int v=e[u][i];
        if(d[v]==-1)
        {
            d[v]=d[u]^1;
            dfs(v);
        }
    }
}
int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        for(int i=0;i<mmax;i++)
            e[i].clear();
        for(int i=1;i<=n;i++)
            scanf("%d",&w[i]);
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&fg[i]);
            if(fg[i]==3)
                sum+=w[i];
        }
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d %d",&u,&v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        init();
        memset(d,-1,sizeof d);
        for(int i=1;i<=n;i++)
        {
            if(d[i]==-1)
            {
                d[i]=0;
                dfs(i);
            }
        }
        int st=0,en=2*n+1;
        for(int i=1;i<=n;i++)
        {
            if(d[i]==0)
            {
                if(fg[i]==1)
                    add(st,i,w[i]);
                if(fg[i]==2)
                    add(i,en,w[i]);
                if(fg[i]==3)
                {
                    add(st,i,w[i]);
                    add(i,i+n,inf);
                    add(i+n,en,w[i]);
                }
            }
            else
            {
                if(fg[i]==1)
                    add(i,en,w[i]);
                if(fg[i]==2)
                    add(st,i,w[i]);
                if(fg[i]==3)
                {
                    add(i,en,w[i]);
                    add(st,i+n,w[i]);
                    add(i+n,i,inf);
                }
            }
        }

        for(int u=1;u<=n;u++)
        {
            int Sz=e[u].size();
            for(int i=0;i<Sz;i++)
            {
                int v=e[u][i];
                if(d[u]==0 && d[v]==1)
                {
                    if( (fg[u]==fg[v]) &&   (fg[u]!=3) )
                    {
                        if(fg[u]==1)
                            add(u,v,inf);
                        else
                            add(v,u,inf);
                    }
                    else if(  (fg[u]==fg[v]) &&   (fg[u]==3)  )
                    {
                        add(u,v,inf);
                        add(v+n,u+n,inf);
                    }
                    else if(fg[u]==3 || fg[v]==3 )
                    {
                        if(fg[u]==3)
                        {
                            if(fg[v]==1)
                                add(u,v,inf);
                            else
                                add(v,u+n,inf);
                        }
                        if(fg[v]==3)
                        {
                            if(fg[u]==1)
                                add(u,v,inf);
                            else
                                add(v+n,u,inf);
                        }
                    }

                }
            }
        }
        printf("%d\n",dinic(st,en,en)-sum);
    }
    return 0;
}
