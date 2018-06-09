#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <string.h>

using namespace std;
typedef pair<int, int> pii;
const int inf=987654321;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int n,m;
int maze[555][555];
pii par[555][555];
bool check[555][555];
int totaltime=0;
vector <pii> goals;

bool inrange(pii loc){
    return loc.first >=0 && loc.first<n && loc.second>=0 && loc.second<m;
}

bool pacheck(pii loc){
    return par[loc.first][loc.second]==loc;
}

int mandist(pii a, pii b){
    return abs(a.first-b.first) + abs(a.second-b.second);
}

int heuri(pii now){
    int min = inf;
    for(int i=0;i<goals.size();i++){
        int dist=mandist(now, goals[i]);
        if(dist<min) min=dist;
    }
    return min;
}

pii GBS(pii start){
    priority_queue<pair < int, pii >, vector < pair < int, pii > >, greater < pair < int, pii > > > pq;
    pq.push(make_pair(heuri(start), start));
    check[start.first][start.second]=true;
    totaltime++;
    pii ret;
    while(!pq.empty()){
        pair<int, pii> now = pq.top();
        pq.pop();
        pii nowp = now.second;
        if(maze[nowp.first][nowp.second]==4) {
            ret=nowp;
            break;
        }
        for(int i=0;i<4;i++){
            pii nextp = make_pair(nowp.first+dx[i], nowp.second+dy[i]);
            if(inrange(nextp) && maze[nextp.first][nextp.second]!=1 && !check[nextp.first][nextp.second]){
                totaltime++;
                par[nextp.first][nextp.second]=nowp;
                check[nextp.first][nextp.second]=true;
                pq.push(make_pair(heuri(nextp), nextp));
            }
        }
    }
    return ret;
}


int main(int argc, const char * argv[]){
//    freopen("input_ex1.txt", "r", stdin);
//    freopen("output_ex1_GBS.txt", "w", stdout);
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&maze[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            par[i][j]=make_pair(i , j);
            if(maze[i][j]==4) goals.push_back(make_pair(i , j));
        }
    }
    pii goal;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(maze[i][j]==3) goal=GBS(make_pair(i , j));
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
