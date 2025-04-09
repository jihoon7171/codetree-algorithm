#include <iostream>
#include<vector>
using namespace std;
int l,n,q;
struct gisa{
    int r;
    int c;
    int h;
    int w;
    int k;
};
vector<gisa>all_gisa;
vector<gisa>copy_all_gisa;
vector<vector<pair<int, int>>>chess;
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};

void remove(int i, int d, vector<vector<pair<int, int>>>&copy_chess){
    int r = all_gisa[i].r;
    int c = all_gisa[i].c;
    int h = all_gisa[i].h;
    int w = all_gisa[i].w;
    int newr = r+dy[d];
    int newc = c+dx[d];
    for(int i = r;i<=r+h-1;i++){
        for(int j=c;j<=c+w-1;j++){
            copy_chess[i][j].second = 0; // 죽은 병사 다 지움
        }
    }
}

void cout_copy(vector<vector<pair<int, int>>>copy_chess){
    for(int i=1;i<=l;i++){
        for(int j=1;j<=l;j++){
            cout<<copy_chess[i][j].second<<" ";
        }
        cout<<"\n";
    }
}

void damage(int i, int d, vector<vector<pair<int, int>>>&copy_chess, int index){
    if( i == index) return;
    int r = all_gisa[i].r;
    int c = all_gisa[i].c;
    int h = all_gisa[i].h;
    int w = all_gisa[i].w;
    int newr = r+dy[d];
    int newc = c+dx[d];
    for(int j = r;j<=r+h-1;j++){
        for(int k=c;k<=c+w-1;k++){
            if(chess[j][k].first == -2){
                all_gisa[i].k--;
                if(all_gisa[i].k < 0){
                    remove(i, d, copy_chess);
                    return ; // 아예 죽어서 끝남
                }
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //   //  cout<<i<<" 피"<<all_gisa[i].k<<" \n";
    // }
    //cout<<"데미지 준 이후 복사본"<<"\n";
   // cout_copy(copy_chess);
}


void gisa_move(int i,int d, vector<vector<pair<int, int>>>&copy_chess, vector<bool>visited, int index){
    if(visited[i]) return;
    visited[i] = true;
   // cout_copy(copy_chess);
    vector<vector<pair<int, int>>>copy_chess_copy(copy_chess);
  //  cout<<"이동 전\n";
    int r = all_gisa[i].r;
    int c = all_gisa[i].c;
    int h = all_gisa[i].h;
    int w = all_gisa[i].w;
    int newr = r+dy[d];
    int newc = c+dx[d];
   //cout<<i<<"움직임 시작"<<r<<c<<"\n";
    for(int j=r;j<=r+h-1;j++){
        for(int k=c;k<=c+w-1;k++){
            int newj = j+dy[d];
            int newk = k+dx[d];
            if(copy_chess[newj][newk].second == 0){
                copy_chess[newj][newk].second = i;
            }else if(copy_chess[newj][newk].second != i){
                gisa_move(copy_chess[newj][newk].second, d,copy_chess, visited, index);
            }else{
                copy_chess[newj][newk].second = i;
            }
        }
    }

    if(d==0){
        for(int i=c;i<=c+w-1;i++){
            copy_chess[r][i].second = 0;
        }
    }

    if(d==2){
        for(int i=c;i<=c+w-1;i++){
            copy_chess[r+h-1][i].second = 0;
        }
    }

    if(d==3){
        for(int i=r;i<=r+h-1;i++){
            copy_chess[i][c+w-1].second = 0;
        }
    }
    if(d==1){
        for(int i=r;i<=r+h-1;i++){
            copy_chess[i][c].second = 0;
        }
    }


    all_gisa[i].r = newr;
    all_gisa[i].c = newc;

   // cout<<i<<" 번째가 움직입니다\n";
   // cout_copy(copy_chess);
   // cout<<"\n";
    damage(i, d, copy_chess, index);
}

void moving(int i,int d, bool original , vector<vector<pair<int, int>>>&copy_chess, int index){
    vector<bool>visited(n+1, false);
    int r = all_gisa[i].r;
    int c = all_gisa[i].c;
    int newr = r+dy[d];
    int newc = c+dx[d];
    bool flag = true;
   // cout<<"moving start"<<i<<d<<"\n";
    for(int j=r;j<=r+all_gisa[i].h-1;j++){
        for(int k=c; k<=c+all_gisa[i].w-1;k++){
            int newj = j+dy[d];
            int newk = k+dx[d];
            if(copy_chess[newj][newk].first == -1){ //벽이거나 범위를 넘어설때
             //   cout<<"벽 입니다"<<"\n";
                flag = false;
                return ;
            }else if(copy_chess[newj][newk].second != 0 && copy_chess[newj][newk].second !=i){
                int new_index = copy_chess[newj][newk].second;
              //  cout<<j<<","<<k<<" "<<"앞"<<d<<"위치에"<<new_index<<"존재"<<"\n";
                moving(new_index,d, false, copy_chess, index);
                //자기자신 혹은 비어있을 경우 -> 이동 가능
            }else if(chess[newj][newk].second == chess[j][k].second || chess[newj][newk].first == 0){
              //  cout<<"이다음엔 나자신 존재"<<"\n";
                break;
            }

        }
    }
    //나와 연관된 것들 모두 움직이고나서 다시한번 내가 움직일 수 있나 체킹 - 안움직이면 복사하지말고 움직일 수 있으면 복사할 것
    bool can_move = false;
    for(int j=r;j<=r+all_gisa[i].h-1;j++){
        for(int k=c; k<=c+all_gisa[i].w-1;k++){
            int newj = j+dy[d];
            int newk = k+dx[d];
            if(copy_chess[newj][newk].first == -1){ //벽이거나 범위를 넘어설때
               // cout<<"이건 결과적으로 움직일 수 없습니다 벽이어서"<<"\n";
                can_move =false;
                return;
            }else if(copy_chess[newj][newk].second != 0 && copy_chess[newj][newk].second !=i){
               // cout<<"이건 결과적으로 움직일 수 없습니다 다른것이 존재해서\n";
                can_move = false;
            }else if(copy_chess[newj][newk].first == -2){
                can_move = true;
               // cout<<j<<k<<newj<<newk<<"\n";
              //  cout<<i<<"함정이 존재하는 곳으로 이동했습니다"<<"\n";
               break;
            }else if(copy_chess[newj][newk].second == chess[j][k].second || copy_chess[newj][newk].first == 0){
                can_move = true;
                continue;
            }

        }
    }
    if(!original && can_move){
       // cout<<i<<"번째는 "<<d<<"방향으로 움직일겁니다"<<"\n";
        gisa_move(i,d, copy_chess, visited, index);
      //  cout_copy(copy_chess);
      //  cout<<"\n";

    }

    if(original && can_move){

        gisa_move(i, d, copy_chess, visited, index);
        chess = copy_chess;
       // cout<<"모든걸 원래맵에 적용시킵니다\n";
        //cout_copy(copy_chess);
        // cout<<"\n";
    }

}



void result(){
    int answer = 0;
    for(int i=1;i<=n;i++){
        if(all_gisa[i].k > 0){
            answer += copy_all_gisa[i].k - all_gisa[i].k;
           // cout<<i<<" 번째 기사 남은 체력\n";
            //cout<<copy_all_gisa[i].k - all_gisa[i].k<<"\n";
        }
    }
    cout<<answer;
}

int main() {
    cin>>l>>n>>q;
    chess.resize(l+2, vector<pair<int, int>>(l+2, {-1,0}));
    all_gisa.resize(n+1);
    for(int i=1;i<=l;i++){
        for(int j=1;j<=l;j++){
            chess[i][j].first = 0;
        }
    }// 사방이 벽으로 둘러쌓여있고 0으로 다 초기화 완료
    for(int i=1;i<=l;i++){
        for(int j=1;j<=l;j++){
            int a;
            cin>>a;
            if(a == 2){
                a = -1;
            }else if(a == 1){
                a = -2;
            }
            chess[i][j].first = a;
        }
    }

    for(int i=1;i<=n;i++){
        cin>>all_gisa[i].r>>all_gisa[i].c>>all_gisa[i].h>>all_gisa[i].w>>all_gisa[i].k;
        int r = all_gisa[i].r;
        int c = all_gisa[i].c;
        int h = all_gisa[i].h;
        int w = all_gisa[i].w;
        int k = all_gisa[i].k;
        //cout<<r<<r+h-1<<"\n";
        //cout<<c<<c+w-1<<"\n";
        for(int j=r;j<=r+h-1;j++){
            for(int k=c;k<=c+w-1;k++){
                chess[j][k].second = i; 
            }
        }
    }

    // for(int i=1;i<=l;i++){
    //         for(int j=1;j<=l;j++){
    //             cout<<chess[i][j].second<<" ";
    //         }
    //         cout<<"\n";
    //     }

    copy_all_gisa = all_gisa;
    for(int j=1;j<=q;j++){
        int i,d;
        cin>>i>>d;
        vector<vector<pair<int, int>>>copy_chess(chess);
    
        moving(i,d,true, copy_chess,i);
    }
    result();




    return 0;
}