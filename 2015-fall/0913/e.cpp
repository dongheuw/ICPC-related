#include <iostream>       
#include <cstdio>              
#include <algorithm>       
#include <iomanip>       
#include <cstdlib>       
#include <string>       
#include <cstring>       
#include <vector>        
#include <map>     
#include <list>  
#define INF 1000000000   
#define LL long long   
#define min3(a,b,c) min(a,min(b,c))
#define max3(a,b,c) max(a,max(b,c))

using namespace std;

list<int> List;
map<int, LL> Map;

int main(){

    int t;
    cin>>t;
    while(t--){
        List.clear();
        Map.clear();

        int n;
        cin>>n;

        int flag=-1;  //总在最前 

        for(int _=1; _<=n; ++_) {
            string op;
            cin >> op;
            printf("Operation #%d: ", _); 

            if(op == "Prior"){ //Prior
                if(List.empty()){
                    printf("empty.\n");
                }else{
                    map<int,LL>::iterator it=Map.end();
                    it--;
                    int tmp=it->first;

                    for(list<int>::iterator it=List.begin();it!=List.end();it++){
                        if(*it==tmp){
                            List.remove(*it);
                            List.push_front(tmp);
                            break;
                        }
                    }
                    printf("success.\n");

                }
            }else if(op == "Add"){  //Add
                int u;
                scanf("%d",&u);
                if(Map.count(u)){
                    printf("same priority.\n");
                }else{
                    List.push_back(u);
                    Map[u]=0;
                    printf("success.\n");
                }
            }else if(op == "Chat"){ //Chat
                int w;
                scanf("%d",&w);
                if(List.empty()){
                    printf("empty.\n");
                }else{
                    if(flag!=-1){
                        Map[flag]+=w;
                    }else{
                        int cur=*List.begin();
                        Map[cur]+=w;
                    }
                    printf("success.\n");

                }
            }else if(op == "Top"){  //Top
                int u;
                scanf("%d",&u);
                if(Map.count(u)){
                    flag=u;
                    printf("success.\n");
                }else{
                    printf("invalid priority.\n");
                }
            }else if(op == "Untop"){ //Untop
                if(flag==-1){
                    printf("no such person.\n");
                }else{
                    flag=-1;
                    printf("success.\n");
                }
            }else if(op == "Rotate"){  //Rotate
                int x;
                scanf("%d",&x);
                if(x<1|| x>List.size()) {
                    printf("out of range.\n");
                }else{
                    int tmp=0;
                    for(list<int>::iterator it=List.begin();it!=List.end();it++){
                        tmp++;
                        if(tmp==x){
                            x=*it;
                            List.remove(*it);

                            List.push_front(x);
                            break;
                        }
                    }
                    printf("success.\n");
                }
            }else if(op == "Close") {
                int u;
                scanf("%d",&u);
                if(Map.count(u)){
                    cout << "close " << u << " with " << Map[u] << "." << endl;
                    for(list<int>::iterator it=List.begin();it!=List.end();it++){
                        if(*it==u){
                            List.remove(*it);
                            break;
                        }
                    }
                    Map.erase(u);
                }else{
                    puts("invalid priority.");
                }
            }else if(op == "Choose") {
                int u;
                scanf("%d",&u);
                if(Map.count(u)){
                    for(list<int>::iterator it=List.begin();it!=List.end();it++){
                        if(*it==u){
                            List.remove(*it);
                            List.push_front(u);
                            break;
                        }
                    }
                    puts("success.");
                }else{
                    puts("invalid priority.");
                }
            }
        }

        int last=-1;
        if(flag!=-1){
            last=flag;
        }else{
            if(!List.empty())
                last=*List.begin();
        }
        if(last!=-1&&Map[last]!=0) {
            cout<<"Bye "<<last<<": "<<Map[last]<<endl;
        }
        for(list<int>::iterator it=List.begin();it!=List.end();it++){
            if(last==*it)
                continue;
            if(Map[*it]>0) {
                cout<<"Bye "<<*it<<": "<<Map[*it]<<endl;
            }
        }
    }
    return 0;
}
