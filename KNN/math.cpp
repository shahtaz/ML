// to do
// 0. read data [done] --> print input data [done]
// 1. data scalling [done] --> printint the scalled data [data]
// 2. get the distance
// 3. do the math
//
//

#include<bits/stdc++.h>

using namespace std;



void print_int_vec(vector<int>& vec, string name);
void print_float_vec(vector<float>& vec, string name);

vector<float> data_normalization(vector<int>& vec, string name);


//print table format

void print_orginal_data(vector<int>& age, vector<int>& height, vector<int>& weight, vector<int>& fit, string label_1, string label_2, string label_3, string label_4);

void print_norm_data(vector<float>& age, vector<float>& height, vector<float>& weight, vector<int>& fit, string label_1, string label_2, string label_3, string label_4);

int main(){

  //read the file
  vector<int> age;
  vector<int> height;
  vector<int> weight;
  vector<int> fit;

  string data_file = "data.txt";
  ifstream file(data_file);

  int temp;
  int  count = 1;
  while(file>>temp){
    if(count == 5) count = 1;

    if(count == 1) age.push_back(temp);
    else if(count == 2) height.push_back(temp);
    else if(count == 3) weight.push_back(temp);
    else if(count == 4) fit.push_back(temp);

    count++;
  }

  file.close();
  //input done

  print_int_vec(age, "age");
  print_int_vec(height, "height");
  print_int_vec(weight, "weight");
  print_int_vec(fit, "fit");


  //normalization data
  vector<float> norm_age = data_normalization(age, "age" );
  vector<float> norm_height = data_normalization(height, "height");
  vector<float> norm_weight = data_normalization(weight, "weight");


  

  print_orginal_data(age, height, weight, fit, "age", "height","weight", "fit");
  print_norm_data(norm_age, norm_height, norm_weight, fit, "norm_age", "norm_height", "norm_weight", "fint");
    
  return 0;
}



// the functions

void print_int_vec(vector<int>& vec, string name){
  cout<<"printing --> "<<name<<endl;
  for(auto u: vec){
    cout<<u<<"\t";
  }cout<<endl;

  cout<<endl;
}

void print_float_vec(vector<float>& vec, string name){
  cout<<"printing --> "<<name<<endl;

  for(auto u: vec){
    cout<<u<<"\t";
  }cout<<endl;
}

vector<float> data_normalization(vector<int>& vec, string name){

  vector<float> res;

  int int_min = *min_element(vec.begin(), vec.end());
  int int_max = *max_element(vec.begin(), vec.end());
  
  float float_min = (float) int_min;
  float float_max = (float) int_max;
  float bot = float_max - float_min;

  for(auto u: vec){
    float temp =(float) ((u-float_min)/(bot));
    res.push_back(temp);
  }


  //printing the value

  cout<<"printing min and max value of "<<name<<endl<<endl;
  cout<<"min\tmax"<<endl;
  
  cout<<int_min<<"\t"<<int_max<<endl<<endl;
  cout<<"normalized data "<<name<<endl;

  print_float_vec(res, name );

  cout<<endl<<endl;
  


  return res;
}



void print_orginal_data(vector<int>& age, vector<int>& height, vector<int>& weight, vector<int>& fit, string label_1, string label_2, string label_3, string label_4){
  cout<<"printing the orginal data"<<endl;
  cout<<label_1<<"\t"<<label_2<<"\t"<<label_3<<'\t'<<label_4<<'\t'<<endl;
  int l  = age.size();

  
  for(int i=0; i<l; i++){
    cout<<age[i]<<'\t'<<height[i]<<'\t'<<weight[i]<<'\t'<<fit[i]<<endl;
  }
  
}

void print_norm_data(vector<float>& age, vector<float>& height, vector<float>& weight, vector<int>& fit, string label_1, string label_2, string label_3, string label_4){
  int g = 8;
  cout<<"printing the normalized  data"<<endl;
  cout<<label_1<<"\t"<<label_2<<"\t"<<label_3<<'\t'<<label_4<<'\t'<<endl;
  int l  = age.size();
  cout<<fixed<<setprecision(5);
  for(int i=0; i<l; i++){
    cout<<age[i]<<"  \t"<<height[i]<<"  \t"<<weight[i]<<"  \t"<<fit[i]<<endl;
  }
  
}

