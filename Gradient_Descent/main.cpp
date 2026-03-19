#include<bits/stdc++.h>


using namespace std;


float cal(float init_x){
  return ((init_x*2.00)+6.00);
}

float  update(float init_x, float alpha){
  return (init_x - (alpha * (cal(init_x))));
}


int main(){

  float init_x = 4.00;
  float alpha = 0.1;

  int iteration = 3 ;
  int count = 0 ;


  for(int i=0; i<iteration; i++){
    cout<<"iteration : "<<i+1<<endl;

    cout<<"initial value : X"<<count<<" = "<<init_x<<endl;

    cout<<"gradiant [f'("<<init_x<<")] ==> "<<cal(init_x)<<endl;

    
    cout<<"update : x"<<++count<<" = "<<update(init_x, alpha)<<endl;

    init_x = update(init_x, alpha);
    
  }


  return 0;
}
