#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <string.h>

using namespace std;
typedef pair<int, int> pii;

int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int n,m;
int maze[555][555];
bool check[555][555];
int totaltime=0;

pii par[555][555];

bool pacheck(pii goal){
    return par[goal.first][goal.second]==goal;
}

pii DFS(int nowx, int nowy, int step){
    totaltime++;
    if(step == 0 && maze[nowx][nowy]==4)
        return make_pair(nowx, nowy);
    if (step > 0){
        pii found;
        for(int i=0;i<4;i++){
            int nextx = nowx+dx[i];
            int nexty = nowy+dy[i];
            if(nextx>=0 && nextx<n && nexty>=0 && nexty<m && maze[nextx][nexty]!=1 && !check[nextx][nexty]){
                par[nextx][nexty] = make_pair(nowx, nowy);
                check[nextx][nexty] = true;
                found = DFS(nextx, nexty, step-1);
                if(found.first!=-1 && found.second!=-1) return found;
                par[nextx][nexty] = make_pair(nextx,nexty);
                check[nextx][nexty] = false;
            }
        }
    }
    return make_pair(-1, -1);
}

pii IDS(int x,int y){
    int step=0;
    while(true){
        check[x][y]=true;
        pii found = DFS(x,y,step);
        if(found.first!=-1 && found.second!=-1) return found;
        step++;
    }
}

int main(int argc, const char * argv[]) {
//    freopen("input_ex3.txt", "r", stdin);
//    freopen("output_ex3_IDS.txt", "w", stdout);
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&maze[i][j]);
            par[i][j]=make_pair(i, j);
        }
    }
    pii goal;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(maze[i][j]==3){
                goal = IDS(i,j);
            }
        }
    }
    int length=0;
    goal = par[goal.first][goal.second];
    while(!pacheck(goal)){
        maze[goal.first][goal.second] = 5;
        length++;
        goal = par[goal.first][goal.second];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",maze[i][j]);
        }
        printf("\n");
    }
    printf("---\n");
    printf("length=%d\n",length);
    printf("time=%d\n",totaltime);
    return 0;
}
