#include<cstdio>  
#include<algorithm>  
#include<cstring>  
#include<queue>  
#include<vector>  
#define N 1010  
#define M 20010  
#define inf ((~(0ULL))>>1)  
using namespace std;  
typedef long long ll;  
int p[N];  
int n,Q;  
struct Edge{  
    int v,w,next;  
}edge[M*2];  
int head[N],cnt;  
int a[M],b[M];  
ll ans[M];  
  
ll dis[N];  
bool vis[N];  
  
void init(){  
    memset(head,-1,sizeof(head));  
    cnt=0;  
}  
void addedge(int u,int v,int w){  
    edge[cnt].v=v;  
    edge[cnt].w=w;  
    edge[cnt].next=head[u];  
    head[u]=cnt++;  
    edge[cnt].v=u;  
    edge[cnt].w=w;  
    edge[cnt].next=head[v];  
    head[v]=cnt++;  
}  
void spfa(int u){  
    int i;  
    queue<int>q;  
    memset(vis,0,sizeof(vis));  
    for(i=1;i<=n;i++)dis[i]=inf;  
    dis[u]=0,vis[u]=1;  
    q.push(u);  
    while(!q.empty()){  
        int s=q.front();  
        q.pop();  
        vis[s]=0;  
        for(i=head[s];i!=-1;i=edge[i].next){  
            int t=edge[i].v;  
            if(p[t]>p[u])continue;  
            if(dis[t]>dis[s]+edge[i].w){  
                dis[t]=dis[s]+edge[i].w;  
                if(!vis[t]){  
                    vis[t]=1;  
                    q.push(t);  
                }  
            }  
        }  
    }  
    for(i=1;i<=Q;i++)  
        if(dis[a[i]]!=inf && dis[b[i]]!=inf)  
            ans[i]=min(ans[i],dis[a[i]]+dis[b[i]]+p[u]);  
}  
int main(){  
    freopen("c.in","r",stdin);
    freopen("c.ans","w",stdout);
    int i,j,u,v,w;  
    int m;  
    while(scanf("%d %d",&n,&m)){  
        if(n==0 && m==0)break;  
        init();  
        for(i=1;i<=n;i++)scanf("%d",&p[i]);  
        for(i=1;i<=m;i++){  
            scanf("%d %d %d",&u,&v,&w);  
            addedge(u,v,w);  
        }  
        scanf("%d",&Q);  
        for(i=1;i<=Q;i++)scanf("%d %d",&a[i],&b[i]);  
        for(i=1;i<=Q;i++)ans[i]=inf;  
        for(i=1;i<=n;i++)spfa(i);  
        for(i=1;i<=Q;i++)  
            if(ans[i]==inf)printf("-1\n");  
            else printf("%lld\n",ans[i]);  
        puts("");  
    }  
    return 0;  
}  
