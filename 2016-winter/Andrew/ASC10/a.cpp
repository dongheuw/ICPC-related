#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>

using namespace std;
char str[100005];
int sub[100005],len,l,st,en;

bool match(int a,int b)
{
    return ((str[a]=='['&&str[b]==']')||(str[a]=='('&&str[b]==')'));
}
int main()
{
    while (gets(str))
    {
        stack<int> s;
        len = strlen(str);
        memset(sub,0,sizeof sub);
        s.push(0);
        for (int i = 1;i < len;i ++)
        {
            if (s.empty()) s.push(i);
            else
            if (match(s.top(),i))
            {
                sub[s.top()] = 1;
                sub[i] = 1;
                s.pop();
            }
            else s.push(i);                  
        }
        for (int i = st = en = l = 0;i < len;)
        {
            while (i < len && sub[i] == 0) i ++;
            int j = i;
            while (i < len && sub[i]) i ++;
            if (i - j > l) l = i - j, st = j, en = i;            
        } 
        for (int i = st;i < en;i ++) putchar(str[i]);
        printf("\n\n");
        getchar();
    }
    return 0;
}
