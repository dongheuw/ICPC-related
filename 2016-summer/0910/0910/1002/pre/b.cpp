#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

int N,Q,A[MAXN];

int gcd(int a,int b) { ///TODO non-recursive
    int t;
    while(b)
    {
        t=a;
        a=b;
        b=t%b;
    }
    return a;
}

struct node {
    unordered_map<int,bool> gl,gr,gm;
    int ga;
    void clear() {
        gl.clear();
        gr.clear();
        gm.clear();
        ga=0;
    }
} T[MAXN*5];
int mn;


void mergenode(const node&a,const node&b,node&d) {
    node c;
    c.clear();
    c.ga=gcd(a.ga,b.ga);
    c.gl=a.gl;
    for (auto i:b.gl) c.gl[gcd(a.ga,i.first)]=true;
    c.gr=b.gr;
    for (auto i:a.gr) c.gr[gcd(b.ga,i.first)]=true;

    c.gm=a.gm;
    for (auto i:b.gm) c.gm[i.first]=true;
    for (auto i:a.gr) for (auto j:b.gl)
        c.gm[gcd(i.first,j.first)]=true;
    //cerr<<"::"<<a.gr.size()<<' '<<b.gl.size()<<' '<<' '<<c.gm.size()<<endl;
    d=c;
}
void build(int l,int r,int o) {
    mn=max(mn,o);
    if (l==r) {
        T[o].gl[A[l]]=T[o].gr[A[l]]=T[o].gm[A[l]]=true;
        T[o].ga=A[l];
        return;
    }
    int mid=(l+r)>>1;

    build(l,mid,o*2);
    build(mid+1,r,o*2+1);

    mergenode(T[o*2],T[o*2+1],T[o]);
}

node* ql[MAXN];
int ln;

void query(int l0,int r0,int l,int r,int o) {
    if (l0<=l&&r<=r0) {
        ql[ln++]=&T[o];
        return;
    }
    int mid=(l+r)>>1;
    if (l0<=mid) query(l0,r0,l,mid,o*2);
    if (mid<r0) query(l0,r0,mid+1,r,o*2+1);
}
int calc() {
    node tmp=*ql[0];
    for (int i=1;i<ln;i++) mergenode(tmp,*ql[i],tmp);
    return tmp.gm.size();
}

int main() {
    freopen("b.in","r",stdin);
    freopen("b.out","w",stdout);

    while (scanf("%d%d",&N,&Q)!=EOF) {
        for (int i=1;i<=N;i++)
            scanf("%d",&A[i]);
        build(1,N,1);
        cerr<<">>>"<<T[1].gm.size()<<' '<<T[1].gl.size()<<' '<<T[1].gr.size()<<endl;
        //for (;;);
        while (Q--) {
            //cerr<<"aaa"<<endl;
            int l,r;
            scanf("%d%d",&l,&r);
            ln=0;
            query(l,r,1,N,1);
            cerr<<"ln:"<<ln<<endl;
            printf("%d\n",calc());
        }

        for (int i=0;i<=mn;i++) T[mn].clear();
        mn=0;


    }
}
/*
5 3
1 3 4 6 9
3 5
2 5
1 5

5 3
1 3 4 6 9
1 2
1 3
1 4

6 4
5 4 6 12 8 24
1 2
2 4
3 5
1 6
*/
