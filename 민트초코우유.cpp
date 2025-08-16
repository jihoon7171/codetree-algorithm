#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<deque>
#include<algorithm>
using namespace std;
int n,m;
vector<vector<string>>food;
vector<vector<int>>bless;
vector<vector<int>>group;
vector<vector<bool>>canattack;

struct king{
    int point;
    int x;
    int y;
};

bool cmp(const king &a, const king &b) {
    if (a.point != b.point) return a.point > b.point; // point 큰 순서
    if (a.y != b.y) return a.y < b.y;                 // y 작은 순서
    return a.x < b.x;                                 // x 작은 순서
}
int dy[4] = {-1,1,0,0};
int dx[4] = {0,0,-1,1};

void input(){
    for(int i=0;i<n;i++){
        string temp;
        cin>>temp;
        for(int j=0;j<temp.size();j++){
            food[i][j] = temp[j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>bless[i][j];
        }
    }

}

void output(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<food[i][j]<<" ";
        }
        cout<<"\n";
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<bless[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<group[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
}


void morning(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            bless[i][j]++;
        }
    }
}

int selectteam(int x, int y){
    string nowfood = food[y][x];
    //cout<<nowfood<<y<<" "<<x<<"\n";
    sort(nowfood.begin(), nowfood.end());
    if(nowfood == "M" || nowfood == "T" || nowfood == "C"){
        return 1;
    }else if(nowfood == "CMT"){
        return 3;
    } 
    else{
        return 2;
    }
}

void fusionfood(int x, int y, int gox, int goy){
    string gofood = food[y][x];
    string nowfood = food[goy][gox];
    string newfood = "";
    set<char>s;
    for(int i=0;i<gofood.size();i++){
        s.insert(gofood[i]);
    }
    for(int i=0;i<nowfood.size();i++){
        s.insert(nowfood[i]);
    }
    for(auto ns : s){
        newfood += ns;
    }
    sort(newfood.begin(), newfood.end());
    food[goy][gox] = newfood;

}

void bfs(int x, int y, int &classnum, int &tx, int &ty, vector<pair<int, int>>&v){
    string nowfood = food[y][x];
    int nowpoint = bless[y][x];
    tx = x;
    ty = y;
    group[y][x] = classnum;
    queue<pair<int, int>>q;
    v.push_back({y,x});
    q.push({y,x});
    while(!q.empty()){
        int nowx = q.front().second;
        int nowy = q.front().first;
        q.pop();
        for(int i=0;i<4;i++){
            int newx = nowx+dx[i];
            int newy = nowy+dy[i];
            if(newx>=0&&newx<n&&newy>=0&&newy<n&&group[newy][newx] == -1&&food[newy][newx] == nowfood){
                group[newy][newx] = classnum;
                if(bless[newy][newx]>nowpoint){
                    ty = newy;
                    tx = newx;
                    nowpoint = bless[newy][newx];
                }else if(bless[newy][newx] == nowpoint){
                    if(newy < ty){
                        ty = newy;
                        tx = newx;
                        nowpoint = bless[newy][newx];                        
                    }else if(newy == ty){
                        if(newx < tx){
                            ty = newy;
                            tx = newx;
                            nowpoint = bless[newy][newx];                               
                        }
                    }
                }
                v.push_back({newy,newx});
                q.push({newy,newx});
            }
        }
    }
    classnum++;
}

void point_to_king(vector<pair<int, int>>&v, int tx, int ty){
    bless[ty][tx] += (v.size()-1);
    for(int i=0;i<v.size();i++){
        int nx = v[i].second;
        int ny = v[i].first;
        if(ny == ty && nx == tx){
            continue;
        }else{
            bless[ny][nx] -= 1;
        }
    }
}

void launch(vector<king>&one,vector<king>&two,vector<king>&three){
    vector<vector<bool>>visited(n, vector<bool>(n, false));
    int classnum = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            group[i][j] = -1; // 매 턴마다 그룹 초기화해줘야하니
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(group[i][j] == -1){
                int tx=j,ty=i;
                vector<pair<int, int>>v;
                bfs(j,i , classnum,tx,ty,v);
                //이제 tx,ty는 대표자의 좌표가 되었음 -> 이걸 어케 이용하면 괜찮을까?
                int nownumber = selectteam(tx,ty);
                point_to_king(v,tx,ty);
                if(nownumber == 1){
                    king nowking = {bless[ty][tx], tx,ty};
                    one.push_back(nowking);
                }else if(nownumber == 2){
                    king nowking = {bless[ty][tx], tx,ty};
                    two.push_back(nowking);                   
                }else{
                    king nowking = {bless[ty][tx], tx,ty};
                    three.push_back(nowking);
                }
            }
        }
    }
}

