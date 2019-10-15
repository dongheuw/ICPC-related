#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 500005;
int N,M,pos0,posN1,root;
int A[maxn],pool[maxn];

struct NODE
{
	int lsum,rsum,rev,maxsum,sum,key,size,same;
	int c[2],father;
}tree[maxn];

void Initialize()
{
	for (int i = (int)5e5;i;i --) pool[++pool[0]] = i;
	scanf("%d%d",&N,&M);
	fo(i,1,N) scanf("%d",&A[i]);
}

void PushUp(int x)
{
	int l = tree[x].c[0], r = tree[x].c[1];
	if (l>0 && r>0)
	{
		int cl = max(0,tree[l].rsum), cr = max(0,tree[r].lsum);
		tree[x].size = tree[l].size + tree[r].size + 1;
		tree[x].lsum = max(tree[l].lsum,tree[l].sum+tree[x].key+cr);
		tree[x].rsum = max(tree[r].rsum,tree[r].sum+tree[x].key+cl);
		tree[x].maxsum = max(max(tree[l].maxsum,tree[r].maxsum),cl+tree[x].key+cr);
		tree[x].sum = tree[l].sum + tree[r].sum + tree[x].key;
	} else
	if (l>0)
	{
		int cl = max(0,tree[l].rsum);
		tree[x].size = tree[l].size + 1;
		tree[x].lsum = max(tree[l].lsum,tree[l].sum+tree[x].key);
		tree[x].rsum = tree[x].key + cl;
		tree[x].maxsum = max(tree[l].maxsum,tree[x].key+cl);
		tree[x].sum = tree[l].sum + tree[x].key;
	} else
	if (r>0)
	{
		int cr = max(0,tree[r].lsum);
		tree[x].size = tree[r].size + 1;
		tree[x].rsum = max(tree[r].rsum,tree[r].sum+tree[x].key);
		tree[x].lsum = tree[x].key + cr;
		tree[x].maxsum = max(tree[r].maxsum,tree[x].key+cr);
		tree[x].sum = tree[r].sum + tree[x].key;
	} else
	{
		tree[x].size = 1;
		tree[x].lsum = tree[x].rsum = tree[x].maxsum = tree[x].sum = tree[x].key;
	}
}

void PutRev(int x)
{
	if (x<0) return;
	tree[x].rev ^= 1;
	swap(tree[x].lsum,tree[x].rsum);
}

void PutSame(int x,int v)
{
	if (x<0) return;
	tree[x].key = tree[x].same = v;
	tree[x].sum = v * tree[x].size;
	tree[x].lsum = tree[x].rsum = tree[x].maxsum = max(tree[x].key,tree[x].sum);
}

void PushDown(int x)
{
	if (tree[x].rev)
	{
		PutRev(tree[x].c[0]);
		PutRev(tree[x].c[1]);
		swap(tree[x].c[0],tree[x].c[1]);
		tree[x].rev = 0;
	}
	if (tree[x].same != maxn)
	{
		PutSame(tree[x].c[0],tree[x].same);
		PutSame(tree[x].c[1],tree[x].same);
		tree[x].same = maxn;
	}
}

int MakeSplay(int l,int r,int father)
{
	int mid = (l + r) >> 1;
	int pos = pool[pool[0]--];
	tree[pos].size = 1;
	tree[pos].c[0] = tree[pos].c[1] = -maxn;
	tree[pos].same = maxn;
	tree[pos].rev = 0;
	tree[pos].key = A[mid];
	tree[pos].father = father;
	if (mid == 0) pos0 = pos;
	if (mid == N+1) posN1 = pos;
	if (l < mid) tree[pos].c[0] = MakeSplay(l,mid-1,pos);
	if (mid < r) tree[pos].c[1] = MakeSplay(mid+1,r,pos);
	PushUp(pos);
	return pos;
}

void rotate(int x,int d)
{
	int y = tree[x].c[d];
	int z = tree[y].c[!d];
	if (tree[x].father > 0)
	{
		int t = tree[x].father;
		int r = (tree[t].c[1] == x);
		tree[t].c[r] = y;
	}
	if (z > 0) tree[z].father = x;
	tree[x].c[d] = z;
	tree[y].father = tree[x].father;
	tree[x].father = y; tree[y].c[!d] = x;
	PushUp(x);
	PushUp(y);
}

