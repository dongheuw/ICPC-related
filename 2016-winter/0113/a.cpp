#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAX_NUMBER = 1000001;
const long long MOD_NUMBER = 1000 * 1000 * 1000 + 7;

bool vis[MAX_NUMBER + 1];
long long ans[MAX_NUMBER];
long long fi[MAX_NUMBER];
int prime[MAX_NUMBER];
int prime_number;

int main() {
	fi[0] = 1;
	fi[1] = 1;
	for (int i = 2; i < MAX_NUMBER; i++) {
		fi[i] = (fi[i - 1] + fi[i - 2]) % MOD_NUMBER;
	}
	int number;
	memset(vis, 0, sizeof(vis));
	memset(ans, 0, sizeof(ans));
	scanf("%d", &number);
	for (long long i = 2; i <= number; i++) {
		if (!vis[i]) {
			ans[i] = fi[number - i];
			long long j = i + i;
			while (j <= number) {
				vis[j] = 1;
				long long temp = j;
				while (temp % i == 0) {
					ans[i] = (ans[i] + fi[number - j]) % MOD_NUMBER;
					temp /= i;
				}
				j += i;
			}
		}
	}
	long long result = 1;
	for (int i = 2; i <= number; i++) {
		if (!vis[i]) {
			result = (result * (ans[i] + 1)) % MOD_NUMBER;
		}
	}
	printf("%lld\n", result);
	return 0;
}