void dinner(vector<king>&one,vector<king>&two,vector<king>&three){
    sort(one.begin(), one.end(), cmp);
    sort(two.begin(), two.end(), cmp);
    sort(three.begin(), three.end(), cmp);
    // cout<<"순서\n";
    // for(int i=0;i<one.size();i++){
    //     cout<<one[i].y<<" "<<one[i].x<<"\n";
    // }


    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            canattack[i][j] = true;
        }
    }
    for(auto q : one){
        if(!canattack[q.y][q.x]){
            continue;
        }
        //cout<<bless[q.y][q.x]<<" "<<q.y<<" "<<q.x<<"\n";
        int direction = bless[q.y][q.x]%4;
        int nowx = q.x;
        int nowy = q.y;
        int blessingpoint = bless[q.y][q.x] - 1;
        bless[q.y][q.x]  = 1;
        while(1){
            nowx += dx[direction];
            nowy += dy[direction];
            if(nowx<0 || nowx>=n || nowy<0 || nowy>=n ){
                break;
            }
            //cout<<q.y<<" "<<q.x<<" 공격시작\n";
            int enemypoint = bless[nowy][nowx];
            //강한 전파
            //같은놈이면 패스
            if(food[q.y][q.x] == food[nowy][nowx]){
                //output();
                continue;
            }
            if(blessingpoint > enemypoint){
                food[nowy][nowx] = food[q.y][q.x];
                blessingpoint -= (enemypoint+1);
                bless[nowy][nowx] += 1;
                canattack[nowy][nowx] = false;
                if(blessingpoint == 0){
                    break;
                }
            //약한 전파
            }else{
                canattack[nowy][nowx] = false;
                bless[nowy][nowx] += blessingpoint;
                blessingpoint = 0;
                fusionfood(q.x,q.y,nowx,nowy);
                break;
            }
            //output();
        }
    }

    for(auto q : two){
        if(!canattack[q.y][q.x]){
            continue;
        }
        int direction = bless[q.y][q.x]%4;
        int nowx = q.x;
        int nowy = q.y;
        int blessingpoint = bless[q.y][q.x] - 1;
        bless[q.y][q.x]  = 1;
        while(1){
            nowx += dx[direction];
            nowy += dy[direction];
            if(nowx<0 || nowx>=n || nowy<0 || nowy>=n ){
                break;
            }
            int enemypoint = bless[nowy][nowx];
            //같은놈이면 패스
            if(food[q.y][q.x] == food[nowy][nowx]){
                //output();
                continue;
            }
            //cout<<q.y<<" "<<q.x<<" 공격시작\n";
            //강한 전파
            if(blessingpoint > enemypoint){
                food[nowy][nowx] = food[q.y][q.x];
                blessingpoint -= (enemypoint+1);
                bless[nowy][nowx] += 1;
                canattack[nowy][nowx] = false;
                if(blessingpoint == 0){
                    break;
                }
            //약한 전파
            }else{
                canattack[nowy][nowx] = false;
                bless[nowy][nowx] += blessingpoint;
                blessingpoint = 0;
                fusionfood(q.x,q.y,nowx,nowy);
                break;
            }
            //output();
        }
    }

    for(auto q : three){
        if(!canattack[q.y][q.x]){
            continue;
        }
        int direction = bless[q.y][q.x]%4;
        int nowx = q.x;
        int nowy = q.y;
        int blessingpoint = bless[q.y][q.x] - 1;
        bless[q.y][q.x]  = 1;
        while(1){
            nowx += dx[direction];
            nowy += dy[direction];
            if(nowx<0 || nowx>=n || nowy<0 || nowy>=n ){
                break;
            }
            int enemypoint = bless[nowy][nowx];
                        //같은놈이면 패스
            if(food[q.y][q.x] == food[nowy][nowx]){
                //output();
                continue;
            }
            //cout<<q.y<<" "<<q.x<<" 공격시작\n";
            //강한 전파
            if(blessingpoint > enemypoint){
                food[nowy][nowx] = food[q.y][q.x];
                blessingpoint -= (enemypoint+1);
                canattack[nowy][nowx] = false;
                bless[nowy][nowx] += 1;
                if(blessingpoint == 0){
                    break;
                }
            //약한 전파
            }else{
                canattack[nowy][nowx] = false;
                bless[nowy][nowx] += blessingpoint;
                blessingpoint = 0;
                fusionfood(q.x,q.y,nowx,nowy);
                break;
            }
            //output();
        }
    }

}

void answeroutput(){
    int cmt=0,ct=0,mt=0,cm=0,m=0,c=0,t=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(food[i][j] == "CMT"){
                cmt+=bless[i][j];
            }else if(food[i][j] == "CT"){
                ct+=bless[i][j];
            }else if(food[i][j] == "MT"){
                mt+=bless[i][j];
            }else if(food[i][j] == "CM"){
                cm+=bless[i][j];
            }else if(food[i][j] == "M"){
                m+=bless[i][j];
            }else if(food[i][j] == "C"){
                c+=bless[i][j];
            }else if(food[i][j] == "T"){
                t+=bless[i][j];
            }
        }
    }

    cout<<cmt<<" "<<ct<<" "<<mt<<" "<<cm<<" "<<m<<" "<<c<<" "<<t<<"\n";
}

void initial(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            group[i][j] = -1;
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            canattack[i][j] = false;
        }
    }   
}


int main() {
    cin>>n>>m;
    food.resize(n, vector<string>(n));
    bless.resize(n, vector<int>(n));
    group.resize(n, vector<int>(n));
    canattack.resize(n, vector<bool>(n));
    input();
    

    while(m--){
        initial();
        vector<king>one;
        vector<king>two;
        vector<king>three;
        morning();
        //output();
        launch(one,two,three);
        //output();
        dinner(one,two,three);
        //output();
        answeroutput();
    }


    

    
}