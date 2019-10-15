#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define S(x) ((x)?((x)->size):0)
#define RAND(x) (double(rand())/RAND_MAX <= (x))

using namespace std;

const int maxn = 26000005;
int M,tail;

struct Node
{
	int size; Node *l,*r;
	char c; bool rev;
	Node(){}
	Node(char _c){c = _c,size = 1,l = r = 0,rev = 0;}
	Node(int _size,Node *_l,Node *_r,char _c,bool _rev){size = _size,c = _c,l = _l,r = _r,rev = _rev;}
}pool[maxn];
Node* root;

char GetOp()
{
	char ch;
	do ch = getchar(); while (ch < 'A' || ch > 'Z');
	return ch;
}

inline void PutRev(Node *x)
{
	swap(x->l,x->r);
	x->rev = 0;
	if (x->l)
	{
		pool[++tail] = Node(x->l->size,x->l->l,x->l->r,x->l->c,(x->l->rev)^1);
		x->l = &pool[tail];
	}
	if (x->r)
	{
		pool[++tail] = Node(x->r->size,x->r->l,x->r->r,x->r->c,(x->r->rev)^1);
		x->r = &pool[tail];
	}
}

inline void PushUp(Node *x)
{
	x->size = S(x->l) + S(x->r) + 1;
}

void Split(Node *x,int p,Node *&L,Node *&R)
{
	if (!x)
	{
		L = R = 0;
		return;
	}
	if (x->rev) PutRev(x);
	pool[++tail] = Node(x->c);
	Node *cur = &pool[tail];
	if (S(x->l) >= p)
	{
		Split(x->l,p,L,R);
		cur->l = R, cur->r = x->r;
		PushUp(cur);
		R = cur;
	} else
	{
		Split(x->r,p-S(x->l)-1,L,R);
		cur->l = x->l, cur->r = L;
		PushUp(cur);
		L = cur;
	}
}

Node *Merge(Node *L,Node *R)
{
	if (!L) return R;
	if (!R) return L;
	if (L->rev) PutRev(L);
	if (R->rev) PutRev(R);
	Node *cur;
	if (RAND((double)L->size/(L->size+R->size)))
	{
		pool[++tail] = Node(L->c);
		cur = &pool[tail];
		cur->l = L->l, cur->r = Merge(L->r,R);
		PushUp(cur);
	} else
	{
		pool[++tail] = Node(R->c);
		cur = &pool[tail];
		cur->l = Merge(L,R->l), cur->r = R->r;
		PushUp(cur);
	}
	return cur;
}

char Select(Node *x,int k)
{
	if (x->rev) PutRev(x);
	int size = S(x->l);
	if (k == size+1) return x->c;
	return k<=size ? Select(x->l,k):Select(x->r,k-size-1);
}

Node *A,*B,*C,*D;
void Insert()
{
	int x;char c;
	scanf("%d %c",&x,&c);
	Split(root,x,A,B);
	pool[++tail] = Node(c);
	root = Merge(A,Merge(&pool[tail],B));
}

void Delete()
{
	int l,r;
	scanf("%d%d",&l,&r);
	Split(root,r,A,B);
	Split(A,l-1,C,D);
	root = Merge(C,B);
}

void Copy()
{
	int l,r,x;
	scanf("%d%d%d",&l,&r,&x);
	Split(root,r,D,C);
	Split(D,l-1,A,B);
	Split(root,x,A,C);
	root = Merge(A,Merge(B,C));
}

void Reverse()
{
	int l,r;
	scanf("%d%d",&l,&r);
	Split(root,r,D,C);
	Split(D,l-1,A,B);
	if (B) B->rev ^= 1; 
	root = Merge(A,Merge(B,C));
}

void Query()
{
	int k;
	scanf("%d",&k);
	printf("%c",Select(root,k));
}

int main()
{
	freopen("editor.in","r",stdin);
	freopen("editor.out","w",stdout);
	scanf("%d",&M);
	fo(cs,1,M)
	{
		char op = GetOp();
		if (op == 'I') Insert();
		if (op == 'D') Delete();
		if (op == 'C') Copy();
		if (op == 'R') Reverse();
		if (op == 'Q') Query();
	}
	printf("\n");
	return 0;
}
