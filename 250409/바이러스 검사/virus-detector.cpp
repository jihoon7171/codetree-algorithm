#include <iostream>
using namespace std;
#include<vector>

long long n,c,a,b;
vector<long long>res;
int main() {
    cin>>n;
    res.resize(n,0);
    for(int i=0;i<n;i++){
        cin>>res[i];
    }
    cin>>a>>b;
    long long count=0;
    for(int i=0;i<n;i++){
        long long human = res[i];
        human -= a;
        count++;
        //cout<<human<<" ";
        if(human >0){
            while(human>0){
                if(human <= b){
                    count++;
                    human -= b;
                    //cout<<human<<" ";
                }else{
                    count += human/b;
                    int temp = human/b;
                    human -= temp*b;
                }
            }
        }
        //cout<<count<<" ";
        //cout<<"\n";
    }
    cout<<count;
}