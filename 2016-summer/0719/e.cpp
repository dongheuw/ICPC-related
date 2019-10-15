#include <bits/stdc++.h>
using namespace std;
const int MAXE = 1000010,MAXN = 10010,INF = 0x7fffffff>>2;

struct graph{
    struct edge{
        int t,n,v,f;
    } E[MAXE];
    int st[MAXN],en,vn,cur[MAXN],vis[MAXN],d[MAXN];
    
    graph() {en=1;}

    void clear() {
        en=1;
        for (int i=1;i<=vn;i++) st[i]=d[i]=0;
        vn=0;
    }
    void ade(int a,int b,int v) {
        vn=max(vn,max(a,b));
        E[++en]=(edge){b,st[a],v,0};
        st[a]=en;
        E[++en]=(edge){a,st[b],v,v};
        st[b]=en;
    }

    int S,T;queue<int> Q;

    bool BFS() {
        for(int i=1;i<=vn;i++) {vis[i]=0;cur[i]=st[i];}
        Q.push(S);
        vis[S]=1;d[S]=0;
        while (!Q.empty()) {
            int f=Q.front();Q.pop();
            for (int i=st[f];i;i=E[i].n) if (!vis[E[i].t]&&(E[i].v-E[i].f)) {
                d[E[i].t]=d[f]+1;
                vis[E[i].t]=1;
                Q.push(E[i].t);
            }
        }
        return vis[T];
    }

    int DFS(int x,int flow) {
        if (x==T||!flow) return flow;
        int t,res=0;
        for (int&i=cur[x];i;i=E[i].n)
            if (d[E[i].t]==d[x]+1&&(t=DFS(E[i].t,min(flow,E[i].v-E[i].f)))) {
                res+=t;
                E[i].f+=t;
                E[i^1].f-=t;
                flow-=t;
                if (!flow) return res;
            }
        return res;
    }

    int maxflow(int s,int t) {
        S=s;T=t;int res=0;
        while (BFS()) res+=DFS(S,INF);
        return res;
    }
} G;

bool sober[10][10];

int N,M,perm[10];
bool vis[10000009];
const int MOD = 1e7+9;
int main ()
{   
    //freopen("1005.in","r",stdin);
    //freopen("1005_test.out","w",stdout);
    while (cin>>N>>M)
    {      
        memset(vis,0,sizeof vis);
        if (!N) {
            cout<<0<<endl;
            continue;
        }
        memset(sober,0,sizeof sober);

        for (int i=0,u,v; i<M; i++)
        {
            scanf("%d%d",&u,&v);
            sober[u][v]=true;
        }

        for (int i=1; i<=N; i++)
        {
            perm[i-1]=i;
        }
        int ans=INF;
        do
        {
            G.clear();
            int S=2*N+1,T=2*N+2;
            long long ha=0;
            for (int i=1; i<=N; i++)
            {
                G.ade(S,i,1);
                G.ade(i+N,T,1);
                int tmp=0;
                for (int j=1; j<=N; j++)
                    if (sober[i][perm[j-1]]||sober[i][perm[j%N]]) {
                        tmp+=1<<(j-1);
                    }
                    else 
                        G.ade(i,j+N,1);
                ha=ha*512+tmp;
                ha%=MOD;
            }
            if (vis[ha]) continue;
            vis[ha]=true;
            ans=min(ans,N-G.maxflow(S,T));
        } while (next_permutation(perm,perm+N-1));
        cout<<ans<<endl;

    }
}
