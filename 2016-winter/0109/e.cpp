#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = (int)2e5 + 10;
char a[maxn],b[maxn];
int n,l,z,lim,cnt[26];

int cmp(const void *p,const void *q)
{
    char *w = (char*)p;
    char *u = (char*)q;
    return (*w-'a')-(*u-'a');
}

int main()
{
    while (scanf("%s",a) != EOF)
    {
        queue<int> Q;
        z = 0; l = strlen(a);
        memset(cnt,0,sizeof cnt);
        fo(i,0,l-1) cnt[a[i]-'a'] ++;
        int t = 0;
        fo(i,0,25)
            if (cnt[i] != 0)
            {
                if (cnt[i] >= 2)
                    while (cnt[i] > 1)
                    {
                        cnt[i] -= 2;
                        a[t] = i + 'a';
                        a[l-1-t] = i + 'a';
                        t ++, z += 2;
                    }
                if (cnt[i] == 1) Q.push(i);
            }
        while (!Q.empty())
        {
            int fr = Q.front(); Q.pop();
            if(z >=l ) break;
            while (cnt[fr] > 0)
            {
                cnt[fr] -= 2;
                a[t] = fr + 'a';
                a[l-1-t] = fr + 'a';
                t ++, z += 2;
                if (z > l) break;
            }
            if (z >= l) break;
        }
        if (l % 2 == 0) lim = l/2;
        else lim = (l-1)/2;
        fo(i,0,lim-1) b[i] = a[i];
        qsort(b,lim,sizeof(char),cmp);
        fo(i,0,lim-1) printf("%c",b[i]);
        if(l % 2 == 1) printf("%c",a[l/2]);
        for(int i = lim-1;i >= 0;i --) printf("%c",b[i]);
        printf("\n");
    }
    return 0;
}
