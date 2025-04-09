#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int soop[73][71];
bool isexit[73][71];
int r,c,k, answer =0;
int exit_position[4] = {0,1,2,3};
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};



bool inrange(int x, int y){
    bool flag = true;
    if(x>=1&&x<=c+2&&y>=1&&y<=r+2) return true;
    return false;
    
}
bool ispossible(int x, int y) {
    if (y >= 1 && y <= r + 2 - 1 && x >= 2 && x <= c - 1) {
        if (soop[y-1][x] == 0 && soop[y][x-1] == 0 && soop[y][x+1] == 0 && soop[y+1][x] == 0 && 
            soop[y][x] == 0 && soop[y-2][x] == 0 && soop[y-1][x+1] == 0&&soop[y-1][x-1] == 0) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
bool isout(int nowx, int nowy){
    for(int i=0;i<4;i++){
        int x = nowx+dx[i];
        int y = nowy+dy[i];
        if(!(y>=3&&y<=r+2&&x>=1&&x<=c)){ // 범위 내부에 존재하는지 체크
            return false;
        }
    }
    return true;
}

void soop_clear(){
    for(int i=0;i<=73;i++){
        for(int j=0;j<=71;j++){
            soop[i][j] = 0;
        }
    }
    for(int i=0;i<=73;i++){
        for(int j=0;j<=71;j++){
            isexit[i][j] = false;
        }
    }
}
int bfs(int x, int y) {
    vector<vector<bool>> visited(73, vector<bool>(71, false));
    int result = y;
    queue<pair<int, int>> q;
    q.push({y, x});
    visited[y][x] = true;
    while (!q.empty()) {
        int nowx = q.front().second;
        int nowy = q.front().first;
        q.pop();
        result = max(result, nowy); // 최대 행 갱신
        for (int i = 0; i < 4; i++) {
            int newx = nowx + dx[i];
            int newy = nowy + dy[i];
            if (inrange(newx, newy) && !visited[newy][newx]) {
                if (soop[newy][newx] == soop[nowy][nowx] || // 같은 골렘 내 이동
                    (isexit[nowy][nowx] && soop[newy][newx] != 0)) { // 출구를 통한 이동
                    visited[newy][newx] = true;
                    q.push({newy, newx});
                }
            }
        }
    }
    return result;
}

void checking(){
    for(int i=1;i<=r+2;i++){
        for(int j=1;j<=c;j++){
            cout<<soop[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void down(int x,int y,int d,int id){
      vector<vector<bool>>visited(74, vector<bool>(71, false));
    while(1){
        //down
        //cout<<y<<" "<<x<<"\n";
        visited[y][x] = true;
        if(ispossible(x,y+1)&&!visited[y+1][x]){
            y = y+1;

          //  visited[y+1][x] = true;
        }else if(ispossible(x-1,y+1)&&!visited[y][x-1]){
            x = x-1;
            d = (d+3)%4;

           // visited[y][x-1] = true;
        }else if(ispossible(x+1,y+1)&&!visited[x+1][y]){
            x = x+1;
            d = (d+1)%4;

          //  visited[y][x+1] = true;
        }else{
            if(!isout(x,y)){
                //cout<<"asdf";
                soop_clear();
                //checking();
                //cout<<"\n";
                return ;
            }else{
                soop[y][x] = id;
                for(int i=0;i<4;i++){
                    int newx = x+dx[i];
                    int newy = y+dy[i];
                    soop[newy][newx] = id;
                    //cout<<newy<<" "<<newx<<soop[newy][newx]<<"\n";
                }
                soop[y][x] = id;
            isexit[y+dy[d]][x+dx[d]] = true;
            //checking();
            //cout<<"\n";
            //cout<<y<<" "<<x<<"qq\n";
            int a = bfs(x,y)-2;
            //cout<<"지금 최고값은 "<<a<<"\n";
            answer += a;
            break;
            }
        }
    }
    return;
}

int main() {
    cin>>r>>c>>k;

    for(int i=1;i<=k;i++){
        int a,b;
        //a 는 시작 열, b는 출구 위치
        cin>>a>>b;
        down(a,1,b,i);
    }
    // cout<<"출구"<<"\n";
    // for(int i=1;i<=r+2;i++){
    //     for(int j=1;j<=c;j++){
    //         cout<<isexit[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    cout<<answer;

}
