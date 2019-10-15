/*
题意：

有绿宝石和蓝宝石。每一块绿宝石的体积为S1，价值为V1；每一块蓝宝石的体积为S2，价值为V2。

问N大小的背包，能装的最大价值。



分析：

看起来像背包的题，但是数据范围是int整型，所以不能使用背包。

考虑到只有两种物品，所有可以采用贪心+枚举的策略。

∵S1x+S2y<=N

设L = lcm(S1,S2)，有N = k * L + left。

对于L的空间，都可以用绿宝石和蓝宝石将这个空间放满，所以，一定全部放单位体积价值高的那种宝石。

用两物体将N填到不能填为止一定与 L+left的不能再填的状况相对应 ,即空出来的部分相对应 .

所以，将N分为俩部分，(k-1)*L与L+left

对于(k-1)*L的容量，贪心的放单位体积价值高的那种宝石。

对于L+left的容量，我们不能贪心的放，所以需要枚举一种宝石的数量，然后求出一个最大值。

需要注意的是，要枚举max(S1,S2)的那块宝石，否则会TLE

*/

#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>

#define LL __int64
#define mt(a,b) memset(a,b,sizeof(a))
using namespace std;

LL gcd(LL a,LL b) {
    return b?gcd(b,a%b):a;
}
LL lcm(LL a,LL b) {
    return a/gcd(a,b)*b;
}

int main() {
    int _;
    while(~scanf("%d",&_)) {
        int Cas = 0;
        LL n, s1, v1, s2, v2;
        while(_--) {
            scanf("%I64d%I64d%I64d%I64d%I64d",&n,&s1,&v1,&s2,&v2);
            LL l = lcm(s1,s2);
            LL k = n/l;
            LL first = (k-1) * l;
            LL second = n - first;

            LL ans = 0;
            if(v1*s2>v2*s1) {
                LL num = l / s1;
                ans += num * v1 * (k-1);
            } else {
                LL num = l / s2;
                ans += num * v2 * (k-1);
            }

            if(s1<s2) {
                swap(s1,s2);
                swap(v1,v2);
            }
            LL max_ans = 0;
            LL maxx = second / s1;
            for(LL x=0; x<=maxx; x++) {
                LL y = (second - (s1*x))/s2;
                max_ans = max(max_ans,v1*x+v2*y);
            }

            printf("Case #%d: %I64d\n",++Cas,ans+max_ans);

        }
    }

    return 0;
}