int tank[maxn],dir[maxn];
void Splay(int x,int t)
{
	int cnt = 0;
	for (int i = x;i != tree[t].father;i = tree[i].father) tank[++cnt] = i;
	for (int i = cnt;i;i --) PushDown(tank[i]);
	fo(i,2,cnt) dir[i] = (tree[tank[i]].c[1] == tank[i-1]);
	for (int i = 2;i <= cnt;i += 2)
		if (i == cnt) rotate(tank[i],dir[i]);
		else
		{
			if (dir[i] == dir[i+1]) rotate(tank[i+1],dir[i+1]), rotate(tank[i],dir[i]);
			else rotate(tank[i],dir[i]), rotate(tank[i+1],dir[i+1]);
		}
	if (t == root) root = x;
}

int Select(int x,int v)
{
	int cur;
	PushDown(x);
	if (tree[x].c[0] > 0) cur = tree[tree[x].c[0]].size + 1; else cur = 1;
	if (cur == v) return x;
	if (v <= cur) return Select(tree[x].c[0],v);
	else return Select(tree[x].c[1],v-cur);
}

void INSERT()
{
	int posi,ctot;
	scanf("%d%d",&posi,&ctot);
	int pos = Select(root,posi+1), posnext = Select(root,posi+2);
	Splay(posnext,root);
	Splay(pos,tree[posnext].c[0]);
	fo(i,1,ctot) scanf("%d",&A[i]);
	tree[tree[root].c[0]].c[1] = MakeSplay(1,ctot,tree[root].c[0]);
	PushUp(tree[root].c[0]),PushUp(root);
}

void Dispose(int x)
{
	if (x<0) return;
	Dispose(tree[x].c[0]);
	Dispose(tree[x].c[1]);
	memset(&tree[x],0,sizeof tree[x]);
	pool[++pool[0]] = x;
}

int l,r,c,prel,sucr;
inline void Set(int l,int r)
{
	r = l + r - 1;
	int prel = Select(root,l), sucr = Select(root,r+2);
	Splay(sucr,root);
	Splay(prel,tree[sucr].c[0]);
}

void DELETE()
{
	scanf("%d%d",&l,&r);
	Set(l,r);
	int x = tree[root].c[0];
	Dispose(tree[x].c[1]);
	tree[x].c[1] = -maxn;
	PushUp(x),PushUp(root);
}

void MAKESAME()
{
	scanf("%d%d%d",&l,&r,&c);
	Set(l,r);
	int x = tree[root].c[0];
	PutSame(tree[x].c[1],c);
	PushUp(x),PushUp(root);
}

void REVERSE()
{
	scanf("%d%d",&l,&r);
	Set(l,r);
	int x = tree[root].c[0];
	PutRev(tree[x].c[1]);
	PushUp(x),PushUp(root);
}

void GETSUM(int cs)
{
	scanf("%d%d",&l,&r);
	if (!r) 
	{
		printf("0\n");
		return;
	}
	Set(l,r);
	int x = tree[root].c[0];
	printf("%d\n",tree[tree[x].c[1]].sum);
}

void MAXSUM()
{
	Splay(posN1,root);
	Splay(pos0,tree[root].c[0]);
	printf("%d\n",tree[tree[tree[root].c[0]].c[1]].maxsum);
}

void Work()
{
	root = MakeSplay(0,N+1,-1);
	fo(cs,1,M)
	{
		char op[10];
		scanf("%s",op);
		string s(op);
		if (s == "INSERT") INSERT();
		if (s == "DELETE") DELETE();
		if (s == "MAKE-SAME") MAKESAME();
		if (s == "REVERSE") REVERSE();
		if (s == "GET-SUM") GETSUM(cs);
		if (s == "MAX-SUM") MAXSUM();
	}
}

int main()
{
	Initialize();
	Work();
	return 0;
}
