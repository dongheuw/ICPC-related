#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
#define sz 10005
#define LL long long
int n,m,Q;
const LL inf = (LL)(1)<<50;
LL g[sz][sz];
int low[sz],dfn[sz],stack[sz],instack[sz],belong[sz],vis[sz],match[sz],id[sz];
LL ti[sz];
int top,deep,kinds;
vector<int>p[sz];
vector<int>q[sz];
void init(){
    memset(dfn,-1,sizeof(dfn));
    top = deep = kinds = 0;
}
void tarjan(int s){
    low[s]=dfn[s]=++deep;
    stack[++top]=s;
    instack[s]=1;
    for(int i=0;i<p[s].size();i++){
        int t = p[s][i];
        if(dfn[t]==-1){
            tarjan(t);
            low[s]=min(low[t],low[s]);
        }
        else if(instack[t]){
            low[s]=min(dfn[t],low[s]);
        }
    }
    if(dfn[s]==low[s]){
        int t;
        do{
            t=stack[top--];
            belong[t]=kinds;
            instack[t]=0;
        }while(s!=t);
        kinds++;
    }
}
void suo(){
    for(int i=0;i<kinds;i++)
        q[i].clear();
    for(int i=0;i<Q;i++){
        for(int j=0;j<p[i].size();j++){
            int t=p[i][j];
            if(belong[i]!=belong[t]){
                q[belong[i]].push_back(belong[t]);
                //cout<< belong[i] << " "<<belong[t]<<endl;
            }
        }
    }
}
int dfs(int s){
    for(int i=0;i<q[s].size();i++){
        int t= q[s][i];
        if(!vis[t]){
            vis[t]=1;
            if(match[t]==-1 || dfs(match[t])){
                match[t]=s;
                return 1;
            }
        }
    }
    return 0;
}
   
int solve(){
    int cnt=0;
    memset(match,-1,sizeof(match));
    for(int i=0;i<kinds;i++){
        memset(vis,0,sizeof(vis));
        cnt+=dfs(i);
    }
    return kinds - cnt - 1;
}   
int main(){
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        scanf("%d%d%d",&n,&m,&Q); 
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i==j)g[i][j]=0;
                else g[i][j]=inf;
            }
        }
        int s,t;
        long long v;
        while(m--){
            scanf("%d%d%I64d",&s,&t,&v);
            g[s][t]=g[t][s]=min(g[s][t],v);
        }
        for(int k=0;k<n;k++)
            for(int j=0;j<n;j++)
                for(int i=0;i<n;i++)
                    if(g[j][i]>g[j][k]+g[k][i])
                        g[i][j]=g[j][i]=g[j][k]+g[k][i];
        for(int i=0;i<Q;i++)
              scanf("%d%I64d",&id[i],&ti[i]);
        for(int i=0;i<Q;i++){
              p[i].clear();
            for(int j=0;j<Q;j++){
                if(i==j)continue;
                if(ti[i]<=ti[j] && g[id[i]][id[j]]<=ti[j]-ti[i])
                    p[i].push_back(j);
            }
        }
        init();
        for(int i=0;i<Q;i++)
            if(dfn[i]==-1)
                tarjan(i);
        suo();
        printf("Case %d: %d\n",cas,solve());
    }
}
