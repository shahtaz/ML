#include<iostream>
#include<vector>
#include<algorithm>
#include <random>


// to do
// holdout validation
// k fold cross

// init data poit* -> randomize it* -> do the both algo


//functions

void holdout_validation(std::vector<int> data);

void k_fold(std::vector<int> data, int k);


int main(){

  std::vector<int> arr;

  int n = 50;


  for(int i=1; i<=n; i++) arr.push_back(i);

  std::random_device rd;
  std::mt19937 g(rd());

 shuffle(arr.begin(), arr.end(),g);


 //holdout validation
 // train test split
 holdout_validation(arr);


 //k_fold
 k_fold(arr, 5);

  return 0;
}



void holdout_validation(std::vector<int> data){
  int test_size = 20; //20%

  int test_point_number =(test_size/100.0)*data.size();

 // std::cout<<test_point_number<<std::endl;

 std::vector<int> train;
 std::vector<int> test;


 for(int i=0; i<test_point_number; i++) test.push_back(data[i]);

 for(int i=test_point_number; i<data.size(); i++) train.push_back(data[i]);



 //printing train  data points
 std::cout<<"pringing the train data points :";
 for(auto u: test) std::cout<<u<<" ";
 std::cout<<std::endl;



 //printing test  data points
 std::cout<<"printing the test data points :";
 for(auto u: train) std::cout<<u<<" ";
 std::cout<<std::endl; 
}




// k fold

void k_fold(std::vector<int> data, int k){
  std::cout<<"k_fold"<<std::endl;

  if(data.size()%k != 0){
    std::cout<<"invalid k value"<<std::endl;
  }else{
    // the main algo**
    int row = k ;
    int col = data.size()/k;

    std::vector<std::vector<int>> arr(row, std::vector<int>(col));

    int idx = 0 ;

    for(int i=0; i<row; i++){
      for(int j=0; j<col; j++){
      arr[i][j] = data[idx++];
    }
    }

    std::vector<char> label;
    label.push_back('A');
    for(int i=0; i<row-1; i++)label.push_back(label.back()+1);
     
    
    for(int i=0; i<row; i++){
      for(int j=0; j<col; j++){
        std::cout<<arr[i][j]<<"\t ";
      }
      std::cout<<'\t'<<"-->[ "<<label[i]<<" ]";
      std::cout<<std::endl;
    }



    std::cout<<"\n\n\n";\
    std::cout<<"printing the k folds sequence"<<std::endl;
    //printing the k_fold sequence
    int picked_frame = 0;
    int iterator = k;

    while(k--){
    for(int i=0; i<row; i++){
    if(i == picked_frame){
      std::cout<<"["<<label[i]<<"] \t";
    }else{
      std::cout<<label[i]<<" \t";
    }
    }
    std::cout<<std::endl;
    picked_frame++;
 }   
  }
}


