#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int T;
char s[17][5],l[17][5];

int main()
{
	freopen("i.in","r",stdin);
	freopen("i.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		fo(i,1,16)
		{
			int t1,t2;
			char s1[5],s2[5];
			scanf("%s %s",s1+1,s2+1);
			scanf("%d%d",&t1,&t2);
			if (t1 < t2) fo(j,1,3) s[i][j] = s2[j], l[i][j] = s1[j];
			else fo(j,1,3) s[i][j] = s1[j], l[i][j] = s2[j];
		}
		fo(i,1,16)
		{
			bool champ = 1;
			fo(j,1,16)
			{
				bool sam = 1;
				fo(k,1,3)
					if (s[i][k] != l[j][k])
					{
						sam = 0;
						break;
					}
				if (sam)
				{
					champ = 0;
					break;
				}
			}
			if (champ)
			{
				printf("%s\n",s[i]+1);
				break;
			}
		}

	}
	return 0;
}
