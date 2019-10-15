#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <string>
#include <map>

using namespace std;
#define For(i,l,r) for (int i = l; i <= r; ++i)
#define Cor(i,l,r) for (int i = l; i >= r; --i)
#define UPD(a,b,c,d,e) {\
	if ((a) < (b)) {\
		a = b;\
		pre[c][d] = e;\
	}\
}
		
int n, m, k; double c;
double price[111][111];
char name[111][111];
int Max[111], size[111];
double dp[2][111111];
short pre[111][111111];
map< vector<int>, int > Status;
vector<int> vec;
vector<int> List[1111111];
void dfs(int x, int sum) {
	if (x > n) {
		List[Status[vec] = Status.size()] = vec;
		return ;
	}
	For(j,0,min(k - sum, Max[x])) {
		vec.push_back(j);
		dfs(x + 1, sum + j);
		vec.pop_back();
	}
}

int go_inc[222222][11], go_dec[222222][11];
void getTransition() {
	For(i,1,Status.size()) {
		For(j,1,n) {
			++List[i][j - 1];
			if (Status.count(List[i])) go_inc[i][j] = Status[List[i]];
			--List[i][j - 1];
			--List[i][j - 1];
			if (Status.count(List[i])) go_dec[i][j] = Status[List[i]];
			++List[i][j - 1];
		}
	}
}

void getAns(int i, int j) {
	if (i == 0) return ;
	
	int mk = pre[i][j];
	if (mk != 0) {
		if (mk > 0) j = go_inc[j][mk]; else j = go_dec[j][-mk];
	}
	getAns(i - 1, j);
	//printf("%.2f\n", Map[make_pair(i, y)]);
	if (mk == 0) puts("HOLD");
	if (mk < 0) printf("BUY %s\n", name[-mk]);
	if (mk > 0) printf("SELL %s\n", name[mk]);
}

int main() {
	scanf("%lf%d%d%d", &c, &m, &n, &k);
	For(i,1,n) {
		scanf("%s %d %d", name[i], &size[i], &Max[i]);
		For(j,1,m) {
			scanf("%lf", &price[i][j]);
			price[i][j] *= size[i];
		}
	}
	dfs(1, 0);
	memset(go_inc, 0, sizeof(go_inc));
	memset(go_dec, 0, sizeof(go_dec));
	getTransition();
	vector<int> tmp(n, 0);
	For(i,0,Status.size()) dp[0][i] = -1e9;
	dp[0][Status[tmp]] = c;
	For(i,0,m - 1) {
		int cur = i & 1, nex = !cur;
		For(j,0,Status.size()) dp[nex][j] = -1e9;
		For(j,0,Status.size()) if (dp[cur][j] >= -1e-8) {
			UPD(dp[nex][j], dp[cur][j], i + 1, j, 0);
			For(k,1,n)  {
				if (go_inc[j][k] != -1 && dp[cur][j] + 1e-8 >= price[k][i + 1]) UPD(dp[nex][go_inc[j][k]], dp[cur][j] - price[k][i + 1], i + 1, go_inc[j][k], -k);
				if (go_dec[j][k] != -1) UPD(dp[nex][go_dec[j][k]], dp[cur][j] + price[k][i + 1], i + 1, go_dec[j][k], k);
			}
		}
	}
	double ans = dp[m & 1][Status[tmp]];
	printf("%.2f\n", ans);
	getAns(m, Status[tmp]);
	return 0;
}
