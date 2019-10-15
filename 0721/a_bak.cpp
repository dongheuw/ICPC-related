#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>

using namespace std;

#define MAXN 1100

struct edge
{
	int p1,p2,next;
	double dis;
}edges[MAXN*MAXN];

int MSTHead[MAXN],en;
int n,set[MAXN];
double maxCost[MAXN][MAXN];
double x[MAXN],y[MAXN];
int p[MAXN];

void adds(int u,int v,double dis){
    edges[en].p1=u;
    edges[en].p2=v;
    edges[en].dis=dis;
    en++;
}

void addMST(int u,int v,double dis){
    edges[en].p1=u;
    edges[en].p2=v;
    edges[en].dis=dis;
    edges[en].next=MSTHead[u];
    MSTHead[u]=en++;
}

bool cmp(edge a,edge b){
	return a.dis<b.dis;
}

void init(int n){
	for(int i=0;i<=n;i++) set[i]=i;
}

int finds(int a)
{
	int root=a,temp;
	while(set[root]!=root) root=set[root];
	while(set[a]!=root){
		temp=a;
		a=set[a];
		set[temp]=root;
	}
	return root;
}

bool unions(int a,int b)
{
	int x=finds(a),y=finds(b);
	if(x==y) return false;
	set[x]=y;
	return true;
}

double kruskal()
{
    double ret=0;
    int m=en,num=0;
    memset(MSTHead,-1,sizeof(MSTHead));
	for(int i=0;i<m && num<n-1;i++){
		if(unions(edges[i].p1,edges[i].p2)){
			ret+=edges[i].dis;
			addMST(edges[i].p1,edges[i].p2,edges[i].dis);
			addMST(edges[i].p2,edges[i].p1,edges[i].dis);
			num++;
		}
	}
	return ret;
}


int vis[MAXN];
void getMaxCost(int u,int st,double mx){
    vis[u]=1;
    for(int i=MSTHead[u];i!=-1;i=edges[i].next){
            int v=edges[i].p2;
            if(vis[v]) continue;
            maxCost[st][v]=max(mx,edges[i].dis);
            getMaxCost(v,st,maxCost[st][u]);
    }
}


double getDist(int i,int j){
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

int main(){
    int t;
    scanf("%d",&t);
    for(int cs=0;cs<t;cs++){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%lf%lf%d",&x[i],&y[i],&p[i]);
        en=0;
        for(int i=0;i<n;i++)
            for(int j=0;j<i;j++){
                    double tmp=getDist(i,j);
                    adds(i,j,tmp);
            }
        init(n);
        sort(edges,edges+en,cmp);
        double ret=kruskal();
        double ans=0;
        for(int i=0;i<n;i++){
            memset(vis,0,sizeof(vis));
            getMaxCost(i,i,0);
        }
        for(int i=0;i<n;i++)
            for(int j=0;j<i;j++){
                    double A=p[i]+p[j];
                    double B=ret-maxCost[i][j];
                    ans=max(ans,A/B);
            }
        printf("%.2lf\n",ans);

    }
    return 0;
}
