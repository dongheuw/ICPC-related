#include <cstdio>
#include <cstring>
#include <iostream>
#define  son(x,y) tr[x].son[y]
#define  cnt(x) tr[x].cnt
#define  fr(i,x,y) for(i=x;i<=y;++i)
#define  frd(i,x,y) for(i=x;i>=y;--i)
#define  frk(k,x,z) for(k=first[x];z=edge[k].y,k;k=edge[k].nxt)
using namespace std;
typedef long long LL;
const int maxn=100010;
const int bit=30;
struct Node{int son[2],cnt;}tr[maxn*(bit+1)];
struct Edge{int y,nxt;}edge[maxn];
LL ans,K;
int T,n,dfn_cnt,E_cnt,node_cnt,rt;
int root[maxn],fi[maxn],se[maxn],a[maxn],first[maxn];
int id[maxn];
bool is_root[maxn];
#define BUF_SIZE 100000
bool IOerror=false;
inline char nc()
{
	static char buf[BUF_SIZE],*p1=buf,*p2=buf;
	if(p1==p2)
	{
		p1=buf;
		p2=buf+fread(buf,1,BUF_SIZE,stdin);
		if(p1==p2)
		{
			IOerror=true;
			return -1;
		}
	}
	return *p1++;
}
bool blank(char ch){return ch==' '||ch=='\n'||ch=='\t'||ch=='\r';}
template <class T>
bool read(T &x)
{
	char ch;
	for(ch=nc();blank(ch);ch=nc());
	if(IOerror)return false;
	for(x=0;'0'<=ch&&ch<='9';ch=nc())x=x*10+ch-'0';
	return true;
}
void Insert(int x,int y)
{edge[++E_cnt]=(Edge){y,first[x]};first[x]=E_cnt;}
void Read()
{
	int i,x,y;
	read(n);read(K);
	fr(i,1,n)read(a[i]);
	memset(first+1,0,n*sizeof(int));E_cnt=0;
	memset(is_root+1,true,n*sizeof(bool));
	fr(i,2,n)
	{
		read(x);read(y);
		is_root[y]=false;
		Insert(x,y);
	}
	fr(i,1,n)if(is_root[i]){rt=i;break;}
}
void Dfs(int x)
{
	int k,y;
	fi[x]=++dfn_cnt;
	id[dfn_cnt]=x;
	frk(k,x,y)Dfs(y);
	se[x]=dfn_cnt;
}
void Pretreat()
{
	int i,j,v,x,y;
	dfn_cnt=0;
	Dfs(rt);
	node_cnt=0;
	fr(i,1,n)
	{
		root[i]=++node_cnt;
		v=a[id[i]];
		tr[x=root[i]]=tr[root[i-1]];
		frd(j,bit,1)
		{
			y=v>>(j-1)&1;
			tr[++node_cnt]=tr[son(x,y)];
			son(x,y)=node_cnt;
			x=son(x,y);
			cnt(x)++;
		}
	}
}
void Solve()
{
	int i,j,x1,x2,y,cur,v;
	ans=0;
	fr(i,1,n)
	{
		cur=id[i];
		if(a[cur]==0||K/a[cur]>1000000000)
		{
			ans+=se[cur]-fi[cur];
			continue;
		}
		v=K/a[cur];
		x1=root[fi[cur]];
		x2=root[se[cur]];
		frd(j,bit,1)
		{
			y=v>>(j-1)&1;
			if(y)ans+=cnt(son(x2,0))-cnt(son(x1,0));
			x1=son(x1,y);
			x2=son(x2,y);
		}
		ans+=cnt(x2)-cnt(x1);
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("j.in","r",stdin);
	freopen("j.out","w",stdout);
	read(T);
	while(T--)
	{
		Read();
		Pretreat();
		Solve();
	}
}
