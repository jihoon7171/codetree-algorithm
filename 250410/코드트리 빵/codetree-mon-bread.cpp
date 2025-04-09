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



bool checking_con(){
    for(int i=1;i<=m;i++){
        if(con[i]) return true; //하나라도 true -> 방문가능한게 있다 -> true 반환 (더 돌아야한다)
    }
    return false;
}

void moving_human(queue<int>&q){
    for(int i=1;i<=human.size();i++){
        //아직 출발 안했거나 편의점에 도착했을경우 -> 움직이면 안됨
        if((human[i].x == 0 && human[i].y == 0) || (human[i].x == con_position[i].x && human[i].y == con_position[i].y)){
            continue;
        }else{
            for(int j=0;j<4;j++){
                int newx = human[i].x+dx[j];
                int newy = human[i].y+dy[j];
                if(newx >=1 && newx <=n && newy >=1 && newy <=n && space[newy][newx] != -1){
                    if(distance(human[i].x, human[i].y, con_position[i].x, con_position[i].y) > distance(newx, newy, con_position[i].x, con_position[i].y)){
                        human[i].x = newx;
                        human[i].y = newy;
                        if(human[i].x == con_position[i].x && human[i].y == con_position[i].y){
                            con[i] = false; // i 번은 편의점에 도착함 -> 맨 마지막에  맵에 -1 해줘야함
                            q.push(i);
                        }
                        break;
                    }
                }
            }
        }
    }
}

void set_basecamp(int index){
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
               // cout<<human[index].y<<" "<<human[index].x<<" "<<d<<"\n";
            }
        }
    }
    basecamp[newindex] = false;
    human[index].x = basecamp_position[newindex].x;
    human[index].y = basecamp_position[newindex].y;
    space[human[index].y][human[index].x] = -1;
   // cout<<human[index].y << " "<<human[index].x<<"\n";
   // cout<<"함수 끝\n";
    return ;
}


void cout_human(){
    for(int i=1;i<=human.size();i++){
        cout<<human[i].y<<" "<<human[i].x<<"\n";
    }
}

void go_con(){
    int t=1;
    int index = 1;
    set_basecamp(index);
    space[human[1].y][human[1].x] = -1;
    while(checking_con()){ //checking_con 이 true 면 아직 방문해야하는 편의점이 존재한다는 의미
        //cout<<t<<"초\n";
        t++;
        queue<int>q;
        //cout_human();
        moving_human(q);
        if(t<=m){
            set_basecamp(t);
        }
        while(!q.empty()){
            int comp = q.front();
            space[con_position[comp].y][con_position[comp].x] = -1;
            q.pop();
            con[comp] = false;
           // cout<<comp<<"편의점 false 완료";
        }
        
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