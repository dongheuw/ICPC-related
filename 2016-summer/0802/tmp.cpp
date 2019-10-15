#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 11000;

typedef long long ll;
char A[MAXN],B[MAXN];
ll ha[MAXN],hb[MAXN];

ll pow29[MAXN];

int an[26],bn[26];

bool check(int x) {
    for (int i=1;i<=x;i++) {
        ll t = ((ha[x]-ha[i]*pow29[x-i]));
        if ((t*pow29[i]+ha[i])==hb[x]) return true;
    }
    return false;
}

int main () {
    pow29[0]=1;
    for (int i=1;i<=10000;i++) pow29[i]=pow29[i-1]*29;
    while (~scanf("%s%s",A+1,B+1)) {
        int N=strlen(A+1);
        for (int i=0;i<26;i++) an[i]=bn[i]=0;
        for (int i=1;i<=N;i++) {
            an[A[i]-'a']++;
            bn[B[i]-'a']++;

            ha[i]=(ha[i-1]*29+A[i]-'a');
            hb[i]=(hb[i-1]*29+B[i]-'a');

            bool flag=true;
            for (int j=0;j<26;j++) if (an[j]!=bn[j]) {
                flag=false;
                break;
            }
            if (flag) {
                flag=check(i);
            }
            putchar(flag+'0');
        }
        putchar('\n');
    }

}
