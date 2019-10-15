#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("b.in","w",stdout);
    int T=10;
    while (T--) {
        int N=9999,Q=9999;
        cout<<N<<' '<<Q<<endl;
        for (int i=1;i<=N;i++)
            cout<<rand()%999999+1<<' ';
        cout<<endl;
        while (Q--) {
            int l=rand()%N+1,r=rand()%N+1;
            if (l>r) swap(l,r);
            cout<<l<<' '<<r<<endl;
        }
    }
}
