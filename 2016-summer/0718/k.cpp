#include <bits/stdc++.h>

using namespace std;

const int MX = 1e2 + 5;

char s[MX][MX];
int vis[2][MX][MX],r,n;
struct Point {
    int x,y;
} P[MX];

bool left(int i,int tot) {
    int ret = 0,now = 0,cnt = 0;
    for(int j = 1;j <= n;j++) {
        if(s[i][j] > now) now = s[i][j],ret++;
        if(s[i][j]) cnt++;
    }
    if(cnt == n) return ret == tot;
    return ret <= tot;
}
bool right(int i,int tot) {
    int ret = 0,now = 0,cnt = 0;
    for(int j = n;j >= 1;j--) {
        if(s[i][j] > now) now = s[i][j],ret++;
        if(s[i][j]) cnt++;
    }
    if(cnt == n) return ret == tot;
    return 1;
}
bool top(int j,int tot) {
    int ret = 0,now = 0,cnt = 0;
    for(int i = 1;i <= n;i++) {
        if(s[i][j] > now) now = s[i][j],ret++;
        if(s[i][j]) cnt++;
    }
    if(cnt == n) return ret == tot;
    return ret <= tot;
}
bool foot(int j,int tot) {
    int ret = 0,now = 0,cnt = 0;
    for(int i = n;i >= 1;i--) {
        if(s[i][j] > now) now = s[i][j],ret++;
        if(s[i][j]) cnt++;
    }
    if(cnt == n) return ret == tot;
    return 1;
}
bool check(int i,int j,int t) {
    if(vis[0][i][t]) return 0;
    if(vis[1][j][t]) return 0;
    s[i][j] = t;
    if(s[i][0] && !left(i,s[i][0])) return s[i][j] = 0;
    if(s[i][n + 1] && !right(i,s[i][n + 1])) return s[i][j] = 0;
    if(s[0][j] && !top(j,s[0][j])) return s[i][j] = 0;
    if(s[n + 1][j] && !foot(j,s[n + 1][j])) return s[i][j] = 0;
    vis[0][i][t] = vis[1][j][t] = 1;
    return 1;
}
bool check_all() {
    for(int i = 0;i <= n + 1;i++) {
        for(int j = 0;j <= n + 1;j++) {
            s[i][j] = isdigit(s[i][j]) ? s[i][j] - '0' : 0;
            if(1 <= i && i <= n && 1 <= j && j <= n) {
                int t = s[i][j];
                if(t) {
                    if(vis[0][i][t]) return 0;
                    if(vis[1][j][t]) return 0;
                    vis[0][i][t] = vis[1][j][t] = 1;
                } else P[r].x = i,P[r].y = j,r++;
            }
        }
    }
    for(int i = 1;i <= n;i++) {
        if(s[i][0] && !left(i,s[i][0])) return 0;
        if(s[i][n + 1] && !right(i,s[i][n + 1])) return 0;
        if(s[0][i] && !top(i,s[0][i])) return 0;
        if(s[n + 1][i] && !foot(i,s[n + 1][i])) return 0;
    }
    return 1;
}
bool DFS(int c) {
    if(c == r) return 1;
    for(int x = 1;x <= n;x++) {
        if(!check(P[c].x,P[c].y,x)) continue;
        if(DFS(c + 1)) return 1;
        vis[0][P[c].x][x] = vis[1][P[c].y][x] = s[P[c].x][P[c].y] = 0;
    }
    return 0;
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        r = 0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i = 0;i <= n + 1;i++) scanf("%s",s[i]);
        if(!check_all() || !DFS(0)) printf("no\n\n");
        else {
            for(int i = 1;i <= n;i++) {
                for(int j = 1;j <= n;j++) printf("%d",(int)s[i][j]);
                printf("\n");
            }
            printf("\n");
        }
    }
    return 0;
}
