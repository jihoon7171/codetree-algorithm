#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int k,m;
int indexnum;
vector<vector<int>>space;
pair<int, int>v[9] = {{1,1},{2,1}, {3,1}, {1,2},{2,2}, {3,2}, {1,3}, {2,3}, {3,3}};
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,1,-1};
int piece[300];
void checking(){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout<<space[i][j]<<" ";
        }
        cout<<"\n";
    }
}
void input(){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cin>>space[i][j];
        }
    }
    for(int i=0;i<m;i++){
        cin>>piece[i];
    }
}

void rotation_nine(vector<vector<int>>&copy_space, int x, int y){

    vector<vector<int>>original(copy_space);
    copy_space[y-1][x+1] = original[y-1][x-1];
    copy_space[y][x+1] = original[y-1][x];
    copy_space[y+1][x+1] = original[y-1][x+1];
    copy_space[y+1][x] = original[y][x+1];
    copy_space[y+1][x-1] = original[y+1][x+1];
    copy_space[y][x-1] = original[y+1][x];
    copy_space[y-1][x-1] = original[y+1][x-1];
    copy_space[y-1][x] = original[y][x-1];
    // copy_space[y+1][x+1] = original[y-1][x-1];
    // copy_space[y][x+1] = original[y-1][x];
    // copy_space[y][x-1] = original[y+1][x];
    // copy_space[y+1][x-1] = original[y+1][x+1];
    // copy_space[y+1][x] = original[y][x+1];
    // copy_space[y-1][x-1] = original[y+1][x-1];
    // copy_space[y-1][x] = original[y][x-1];
    // copy_space[y-1][x+1] = original[y-1][x-1];

}

int tamsa(vector<vector<int>>&copy_space){
    int count=0;
    vector<vector<bool>>visit(5, vector<bool>(5, false));
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            int number = copy_space[i][j];
            int temp_count=1;
            if(!visit[i][j])
            visit[i][j] = true;
            queue<pair<int, int>>q;
            queue<pair<int, int>>position;
            position.push({i,j});
            q.push({i,j});
            while(!q.empty()){
                int x = q.front().second;
                int y = q.front().first;
                q.pop();
                for(int i=0;i<4;i++){
                    int newx = x+dx[i];
                    int newy = y+dy[i];
                    if(newx >=0 && newx < 5 && newy >=0&& newy<5 &&!visit[newy][newx] && copy_space[newy][newx] == number){
                        temp_count++;
                        q.push({newy, newx});
                        visit[newy][newx] = true;
                        position.push({newy, newx});
                    }
                }
            }
            if(temp_count >= 3){
                while(!position.empty()){
                    int x = position.front().second;
                    int y = position.front().first;
                    position.pop();
                    copy_space[y][x] = 0;
                    count++;
                }
            }
        }
    }
    return count;
}


void fill(){
    for(int i=0;i<5;i++){
        for(int j=4;j>=0;j--){
            if(space[j][i] == 0 && indexnum < m){
                space[j][i] = piece[indexnum];
                indexnum++;
            }
        }
    }
}
//3 2 3 5 2 4 6 1 3 2 5 6 2 1 5 6 7 1 2 3

bool go_rotation(int &counting){
    int result_rotation = 0;
    int count =-1;
    pair<int, int>result_position = {0,0};
    for(int i=0;i<9;i++){
        int x = v[i].second;
        int y = v[i].first;
        for(int j=1;j<=3;j++){
            vector<vector<int>>copy_space(space);
            if(j == 1){
                rotation_nine(copy_space, x, y);
                if(count < tamsa(copy_space)){
                    count = tamsa(copy_space);
                    result_rotation = j;
                    result_position.first = y;
                    result_position.second = x;
                }else if(count == tamsa(copy_space)){
                    //cout<<result_rotation<<" "<<j<<"asdfasdf\n";
                    if(result_rotation > 1){
                        //cout<<y<<" "<<x<<"asdfasdf\n";
                        result_rotation = 1;
                        result_position.first = y;
                        result_position.second = x;
                    }
                }
            }else if(j == 2){
                rotation_nine(copy_space,x,y);
                rotation_nine(copy_space,x,y);
                if(count < tamsa(copy_space)){
                    count = tamsa(copy_space);
                    result_rotation = j;
                    result_position.first = y;
                    result_position.second = x;
                }else if(count == tamsa(copy_space)){
                    if(result_rotation > 2){
                        result_rotation = j;
                        result_position.first = y;
                        result_position.second = x;
                    }
                }
            }else if( j == 3){
                rotation_nine(copy_space,x,y);
                rotation_nine(copy_space,x,y);
                rotation_nine(copy_space,x,y);
                if(count < tamsa(copy_space)){
                    count = tamsa(copy_space);
                    result_rotation = j;
                    result_position.first = y;
                    result_position.second = x;
                }
            }
        }
    }
    if(count <= 0){
        return false;
    }else{
        //cout<<result_rotation<<"asdfasdf ";
        for(int i=0;i<result_rotation;i++){
            rotation_nine(space, result_position.second, result_position.first);
        }
        counting += tamsa(space);
        while(true){
            fill();
            //checking();
            //cout<<"asdf";
            int temp = tamsa(space);
            if(temp == 0){
                break;
            }
            counting += temp;
            //cout<<temp<<" ";
        }
        cout<<counting;
       

    }
     return false;

}



int main() {
    cin>>k>>m;
    space.resize(5, vector<int>(5,0));
    input();
    indexnum =0;
    for(int i=0;i<k;i++){
        int counting=0;
        bool checked = go_rotation(counting);
        
        cout<<" ";
    }

    

}