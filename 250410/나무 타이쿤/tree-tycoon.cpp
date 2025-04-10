#include <iostream>
#include<vector>
using namespace std;

int n,m, direction ,c;
vector<vector<int>>space;
vector<vector<int>>nutrition;

int dx[9] = {0,1,1,0,-1,-1,-1,0,1};
int dy[9] = {0,0,-1,-1,-1,0,1,1,1};

void move_nut(int d, int p){
    //cout<<"이동 시작\n";
    vector<vector<int>>copy_nutrition(n, vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(nutrition[i][j] == 1){
                int newx = (j+dx[d]*p)%n;
                int newy = (i+dy[d]*p)%n;
               //cout<<j<<" "<<dx[d]<<" "<<p<<" "<<n<<"\n";
                if(newx<0){
                    newx +=n;
                }
                if(newy<0){
                    newy += n;
                }
               // cout<<i<<" "<<j<<" ->"<<newy<<" "<<newx<<"\n";
                copy_nutrition[newy][newx] = 1;
            }
        }
    }
    // cout<<"move complete\n";
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<copy_nutrition[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
    nutrition = copy_nutrition;
}

void plus_nutrition(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(nutrition[i][j] == 1){
                space[i][j] ++;
            }
        }
    }
}

void injection_nut(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(nutrition[i][j] == 1){
                int count =0;
                for(int k=1;k<=4;k++){
                    int newx = j+dx[k*2];
                    int newy = i+dy[k*2];
                    if(newx>=0&&newx<n&&newy>=0&&newy<n){
                        if(space[newy][newx]>0){
                            count++;
                        }
                    }
                }
                space[i][j] += count;
            }
        }
    }
    // cout<<"injection complete\n";
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<space[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
}

void minus_nutrition(){
    vector<vector<int>>copy_nutrition(n, vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(nutrition[i][j] != 1){
                if(space[i][j] >=2){
                    space[i][j] -= 2;
                    copy_nutrition[i][j] = 1;
                }
            }
        }
    }
     nutrition = copy_nutrition;
    // cout<<"minus complete\n";
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<space[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
}

void result(){
    int answer =0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            answer += space[i][j];            
        }
    }
    cout<<answer;
}

int main() {
    cin>>n>>m;
    space.resize(n, vector<int>(n));
    nutrition.resize(n, vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>space[i][j];
        }
    }
    for(int i=n-2;i<=n-1;i++){
        for(int j=0;j<=1;j++){
            nutrition[i][j] = 1; // 영양제가 존재하는 곳
        }
    }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<space[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
    for(int i=0;i<m;i++){
        int direction, c;
        cin>>direction>>c;
        move_nut(direction ,c);
        plus_nutrition();
        injection_nut();
        minus_nutrition();
    }
    result();
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<space[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    return 0;
}