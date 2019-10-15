#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;
#define LL long long
const int maxn=200010;
int N,test;
LL K,res;
int temp[maxn],tempran[maxn],ran[maxn],sa[maxn],tsa[maxn],height[maxn];
int p[maxn];
char s[maxn];
void getran(int x){
	tempran[sa[1]]=1;
	for (int i=2;i<=N;i++)
		if ((ran[sa[i]]==ran[sa[i-1]])&&(ran[sa[i]+x]==ran[sa[i-1]+x]))
			tempran[sa[i]]=tempran[sa[i-1]];
		else tempran[sa[i]]=tempran[sa[i-1]]+1;
	memcpy(ran,tempran,sizeof(ran));
}
void work(int x){
	memset(temp,0,sizeof(temp));
	for (int i=1;i<=N;i++)temp[ran[i+x]]++;
	for (int i=1;i<maxn;i++)temp[i]+=temp[i-1];
	for (int i=N;i;i--)tsa[temp[ran[i+x]]--]=i;
	memset(temp,0,sizeof(temp));
	for (int i=1;i<=N;i++)temp[ran[i]]++;
	for (int i=1;i<maxn;i++)temp[i]+=temp[i-1];
	for (int i=N;i;i--)sa[temp[ran[tsa[i]]]--]=tsa[i];
	getran(x);
}
void getheight(){
	int i,j,k=0;
	for (i=1;i<=N;height[ran[i++]]=k)
		for (k?--k:0,j=sa[ran[i]-1];s[i+k]==s[j+k];k++);
}
LL check(int mid){
	LL res=0;
	for (int i=1;i<=mid;i++)res+=N-sa[i]+1;
	int Min=height[mid+1];
	for (int i=mid+1;i<=N;i++){
		res+=Min;
		Min=min(Min,height[i+1]);
		if (!Min)break;
	}
	return res;
}
int main(){
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	scanf("%d\n",&test);
	for (int tt=1;tt<=test;tt++){
		memset(sa,0,sizeof(sa));
		memset(tsa,0,sizeof(tsa));
		memset(ran,0,sizeof(ran));
		memset(temp,0,sizeof(temp));
		memset(tempran,0,sizeof(tempran));
		memset(height,0,sizeof(height));
		memset(p,0,sizeof(p));
		scanf("%s%I64d\n",s+1,&K);
		N=strlen(s+1);
		for (int i=1;i<=N;i++)ran[i]=s[i];
		for (int i=1;i<=N;i<<=1)work(i);
		getheight();
		int l=0,r=N;
		while (l<r){
			int mid=(l+r+1)>>1;
			if (check(mid)<K)l=mid;
			else r=mid-1;
		}
		res=check(l);
		l++;
		p[l]=N-sa[l]+1;
		for (int i=l+1;i<=N;i++)p[i]=min(p[i-1],height[i]);
		int x=N;
		for (int i=height[l]+1;i<=N-sa[l]+1;i++){
			for (;x>l&&p[x]<i;x--);
			if (res+(x-l+1)>=K){
				printf("Case %d: ",tt);
				for (int j=1;j<=i;j++)
					printf("%c",s[sa[l]+j-1]);
				printf("\n");
				break;
			}
			res+=x-l+1;
		}
	}
}