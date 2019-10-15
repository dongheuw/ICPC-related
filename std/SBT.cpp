#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 1000000000

using namespace std;

const int maxn = 2000005;
int N,T,tot;
int left[maxn],right[maxn],size[maxn],key[maxn];

inline void L_rotate(int &t)
{
	int k = right[t];
	right[t] = left[k];
	left[k] = t;
	size[k] = size[t];
	size[t] = size[left[t]] + size[right[t]] + 1;
	t = k;
}

inline void R_rotate(int &t)
{
	int k = left[t];
	left[t] = right[k];
	right[k] = t;
	size[k] = size[t];
	size[t] = size[left[t]] + size[right[t]] + 1;
	t = k;
}

inline void maintain(int &t,bool flag)
{
	if (!flag)
	{
		if (size[left[left[t]]] > size[right[t]])
			R_rotate(t);
		else if (size[right[left[t]]] > size[right[t]])
			L_rotate(left[t]), R_rotate(t);
		else return;
	} else 
	{
		if (size[right[right[t]]] > size[left[t]])
			L_rotate(t);
		else if (size[left[right[t]]] > size[left[t]])
			R_rotate(right[t]), L_rotate(t);
		else return;
	}
	maintain(left[t],0);
	maintain(right[t],1);
	maintain(t,0);
	maintain(t,1);
}

inline void Insert(int &t,int v)
{
	if (!t)
	{
		t = ++ tot;
		size[t] = 1;
		left[t] = right[t] = 0;
		key[t] = v;
	} else 
	{
		size[t] ++;
		if (v < key[t]) Insert(left[t],v);
		else Insert(right[t],v);
		maintain(t,v >= key[t]);
	}
}

inline int Delete(int &t,int v)
{
	size[t] --;
	if ((key[t] == v) || (v < key[t] && !left[t]) || (v >= key[t] && !right[t]))
	{
		int ret = key[t];
		if (!left[t] || !right[t]) t = left[t] + right[t];
		else key[t] = Delete(left[t],key[t]+1);
		return ret;
	}
	if (v < key[t]) return Delete(left[t],v);
	else return Delete(right[t],v);
}

inline int Rank(int t,int v)
{
	if (!t) return 0;
	if (v <= key[t]) return Rank(left[t],v);
	else return size[left[t]] + 1 + Rank(right[t],v);
}

inline int Select(int t,int v)
{
	int temp = size[left[t]] + 1;
	if (temp == v) return key[t];
	if (v <= temp) return Select(left[t],v);
	else return Select(right[t],v-temp);
}

inline int Pred(int t,int v)
{
	if (!t) return INF;
	if (v <= key[t]) return Pred(left[t],v);
	else 
	{
		int temp = Pred(right[t],v);
		if (temp == INF) return key[t];
		else return temp;
	}
}

inline int Succ(int t,int v)
{
	if (!t) return INF;
	if (v >= key[t]) return Succ(right[t],v);
	else 
	{
		int temp = Succ(left[t],v);
		if (temp == INF) return key[t];
		else return temp;
	}
}

int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&N);
	while (N--)
	{
		int op,x;
		scanf("%d%d",&op,&x);
		if (op == 1) Insert(T,x);
		if (op == 2) Delete(T,x);
		if (op == 3) printf("%d\n",Rank(T,x)+1);
		if (op == 4) printf("%d\n",Select(T,x));
		if (op == 5) printf("%d\n",Pred(T,x));
		if (op == 6) printf("%d\n",Succ(T,x));
	}
	return 0;
}
