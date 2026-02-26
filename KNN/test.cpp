#include<bits/stdc++.h>

using namespace std;


int n = 10;

int main(){
    vector<int> vec;

    for(int i=0; i<n; i++){
        int temp;
        cin>>temp;
        vec.push_back(temp);
    }

    int mmin = *min_element(vec.begin(), vec.end());
    int mmax = *max_element(vec.begin(), vec.end());

    cout<<mmin<<" "<<mmax<<endl;
    return 0;
}