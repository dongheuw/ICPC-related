#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define fd(i,a,b) for (int i = a;i >= b;i --)

using namespace std;

const int maxn = 300100;
const int maxm = 900010 * 2;

int fst[2][maxn],nxt[2][maxm],pnt[2][maxm],tot;
int ansl[maxn],ansr[maxn],nr,nl,real[maxn],rt;
bool inl[maxn],inr[maxn],ed[maxn];
int n,m,A,B;
int x[maxn],y[maxn],p[maxn];
 
bool cmp(const int &i, const int &j)
{
	return y[i] > y[j];
}

void add(int s, int t)
{
	pnt[0][++tot] = t;
	nxt[0][tot] = fst[0][s];
	fst[0][s] = tot;
	pnt[1][tot] = s;
	nxt[1][tot] = fst[1][t];
	fst[1][t] = tot;
}

void update(int k)
{
	if (k < nl) nl = k;
	if (k > nr) nr = k;
}
 
void bfs(bool *ed, int k, int l)
{
	static int q[maxn],qt,qh;
    qt = 0; qh = 1;
    fo(i,1,n) 
    	if (x[i] == k) 
    	{
    		q[++qt] = i;
    		ed[i] = 1;
    	}
    for (int now;qh <= qt;qh ++)
    {
    	now = q[qh];
    	for (int i = fst[l][now];i;i = nxt[l][i])
        	if (!ed[pnt[l][i]]) 
        		ed[pnt[l][i]] = 1, q[++qt] = pnt[l][i];
    }
}
 
void rdfs(int k)
{
    if (x[k] == A && inr[k]) update(real[k]);
    ed[k] = 1;
    for (int i = fst[0][k];i;i = nxt[0][i])
    	if (!ed[pnt[0][i]]) rdfs(pnt[0][i]);
}

void Initialize()
{
	scanf("%d%d%d%d",&n,&m,&A,&B);
    fo(i,1,n) scanf("%d%d",&x[i],&y[i]), p[i] = i;
    fo(i,1,m) 
    {
    	int l,r,mode;
		scanf("%d%d%d",&l,&r,&mode);
		if (mode == 1) add(l,r); 
		else add(l,r), add(r,l);
	}
    sort(p+1,p+1+n,cmp);
    bfs(inr,0,0);
    bfs(inl,A,1);
}

void Work()
{
	fo(i,1,n)
    	if (inr[p[i]] && x[p[i]] == A) 
    		real[p[i]] = ++rt;
    nr = 1;
    fo(i,1,n)
    	if (inl[p[i]] && !x[p[i]]) 
    		rdfs(p[i]), ansr[i] = nr;
    memset(ed,0,sizeof ed);
    nl = rt;
    fd(i,n,1)
    	if (inl[p[i]] && !x[p[i]]) 
    		rdfs(p[i]), ansl[i] = nl;
}

void Print()
{
    fo(i,1,n)
    	if (!x[p[i]]) printf("%d\n",inl[p[i]] ? (ansr[i]-ansl[i]+1) : 0);
}

int main()
{
    Initialize();
    Work();
    Print();
    return 0;
}
