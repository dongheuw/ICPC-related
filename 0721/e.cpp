
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define N 408
#define M 10008
#define inf 0x7ffffff
vector<int>g[N];
int id[N], pre[N], low[N], s[N], stop, cnt, scnt;

void tarjan(int v, int n) {
    int t, minc = low[v] = pre[v] = cnt++;
    s[stop++] = v;
    for (int i = 0; i < g[v].size(); i++) {
        if (-1 == pre[g[v][i]]) tarjan(g[v][i], n);
        if (low[g[v][i]] < minc) minc = low[g[v][i]];
    }
    if (minc < low[v]) {
        low[v] = minc;
        return;
    }
    do {
        id[t = s[--stop]] = scnt;
        low[t] = n;
    } while (t != v);
    ++scnt;
}
int n, m;
int A[M], B[M], C[M];

bool _2sat() {
    stop = cnt = scnt = 0;
    memset(pre, -1, sizeof (pre));
    int nn = n * 2;
    for (int i = 0; i < nn; ++i) if (-1 == pre[i]) tarjan(i, nn);
    for (int i = 0; i < n; i++) if (id[i] == id[i + n]) return 0;
    return 1;
}

void add(int a, int b) {
    g[a].push_back(b);
}

void build(int mid) {
    for (int i = 0; i < N; i++) g[i].clear();
    int a, b, c;
    for (int i = 0; i < mid; i++) {
        a = A[i], b = B[i], c = C[i];
        switch (c) {
            case 0: add(a, b + n), add(b, a + n);
                break;
            case 1: add(a, b), add(b, a), add(a + n, b + n), add(b + n, a + n);
                break;
            case 2: add(b + n, a), add(a + n, b);
                break;
        }
    }
}

int main() {
    int tc;
    scanf("%d", &tc);
    while (tc--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++)
            scanf("%d%d%d", A + i, B + i, C + i);
        int l = 0, r = m, mid;
        while (l <= r) {
            mid = (l + r) >> 1;
            build(mid);
            if (_2sat()) l = mid + 1;
            else r = mid - 1;
        }
        printf("%d\n", l - 1);
    }
    return 0;
}
