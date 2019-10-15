#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
#define pb push_back
#define mp make_pair
int lim;
const double eps = 1e-9;
bool gauss(double a[13][12], int n)
{
	int i, j, k, r;
	for (i = 0; i < n; i++) {
		r = i;
		for (j = i + 1; j < n; j++)
			if (fabs(a[j][i]) > fabs(a[r][i]))
				r = j;

		if (fabs(a[r][i]) < eps)
			return 0;

		if (r != i)
			for (j = 0; j <= n; j++)
				swap(a[r][j], a[i][j]);
		for (j = n; j >= i; j--)
			for (k = i + 1; k < n; k++)
				a[k][j] -= a[k][i] / a[i][i] * a[i][j];
	}
	for (i = n - 1; i >= 0; i--) {
		for (j = i + 1; j < n; j++)
			a[i][n] -= a[j][n] * a[i][j];
		a[i][n] /= a[i][i];
	}
	return 1;
}

map<string, int> idx, Right, Left;
char s[100005];
int tot;
string str[11];
vector<pair<string, double> > data[11];
double xs[12][12];
double ff[12][12];
double cs[12][12];
string cf[12];
double ans[12][12];
int n;
char tp[11111];

int main() {
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	int i, j;
	j = 0;
	while (scanf("%s", tp) != EOF) {
		str[n] = (string) tp;
		if (idx.find(tp) == idx.end())
			idx[tp] = tot++;
		scanf("%s", tp);
		gets(s);
		int len = strlen(s);
		bool op = 0;
		int num;
		xs[n][n] = 100;
		string tmp;
		for (i = 1; i < len; i++) {
			if (!op) {
				tmp.clear();
				for (j = i; s[j] != ' ' && j < len; j++)
					tmp += s[j];
				if (idx.find(tmp) == idx.end())
					idx[tmp] = tot++;
				i = j;
			} else {
				num = 0;
				for (j = i; s[j] != ' ' && j < len; j++)
					num = (num * 10) + s[j] - '0';
				data[n].pb(make_pair(tmp, num));
				i = j;
			}
			op ^= 1;
		}
		n++;
	}
	Right = idx;
	for (i = 0; i < n; i++)
		if (Right.count(str[i]))
			Right.erase(str[i]);
	map<string, int>::iterator it;
	for (it = Right.begin(); it != Right.end(); it++) {
		it->second = lim;
		cf[lim++] = it->first;
	}
	for (i = 0; i < n; i++)
		Left[str[i]] = i;

	for (i = 0; i < n; i++) {
		for (j = 0; j < (int) data[i].size(); j++) {
			if (Right.count(data[i][j].first)) {
				cs[i][Right[data[i][j].first]] += data[i][j].second;
			} else
				xs[i][Left[data[i][j].first]] -= data[i][j].second;
		}
	}
	for (i = 0; i < n; i++) {
		for (int x = 0; x < lim; x++) {
			for (j = 0; j < n; j++) {
					xs[j][n] = cs[j][x];
					memcpy(ff, xs, sizeof(ff));
					gauss(ff, n);
					for (int k = 0; k < n; k++)
						ans[k][x] = ff[k][n];

			}
		}
	}
	for (i = 0; i < n; i++) {
		printf("%s :", str[i].c_str());
		for (j = 0; j < lim; j++) {
			printf(" %s %.4f", cf[j].c_str(), ans[i][j]*100);
		}
		puts("");
	}

	return 0;

}
