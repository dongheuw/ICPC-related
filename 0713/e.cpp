#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int n,a,b,num[3],req[3],cnt;
string s,ans;

int main()
{
    freopen("e.in","r",stdin);
    freopen("e.out","w",stdout);
    cin >> n >> a >> b;
    cin >> s;
    fo(i,0,s.size()-1) num[s[i]-'0'] ++;
    req[0] = a - num[0];
    req[1] = b - num[1];

    if (a+b > s.size() || n != s.size() || a+b > n)
    {
        cout << -1 << endl;
        return 0;
    }
    if (req[0] == 0 && req[1] == 0)
    {
        cout << 0 << endl;
        cout << s << endl;
        return 0;
    }

    ans = s;
    fo(i,0,n-1)
    {
        if (ans[i] == '0' && req[0] < 0)
        {
            if (req[1] > 0)
            {
                cnt ++;
                ans[i] = '1';
                req[1] --, req[0] ++;
            }
            else if (req[1] <= 0)
            {
                cnt ++;
                ans[i] = '2';
                req[0] ++;
            }
        }
	}

    fo(i,0,n-1)
    {
        if (ans[i] == '1' && req[1] < 0)
        {
            if (req[0] > 0)
            {
                cnt ++;
                ans[i] = '0';
                req[0] --, req[1] ++;
            }
            else if (req[0] <= 0)
            {
                cnt ++;
                ans[i] = '2';
                req[1] ++;
            }
        }
    }
    
    fo(i,0,n-1)
    {
	   if (ans[i] == '2')
       {
            if (req[0] > 0)
            {
                cnt ++;
                ans[i] = '0';
                req[0] --;
            }
            else if (req[1] > 0)
            {
                cnt ++;
                ans[i] = '1';
                req[1] --;
            }
        }
    }
    if (!(req[0] == 0 && req[1] == 0))
    {
        cout << -1 << endl;
        return 0;
    }
    cout << cnt << endl << ans << endl;
    return 0;
}
