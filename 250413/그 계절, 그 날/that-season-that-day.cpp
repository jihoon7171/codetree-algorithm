#include <iostream>

using namespace std;
int Y, M, D;

bool yoon(int Y){
    if(Y%4 == 0){
        if(Y%100 == 0){
            if(Y%400 == 0){
                return true;
            }else{
                return false;
            }
        }else{
            return true;
        }
    }else{
        return true;
    }
}

void season(int m){
    if(m >=3 && m<=5){
        cout<<"Spring";
    }else if(m >=6 && m<=8){
        cout<<"Summer";
    }else if(m>=9 && m<=11){
        cout<<"Fall";
    }else {
        cout<<"Winter";
    }
}

void checking(int y, int m, int d){
    if(m==1 || m==3 || m ==5 || m==7 || m == 8 || m ==10 || m == 12){
        season(m);
    }else if( m == 2){
        if(yoon(y)){
            if(d>30){
                cout<<-1;
            }else{
                season(m);
            }
        }else{
            if(d>29){
                cout<<-1;
            }else{
                season(m);
            }
        }
    }else{
        if(d>30){
            cout<<-1;
        }else{
            season(m);
        }
    }
}

int main() {
    cin >> Y >> M >> D;
    checking(Y,M,D);

    return 0;
}