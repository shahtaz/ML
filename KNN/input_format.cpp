#include<bits/stdc++.h>

using namespace std;

#define pb push_back

int num_of_feature = 4;

int main(){

    ofstream file("data.txt", ios::app);

    if(!file){
        cout<<"error at opening file"<<endl;
        return 1;
    }

    int temp;
    int count = 0;
    vector<int> raw_data;
    while(cin>>temp){
        raw_data.pb(temp);
        count++;
    }

    for(int i=0; i<raw_data.size(); i++){
        file<<raw_data[i]<<" ";
        if((i+1)% num_of_feature == 0 ){
            file<<'\n';
        }
    }
    file.close();


    return 0;
}