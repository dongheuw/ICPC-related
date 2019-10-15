#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int T,len;
vector<int> A;

int gcd(int x,int y)
{
	if (!y) return x; else return gcd(y,x%y);
}

void Preprocess()
{
	for (int y = 1;y <= 500;y ++)
		for (int x = y + 1;;x ++)
		{
			int a = 2 * x * y, b = x * x - y * y;
			if (a + b > 500000) break;
			int w = min(a,b), h = max(a,b);
			if (gcd(w,h) != 1) continue;
			A.push_back((w+h)*2);
		}
	sort(A.begin(),A.begin()+A.size());
}

int main()
{
	freopen("j.in","r",stdin);
	freopen("j.out","w",stdout);
	Preprocess();
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d",&len);
		int ans = 0;
		for (unsigned i = 0;i < A.size();i ++)
			if (A[i] <= len) ans ++, len -= A[i];
			else break;
		printf("%d\n",ans);
	}
	return 0;
}
