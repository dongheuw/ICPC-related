#include <bits/stdc++.h>
#define LL long long
const int mod=1000000007;
const int maxn=10000005;
bool check[maxn];
LL sumPhi[maxn];
int cnt,phi[maxn],prime[maxn];

void getphi(){
    phi[1]=1;
    cnt=0;
    for(int i=2;i<maxn;i++){
        if(!check[i]){phi[i]=i-1;prime[cnt++]=i;}
        for(int j=0;j<cnt;j++){
            if(i*prime[j]>=maxn)break;
            check[i*prime[j]]=true;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];break;
            }else{
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
            }
        }
    }
    sumPhi[0]=0;
    for(int i=1;i<maxn;i++)sumPhi[i]=(sumPhi[i-1]+phi[i])%mod;  
}

LL work(int n,int m)
{
    if(n==1) return sumPhi[m];
    if(m==1) return phi[n];
    if(m<1) return 0;
    for(int i=0;i<cnt;++i){
        if(n%prime[i]==0)
            return ((prime[i]-1)*work(n/prime[i],m)%mod+work(n,m/prime[i]))%mod;    
    }   
    return 0;
}
LL pow(LL a,LL b,int p)
{
    LL ret=1;
    a %= p;
    while(b)
    {
        if(b&1) ret=(ret*a)%p;
        a= a*a%p;
        b >>= 1;
    }   
    return ret;
}

LL gao(LL k,int p)
{
    if(p==1) return 0;
    LL tmp=gao(k,phi[p]);
    return pow(k,tmp+phi[p],p); 
}

int main()
{
    int n,m,p;
    getphi();
    while(~scanf("%d%d%d",&n,&m,&p))
    {
        LL k=work(n,m);
        printf("%I64d\n",gao(k,p)); 
    }
    return 0;   
}
