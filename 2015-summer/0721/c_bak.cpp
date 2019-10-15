#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define maxn 10
#define inf 21000000
int status[]={1,2,4,8,16,32,64,128,256};
struct node{
    bool up,down,left,right,is_hole;
    bool is_end;
}map1[maxn][maxn],map2[maxn][maxn];
int is_visit[maxn][maxn][maxn][maxn],global;
char ans[100*100];
char now[100*100];
bool flag;
int find_ans(int x1,int y1,int x2,int y2,int step){
    if(step >=global || is_visit[x1][y1][x2][y2]<=step)
        return 0;
    is_visit[x1][y1][x2][y2]=step;
    if(map1[x1][y1].is_end && map2[x2][y2].is_end){
        flag=true;
        now[step]=0;
        if(step<global)global=step,strcpy(ans,now);
        else if(step==global && (strcmp(ans,now)>0))strcpy(ans,now);
    }
    if((map1[x1][y1].down || (x1+1<=6 && !map1[x1+1][y1].is_hole)) &&\
       (map2[x2][y2].down || (x2+1<=6 && !map2[x2+1][y2].is_hole))){
           if(map1[x1][y1].down){
                if(map2[x2][y2].down);
                else { now[step]='D';find_ans(x1,y1,x2+1,y2,step+1);}
           }
           else if(map2[x2][y2].down){
                now[step]='D';
                find_ans(x1+1,y1,x2,y2,step+1);
           }
           else {
                now[step]='D';
                find_ans(x1+1,y1,x2+1,y2,step+1);
           }
    }
    if((map1[x1][y1].left || (y1-1>=1 && !map1[x1][y1-1].is_hole)) &&\
       (map2[x2][y2].left || (y2-1>=1 && !map2[x2][y2-1].is_hole))){
           if(map1[x1][y1].left){
                if(map2[x2][y2].left);
                else { now[step]='L';find_ans(x1,y1,x2,y2-1,step+1);}
           }
           else if(map2[x2][y2].left){
                now[step]='L';
                find_ans(x1,y1-1,x2,y2,step+1);
           }
           else {
                now[step]='L';
                find_ans(x1,y1-1,x2,y2-1,step+1);
           }
    }
     if((map1[x1][y1].right || (y1+1<=6 && !map1[x1][y1+1].is_hole)) &&\
       (map2[x2][y2].right || (y2+1<=6 && !map2[x2][y2+1].is_hole))){
           if(map1[x1][y1].right){
                if(map2[x2][y2].right);
                else { now[step]='R';find_ans(x1,y1,x2,y2+1,step+1);}
           }
           else if(map2[x2][y2].right){
                now[step]='R';
                find_ans(x1,y1+1,x2,y2,step+1);
           }
           else {
                now[step]='R';
                find_ans(x1,y1+1,x2,y2+1,step+1);
           }
    }
    if((map1[x1][y1].up || (x1-1>=1 && !map1[x1-1][y1].is_hole)) &&\
       (map2[x2][y2].up || (x2-1>=1 && !map2[x2-1][y2].is_hole))){
           if(map1[x1][y1].up){
                if(map2[x2][y2].up);
                else { now[step]='U';find_ans(x1,y1,x2-1,y2,step+1);}
           }
           else if(map2[x2][y2].up){
                now[step]='U';
                find_ans(x1-1,y1,x2,y2,step+1);
           }
           else {
                now[step]='U';
                find_ans(x1-1,y1,x2-1,y2,step+1);
           }
    }
    return 0;
}
int main(){
    int i,j,k,p,q,r,t,x1,y1,x2,y2;
    scanf("%d",&t);
      for(i=1;i<=6;i++)
        for(j=1;j<=6;j++){
            scanf("%d",&k);
            map1[i][j].left=k&status[0];
            map1[i][j].down=k&status[1];
            map1[i][j].right=k&status[2];
            map1[i][j].up=k&status[3];
            map1[i][j].is_hole=!(k&status[4]);
            map1[i][j].is_end=k&status[6];
            if(k&status[5]) x1=i,y1=j;
        }
        t--;
    while(t--){
            ans[0]=0;
            flag=false;
            global=21000000;
        for(i=0;i<8;i++)
        for(j=0;j<8;j++)
        for(p=0;p<8;p++)
        for(q=0;q<8;q++)
        is_visit[i][j][p][q]=inf;
        for(i=1;i<=6;i++)
        for(j=1;j<=6;j++){
            scanf("%d",&k);
            map2[i][j].left=k&status[0];
            map2[i][j].down=k&status[1];
            map2[i][j].right=k&status[2];
            map2[i][j].up=k&status[3];
            map2[i][j].is_hole=!(k&status[4]);
            map2[i][j].is_end=k&status[6];
            if(k&status[5]) x2=i,y2=j;
        }
        find_ans(x1,y1,x2,y2,0);
        if(flag) printf("%s\n",ans);
        else printf("-1\n");
        for(i=1;i<=6;i++)
        for(j=1;j<=6;j++)
        map1[i][j]=map2[i][j];
        x1=x2,y1=y2;
    }
    return 0;
}
