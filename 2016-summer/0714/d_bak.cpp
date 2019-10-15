#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 100010;

char s[MAXN];
int sa[MAXN], height[MAXN], Rank[MAXN], c[MAXN], tmp[MAXN];
int n;

void makesa(int m) {
    memset(c, 0, m * sizeof(int));
    for(int i = 0; i < n; ++i) ++c[Rank[i] = s[i]];
    for(int i = 1; i < m; ++i) c[i] += c[i - 1];
    for(int i = 0; i < n; ++i) sa[--c[Rank[i]]] = i;
    for(int k = 1; k < n; k <<= 1) {
        for(int i = 0; i < n; ++i) {
            int j = sa[i] - k;
            if(j < 0) j += n;
            tmp[c[Rank[j]]++] = j;
        }
        int j = c[0] = sa[tmp[0]] = 0;
        for(int i = 1; i < n; ++i) {
            if(Rank[tmp[i]] != Rank[tmp[i - 1]] || Rank[tmp[i] + k] != Rank[tmp[i - 1] + k])
                c[++j] = i;
            sa[tmp[i]] = j;
        }
        memcpy(Rank, sa, n * sizeof(int));
        memcpy(sa, tmp, n * sizeof(int));
    }
}

void calheight() {
    for(int i = 0, k = 0; i < n; height[Rank[i++]] = k) {
        if(k > 0) --k;
        int j = sa[Rank[i] - 1];
        while(s[i + k] == s[j + k]) ++k;
    }
}

int logn[MAXN];
int best[20][MAXN];

void initRMQ() {
    logn[0] = -1;
    for(int i = 1; i <= n; ++i)
        logn[i] = (i & (i - 1)) == 0 ? logn[i - 1] + 1 : logn[i - 1];
    for(int i = 1; i <= n; ++i) best[0][i] = height[i];
    for(int i = 1; i <= logn[n]; ++i) {
        int ed = n - (1 << i) + 1;
        for(int j = 1; j <= ed; ++j)
            best[i][j] = min(best[i - 1][j], best[i - 1][j + (1 << (i - 1))]);
    }
}

int lcp(int a, int b) {
    a = Rank[a], b = Rank[b];
    if(a > b) swap(a, b);
    ++a;
    int t = logn[b - a + 1];
    return min(best[t][a], best[t][b - (1 << t) + 1]);
}

void solve() {
    int ans = 0, ansL = 1, ansR = 1;
    for(int i = 1; i < n - 1; ++i) if(s[i] < s[ans]) ans = i;
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j + i < n - 1; j += i) {
            int t = lcp(j, j + i), p = 0;
            if(t % i) {
                p = i - t % i;
                if(j < p) p = 0;
                t = max(t, lcp(j - p, j + i - p));
            }
            if(t / i + 1 > ansR || (t / i + 1 == ansR && Rank[j] < Rank[ans])) {
                ans = j - p;
                ansR = t / i + 1;
                ansL = ansR * i;
            }
        }
    }
    for(int i = 0; i < n - 1; ++i)
        if(lcp(i, i + ansL / ansR) >= ansL - ansL / ansR && Rank[i] < Rank[ans]) ans = i;
    for(int i = ans; i < ans + ansL; ++i) putchar(s[i]);
    puts("");
}

int main() {
    freopen("d.in","r",stdin);
    freopen("d.out","w",stdout);
    int kase = 0;
    while(scanf("%s", s) != EOF) {
        if(*s == '#') break;
        n = strlen(s) + 1;
        makesa(128);
        calheight();
        initRMQ();
        printf("Case %d: ", ++kase);
        solve();
    }
}
