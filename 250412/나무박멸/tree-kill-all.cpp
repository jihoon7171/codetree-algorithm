#include <iostream>
#include<queue>
#include<vector>
using namespace std;
int n,m,k,c;
struct info{
    int tree; // 나무의 수 -> -1 이면 벽 0 이면 빈칸 0이상이면 나무의 수
    int jecho; // 0 -> 제초제 없음 0이상 -> 제초제 연 
};
struct position{
    int x;
    int y;
};
//0,2,4,6 -> 상 좌 하 우
// 1, 3, 5, 7 -> 대각선
int dx[8] = {0,1,1,1,0,-1,-1,-1};
int dy[8] = {-1,-1,0,1,1,1,0,-1}; 
vector<vector<info>>space;
void printing(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<space[i][j].tree<<" ";
        }
        cout<<"\n";
    }
}
void spread_tree(vector<vector<bool>>&ispossible){\
    vector<vector<info>>copy_space(space);

    //cout<<"spread_tree start\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(space[i][j].tree>0 && ispossible[i][j]){
                int count  = 0;
                for(int k=0;k<7;k+=2){
                    int newx = j + dx[k];
                    int newy = i+dy[k];
                    if(newx >=0 && newx < n && newy >=0 && newy < n && copy_space[newy][newx].tree ==0&&space[newy][newx].jecho == 0){
                        count++;
                    }
                }
                if(count == 0) continue;
                int temp = copy_space[i][j].tree / count; 
                    for(int k=0;k<7;k+=2){
                    int newx = j + dx[k];
                    int newy = i+dy[k];
                    if(newx >=0 && newx < n && newy >=0 && newy < n && copy_space[newy][newx].tree ==0&&space[newy][newx].jecho == 0){
                        space[newy][newx].tree += temp;
                    }
                }
            }
        }
    }
  //  cout<<"after spread tree\n";
  //  printing();
  //  cout<<"\n";
}
void grow_tree(){
    vector<vector<bool>>ispossible(n, vector<bool>(n, false));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(space[i][j].tree>0){
                int count =0;
                for(int k=0;k<7;k+=2){
                    int newx = j + dx[k];
                    int newy = i+dy[k];
                    if(newx >=0 && newx < n && newy >=0 && newy < n && space[newy][newx].tree>0){
                        count++;
                    }
                }
                space[i][j].tree += count;
                ispossible[i][j] = true;
            }
        }
    }
   // cout<<"after growup\n";
    //printing();
    spread_tree(ispossible);
}
void cout_jecho(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<space[i][j].jecho<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

int do_spread_number(int x, int y){
    int result = space[y][x].tree;
    space[y][x].jecho++;
    for(int i=1;i<8;i+=2){
        int count = 1;
        while(count<=k){
            int newx = x+dx[i]*count;
            int newy =y+dy[i]*count;
            if(newx>=0&&newx<n&&newy>=0&&newy<n){
                if(space[newy][newx].tree == 0){
                    space[newy][newx].jecho = 1;
                    break;
                }else if(space[newy][newx].tree > 0){
                    space[newy][newx].jecho = 1;
                    result += space[newy][newx].tree;
                }else if(space[newy][newx].tree == -1){
                    break;
                }
            }
            count++;
        }
    }
   // cout_jecho();
   // cout<<"\n";
    return result;
}
//제초제 표시는 나중에 해야함 진짜로 돌릴떄 이거는 단순히 숫자 확인요
int find_spread_number(int x, int y){
    int result = space[y][x].tree;
    for(int i=1;i<8;i+=2){
        int count = 1;
        while(count<=k){
            int newx = x+dx[i]*count;
            int newy =y+dy[i]*count;
            if(newx>=0&&newx<n&&newy>=0&&newy<n){
                if(space[newy][newx].tree == 0){
                    //제초기 표시만 하기
                    break;
                }else if(space[newy][newx].tree > 0){
                    //제초기 표기 추가
                    result += space[newy][newx].tree;
                }else if(space[newy][newx].tree == -1){
                    break;
                }
            }
            count++;
        }
    }
    return result;
}

void kill_tree(int &answer){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(space[i][j].jecho > 0){
                answer +=space[i][j].tree;
                space[i][j].tree = 0;
            }
        }
    }
}

void kill_jecho(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(space[i][j].jecho > c){
                space[i][j].jecho = 0;
            }
        }
    }
}

void plus_jecho(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(space[i][j].jecho > 0){
                space[i][j].jecho++;
            }
        }
    }
}

void find_maximum(){
    pair<int, int> go_position;
    int comp = -1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if( space[i][j].tree == -1 || space[i][j].tree == 0) continue;
            int temp = find_spread_number(j,i);
            if(comp < temp){
                comp = temp;
                go_position.first = i;
                go_position.second = j;
            }
        }
    }
    //cout<<go_position.second<<" "<<go_position.first<<"\n";
    do_spread_number(go_position.second, go_position.first);
}


int main() {
    cin>>n>>m>>k>>c;
    space.resize(n, vector<info>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>space[i][j].tree;
        }
    }
    // grow_tree();
    // find_minimum();
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<space[i][j].jecho<<" ";
    //     }
    //     cout<<"\n";
    // }
    //cout<<"\n";
    int answer = 0;
    for(int i=0;i<m;i++){
        if(i>1){
        plus_jecho();
        }

        kill_jecho();
      //  cout<<"after kill_jecho\n";
      //  cout_jecho();
        grow_tree();
        find_maximum();      
        kill_tree(answer);

       // cout_jecho();
       // cout<<i<<"번째 ㄱ끝나고 space"<<"\n";
        //printing();
       // cout<<"\n";
    }
    cout<<answer;        

}
