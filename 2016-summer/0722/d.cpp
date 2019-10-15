#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#define RAND(x) (double(rand())/RAND_MAX <= (x))

using namespace std;

const int maxn = 100005;

int n,Id;

struct Treap
{
	int id,sz;                
	Treap *l,*r;
	Treap(int id):id(id),sz(1),l(0),r(0){}
}*t;

map<string,int> ctd;
int reli[maxn];
string code,cd[maxn];

int GetSize(Treap *t)
{
	return t ? t->sz : 0;
}

void Update(Treap *&t)
{
	if (t) t->sz = GetSize(t->l) + GetSize(t->r) + 1;
}

void Merge(Treap *&t,Treap *l,Treap *r)
{
	if (!l) t = r;
	else if (!r) t = l;
	else
	if (RAND((double)l->sz/(l->sz+r->sz)))
	{
		Merge(l->r,l->r,r);
		t = l;
	} else
	{
		Merge(r->l,l,r->l);
		t = r;
	}
	Update(t);
}

bool cmp(int id1,int id2)
{
	if (reli[id1] != reli[id2]) return reli[id1] > reli[id2];
	return id1 < id2;
}

void Split(Treap *t,Treap *&l,Treap *&r,int x)
{
	if (!t) l = r = NULL;
	else
	{
		if (cmp(t->id,x))
		{
			Split(t->r,t->r,r,x);
			l = t;
		} else
		{
			Split(t->l,l,t->l,x);
			r = t;
		}
		Update(t);
	}
}     

void Delete(Treap *&t,int id)
{
	if (t->id == id) Merge(t,t->l,t->r);
	else if (cmp(t->id,id)) Delete(t->r,id);
	else Delete(t->l,id);
	Update(t);
}

int Rank(Treap *&t,int k)
{
	int impl = GetSize(t->l) + 1;
	if (k == impl) return t->id;
	if (k < impl) return Rank(t->l,k);
	return Rank(t->r,k - impl);
}

int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	ios::sync_with_stdio(0);
	for (cin >> n;n;n --)
	{
		string cmd;
		cin >> cmd;
		if (cmd[0] == 'I')
		{
			cin >> code;
			if (ctd.find(code) == ctd.end())
			{
				cout << "CREATED " << Id << " 0" << endl;
				ctd[code] = Id;
				Treap *L,*R;
				Split(t,L,R,Id);
				Merge(t,L,new Treap(Id));
				Merge(t,t,R);
				cd[Id++] = code;
			} else
			{
				int &id = ctd[code];
				cout << "EXISTS " << id << ' ' << reli[id] << endl;
			}
		} else if (cmd[0] == 'D')
		{
			cin >> code;
			if (ctd.find(code) == ctd.end()) cout << "BAD REQUEST" << endl;
			else
			{
				int &id = ctd[code];
				cout << "OK " << id << ' ' << reli[id] << endl;
				Delete(t,id);
				reli[id] = 0;
				ctd.erase(code);
			}
		} else if (cmd[0] == 'R')
		{
			int m;
			cin >> code >> m;
			if (ctd.find(code) == ctd.end()) cout << "BAD REQUEST" << endl;
			else
			{
				int &id = ctd[code];
				Delete(t,id);    
				reli[id] += m;
				Treap *L,*R;
				Split(t,L,R,id);
				Merge(t,L,new Treap(id));
				Merge(t,t,R);
				cout << "OK " << id << ' ' << reli[id] << endl;
			}
		} else
		{
			int m;
			cin >> m;
			m = min(m,GetSize(t)-1);
			if (m == -1) cout << "EMPTY" << endl;
			else
			{
				int id = Rank(t,m+1);
				cout << "OK " << cd[id] << ' ' << id << ' ' << reli[id] << endl;
			}
		}
	}
	return 0;
}
