#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
int dy[4] = {-1,0,0,1};
int dx[4] = {0,-1,1,0};
struct position{
    int y;
    int x;
};
int n,m;
int basecamp_num;
vector<vector<int>>space;
vector<bool>basecamp(226, true);
vector<bool>con;
vector<position>human;
vector<position>con_position;
vector<position>basecamp_position(226);
int distance(int x, int y, int gx, int gy){
    return abs(x-gx) + abs(y-gy);
}


void cout_space(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<space[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

bool checking_con(){
    for(int i=1;i<=m;i++){
        if(con[i]) return true; //하나라도 true -> 방문가능한게 있다 -> true 반환 (더 돌아야한다)
    }
    return false;
}

position find_minimum(int index, vector<vector<int>>&visited){

    position return_position;
    int x = human[index].x;
    int y = human[index].y;
    int minx, miny;
    int dis = 100000;
    for(int i=0;i<4;i++){
        int newx = x+dx[i];
        int newy = y+dy[i];
        if(newx >=1 && newx <=n && newy >=1 && newy <=n && visited[newy][newx] < dis && visited[newy][newx] != -1){
            dis = visited[newy][newx];
            minx = newx;
            miny = newy;
        }
    }
   // cout<<index<<" 번이 이동하는 위치는"<<miny<<" "<<minx<<"\n";
    return_position  = {miny,minx};
    return return_position;
}

void moving_human(queue<int>&q){
    for(int i=1;i<=human.size()-1;i++){
        if(!con[i]||(human[i].x == 0 && human[i].y == 0) || (human[i].x == con_position[i].x && human[i].y == con_position[i].y)){
            continue;
        }else {
            vector<vector<int>>visited(n+1, vector<int>(n+1, -1));
            visited[con_position[i].y][con_position[i].x] = 0;
             int x = con_position[i].x;
             int y = con_position[i].y;
             queue<position>p;
             p.push({y,x});
             while(!p.empty()){
                int nowx = p.front().x;
                int nowy = p.front().y;
                p.pop();
                for(int j=0;j<4;j++){
                    int newx = nowx+dx[j];
                    int newy = nowy+dy[j];
                    if(newx >=1 && newx <=n && newy >=1 && newy <=n && visited[newy][newx] == -1&&(space[newy][newx] == 0 || space[newy][newx] == 1)){
                        visited[newy][newx] = visited[nowy][nowx]+1;
                        p.push({newy,newx});
                    }
                }
            }
            position nposition = find_minimum(i, visited);
            human[i].y = nposition.y;
            human[i].x = nposition.x;
           // cout<<"사람움직이기 시작"<<i<<"번째 사람 "<<human[i].y<<" "<<human[i].x<<"\n";
            if(human[i].y == con_position[i].y && human[i].x == con_position[i].x){
                q.push(i);
                continue;
            }
            // cout<<i<<"움직이기 시작 후 위치\n";
            // for(int i=1;i<=n;i++){
            //     for(int j=1;j<=n;j++){
            //         cout<<visited[i][j]<<" ";
            //     }
            //     cout<<"\n";
            // }
            // cout<<i<<"움직이기 시작 후 위치 end\n";
        }
    }
}


void set_basecamp(int index, queue<int>&p){
   // cout<<"함수시작\n";
    int cx = con_position[index].x;
    int cy = con_position[index].y;
    int d = 1000000;
   // cout<<cx<<" "<<cx<<"\n";
    int newindex = 1;
    
    for(int i=1;i<=basecamp_num;i++){
        if(basecamp[i]){
            if(d > distance(basecamp_position[i].x, basecamp_position[i].y, cx, cy)){
                d = distance(basecamp_position[i].x, basecamp_position[i].y, cx, cy);
                human[index].x = basecamp_position[i].x;
                human[index].y = basecamp_position[i].y;
                newindex = i;
                
            }
        }
    }
    basecamp[newindex] = false;
   // cout<<index<<"집은"<<human[index].y<<" "<<human[index].x<<" "<<d<<"\n";
    human[index].x = basecamp_position[newindex].x;
    human[index].y = basecamp_position[newindex].y;
    //space[human[index].y][human[index].x] = -1;
    p.push(newindex);
   // cout<<human[index].y << " "<<human[index].x<<"\n";
   // cout<<"함수 끝\n";
    return ;
}


void cout_human(){
    cout<<"모든 사람 위치 나오기 start\n";
    for(int i=1;i<=human.size();i++){
        cout<<human[i].y<<" "<<human[i].x<<"\n";
    }
    cout<<"모든 사람 위치 나오기 끝\n";
}



void go_con(){
    int t=1;
    int index = 1;
    queue<int>p;
    set_basecamp(index, p);
    space[human[1].y][human[1].x] = -1;
    while(!p.empty()){
        int comp = p.front();
        space[basecamp_position[comp].y][basecamp_position[comp].x] = -1;
        p.pop();
    }
   // cout<<1<<"번의 집은"<<human[1].y<<human[1].x
    while(checking_con()){ //checking_con 이 true 면 아직 방문해야하는 편의점이 존재한다는 의미
        t++;
       // cout<<t<<"초\n";
        queue<int>q;
        queue<int>p;
        //cout_human();
        moving_human(q);
        if(t<=m){
            set_basecamp(t, p);
        }
        while(!q.empty()){
            int comp = q.front();
            space[con_position[comp].y][con_position[comp].x] = -1;
            q.pop();
            con[comp] = false;
            //cout<<comp<<"편의점 false 완료\n";
        }
        while(!p.empty()){
          //  cout<<t<<"번 집 지우기 완료\n";
            int comp = p.front();
            space[basecamp_position[comp].y][basecamp_position[comp].x] = -1;
            p.pop();
        }
       // cout<<"전체스페이스"<<"초\n";
       // cout_space();
       // cout<<"전체스페이스\n";
    }
    cout<<t;
}

int main() {
    cin>>n>>m;
    space.resize(n+1, vector<int>(n+1));
    con.resize(m+1, true);
    human.resize(m+1);
    con_position.resize(m+1);
    basecamp_num=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>space[i][j];
            if(space[i][j] == 1){
                basecamp_position[basecamp_num].y =i;
                basecamp_position[basecamp_num].x = j;
                basecamp_num++;
            }

        }
    }
    basecamp_num = basecamp_num-1;
    //cout<<"정렬전"<<"\n";
    // for(int i=1;i<=basecamp_num;i++){
    //     cout<<basecamp_position[i].y<<" "<<basecamp_position[i].x<<"\n";
    // }
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>y>>x;
        con_position[i].x = x;
        con_position[i].y = y;
    }
    go_con();
    //  set_basecamp(1);
    // // cout<<"1 end"<<"\n";
    // set_basecamp(2);
    // set_basecamp(3);
    // // for(int i=1;i<=3;i++){
    // //     cout<<human[i].y<<" "<<human[i].x<<"\n";
    // // }
    // // cout<<"asdfasdf";
    return 0;
}