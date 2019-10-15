#include <cstdio>
#include <cstring>
#include <map>
#define  fa(x) tr[x].fa
#define  ls(x) tr[x].son[0]
#define  rs(x) tr[x].son[1]
#define  sz(x) tr[x].sz
#define  v(x) tr[x].v
#define  son(x,w) tr[x].son[w]
#define  fr(i,x,y) for(i=x;i<=y;i++)
using namespace std;
typedef unsigned long long ULL;
const int maxn=(int)1e5+10;
struct Node{
	int fa,son[2],sz,v;
}tr[maxn];
int m,cnt,root;
map <ULL,int> Map;
char opt[20],name[40];
char names[maxn][40];
bool live[maxn];
void Update(int x){sz(x)=sz(ls(x))+sz(rs(x))+1;}
void Rotate(int x,bool w)
{
	int y=fa(x);
	fa(x)=fa(y);
	if(y==root)root=x;
	else son(fa(x),rs(fa(x))==y)=x;
	son(y,w^1)=son(x,w);
	fa(son(x,w))=y;
	son(x,w)=y;
	fa(y)=x;
	Update(y);
	Update(x);
}
void Splay(int x,int aim)
{
	while(fa(x)!=aim)
		if(fa(fa(x))==aim)Rotate(x,ls(fa(x))==x);
		else
			if(ls(fa(fa(x)))==fa(x))
				if(ls(fa(x))==x)
					Rotate(fa(x),1),Rotate(x,1);
				else
					Rotate(x,0),Rotate(x,1);
			else
				if(ls(fa(x))==x)
					Rotate(x,1),Rotate(x,0);
				else
					Rotate(fa(x),0),Rotate(x,0);
}
void Insert(int x,bool w, int y)
{
	son(x,w)=y;
	fa(y)=x;ls(y)=rs(y)=0;
	Splay(y,0);
}
void Insert(int y)
{
	int x=root;
	while(true)
		if(v(y)>v(x)||(v(y)==v(x)&&y<x))
			if(!ls(x))
			{
				Insert(x,0,y);
				break;
			}else x=ls(x);
		else
			if(!rs(x))
			{
				Insert(x,1,y);
				break;
			}else x=rs(x);
}
int Get(char ch)
{
	if('0'<=ch&&ch<='9')return ch-'0';
	if('a'<=ch&&ch<='z')return 10+ch-'a';
	return 10+26+ch-'A';
}
ULL Hash(char *s)
{
	ULL ret=0;
	for(;*s;s++)ret=ret*62+Get(*s);
	return ret;
}
void Issue()
{
	int len;
	scanf("%s",name+1);len=strlen(name+1);
	int &cun=Map[Hash(name+1)];
	if(cun==0)
	{
		cun=++cnt;
		live[cnt]=true;
		v(cnt)=0;
		memcpy(names[cnt]+1,name+1,len*sizeof(char));
		printf("CREATED %d 0\n",cnt-2);
		Insert(cnt);
	}else printf("EXISTS %d %d\n",cun-2,v(cun));
}
void Erase(int x)
{
	int y;
	Splay(x,0);
	for(y=ls(x);rs(y);y=rs(y));
	Splay(y,0);
	for(y=rs(x);ls(y);y=ls(y));
	Splay(y,root);
	ls(y)=0;
	Update(y),Update(root);
}
void Delete()
{
	scanf("%s",name+1);
	int &t=Map[Hash(name+1)];
	if(t&&live[t]){
		Erase(t);
		live[t]=false;
		printf("OK %d %d\n",t-2,v(t));
		t=0;
	}else printf("BAD REQUEST\n");
}
void Reliability()
{
	int v,x;
	scanf("%s%d",name+1,&v);
	x=Map[Hash(name+1)];
	if(x&&live[x])
	{
		Erase(x);
		v(x)+=v;
		Insert(x);
		printf("OK %d %d\n",x-2,v(x));
	}else printf("BAD REQUEST\n");
}
int Rank(int k)
{
	int x=root;
	while(true)
		if(sz(ls(x))+1==k)return x;
		else if(k<=sz(ls(x)))x=ls(x);
		else k-=sz(ls(x))+1,x=rs(x);
}
void Find()
{
	int k;
	scanf("%d",&k);k++;
	if(sz(root)==2){printf("EMPTY\n");return;}
	if(k>sz(root)-2)k=sz(root)-2;
	k=Rank(k+1);
	Splay(k,0);
	printf("OK %s %d %d\n",names[k]+1,k-2,v(k));
}
int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	scanf("%d",&m);
	Map.clear();
	root=1;
	rs(1)=m+2;sz(1)=2;v(1)=(1ll<<31)-1;
	fa(m+2)=1;sz(m+2)=1;v(m+2)=-(1ll<<31);
	live[1]=live[m+2]=true;
	cnt=1;
	while(m--)
	{
		scanf("%s",opt);
		if(opt[0]=='I')Issue();
		else if(opt[0]=='D')Delete();
		else if(opt[0]=='R')Reliability();
		else Find();
	}
}
