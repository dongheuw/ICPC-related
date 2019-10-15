#include <cstdio>
#include <cstring>
#include <algorithm>
#define  fr(i,x,y) for(i=x;i<=y;++i)
#define  frd(i,x,y) for(i=x;i>=y;--i)
#define  son(x,y) tr[x].son[y]
#define  pos(x) tr[x].pos
using std::min;
const int maxn=100010;
const int bit=30;
struct Node{int son[2],pos;}tr[maxn*(bit+1)];
int T,n,m,node_cnt;
int a[maxn],root[maxn];
#define  BUF_SIZE 100000
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
inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\t'||ch=='\r';}
template <class T>
inline bool read(T &x)
{
	char ch;
	for(ch=nc();blank(ch);ch=nc());
	if(IOerror)return false;
	for(x=0;'0'<=ch&&ch<='9';ch=nc())x=x*10+ch-'0';
	return true;
}
void Read()
{
	int i,j,x,y;
	read(n);
	fr(i,1,n)read(a[i]);
	root[n+1]=0;
	node_cnt=0;
	frd(i,n,1)
	{
		root[i]=++node_cnt;
		tr[x=root[i]]=tr[root[i+1]];
		frd(j,bit,1)
		{
			y=a[i]>>(j-1)&1;
			tr[++node_cnt]=tr[son(x,y)];
			son(x,y)=node_cnt;
			x=son(x,y);
			pos(x)=i;
		}
	}
}
int Query(int v,int p)
{
	int x=root[p],i,y,ret=n+1;
	frd(i,bit,1)
	{
		y=v>>(i-1)&1;
		if(y&&son(x,0))ret=min(ret,pos(son(x,0)));
		x=son(x,y);
	}
	if(x)ret=min(ret,pos(x));
	return ret;
}
void Solve()
{
	int l,r,x,v;
	read(m);
	while(m--)
	{
		read(l);read(r);
		x=l+1;
		v=a[l];
		while(x<=r)
		{
			v%=a[x];
			x=Query(v,x+1);
		}
		printf("%d\n",v);
	}
}
int main()
{
	freopen("h.in","r",stdin);
	freopen("h.out","w",stdout);
	read(T);
	while(T--)
	{
		Read();
		Solve();
	}
}
