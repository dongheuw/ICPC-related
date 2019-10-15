#include<iostream>
#include<vector>
#include<queue>
#define inf 0x7ffffff
#define N 1005
using namespace std; 
struct node{
    int v,w,id; //id记录其为第几条边 
    node(int a,int b,int c){
        v=a;w=b;id=c;
    }
};
int d[N],q[N],path[N]; //q[i]记录最短路中第i个点用到的边，path记录最短路径 
bool vis[N],pre[50*N]; //pre[i]将第i条边暂时隐去 
int n,m;
vector<node>V[N];
bool flag; //求最短路与遍历最短路的开关 
void spfa()
{
    queue<int>Q;
    memset(vis,false,sizeof(vis));
    for(int i=0;i<=n;i++) d[i]=inf;
    d[0]=0;
    vis[0]=true;
    Q.push(0);
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        vis[u]=false;
        int n0=V[u].size();
        for(int i=0;i<n0;i++){
            int v=V[u][i].v;
            int w=V[u][i].w;
            int id=V[u][i].id;
            if(pre[id]) continue; //如果遍历到此边跳过 
            if(d[v]>d[u]+w){
                d[v]=d[u]+w;
                if(flag){
                    path[v]=u; q[v]=id;
                }
                if(!vis[v]){
                    Q.push(v);
                    vis[v]=true;
                }
            }
        }
    }  
}
int main(void)
{
    int t;
    int a,b,c;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;i++) V[i].clear();
        for(int i=0;i<m;i++){
            scanf("%d%d%d",&a,&b,&c);
            a--;b--;
            V[a].push_back(node(b,c,i));
            V[b].push_back(node(a,c,i));
        }
        flag=true;
        memset(pre,false,sizeof(pre));
        spfa();
        flag=false;
        if(d[n-1]==inf){
            puts("-1");continue;
        }
        int ans=inf;
        bool tflag=true;
        for(int i=n-1;i!=0;i=path[i]){
            pre[q[i]]=true;  //最短路边的开关 
            spfa();
            pre[q[i]]=false;
            if(d[n-1]==inf){
                ans=inf;break;
            }
            if(tflag){
                ans=d[n-1]; tflag=false;
            }else ans=max(ans,d[n-1]);
        }
        if(ans==inf) puts("-1");
        else printf("%d\n",ans);
    }
    return 0;
}
