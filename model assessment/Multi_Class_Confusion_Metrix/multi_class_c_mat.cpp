#include <cmath>
#include<iostream>
#include<fstream>
#include <vector>
#include <math.h>


//class info
typedef struct{

  int total = 0;
  
  int TP = 0;
  int FP = 0;
  int FN = 0;
  int TN = 0;


  float precision = 0.0f;
  float recall = 0.0f;
  float specificity = 0.0f;
  float f_score = 0.0f;

  void calculation(){
    //cal prec
    precision = (TP + FP) == 0 ? 0 : float(TP)/(TP + FP);

    recall = (TP + FN ) == 0 ? 0 : float(TP)/(TP + FN);

    specificity = (TN + FP ) == 0 ? 0 : float(TN)/(TN + FP);

    f_score = (precision + recall ) == 0 ? 0 : 2*(precision * recall)/(precision + recall);

    
  }

  void print_data(){
    std::cout<<"printing calculation : "<<std::endl;

    std::cout<<"precision      :: "<<precision<<std::endl;
    std::cout<<"recall         :: "<<recall<<std::endl;
    std::cout<<"specificity    :: "<<specificity<<std::endl;
    std::cout<<"f-score        :: "<<f_score<<std::endl;
  }

  void print_mat_data(){
    std::cout<<"printing mat data"<<std::endl;

    std::cout<<"TP -> "<<TP<<std::endl;
    std::cout<<"FP -> "<<FP<<std::endl;
    std::cout<<"FN -> "<<FN<<std::endl;
    std::cout<<"TN -> "<<TN<<std::endl;
    std::cout<<"total ->"<<total<<std::endl;
  }
}Class;


//function prototype
void con_mat(std::string file_name);

int main(){
  std::string f_0 = "two.txt";
  std::string f_1 = "three.txt";
  std::string f_2 = "four.txt";

  int n;
  std::cout<<"enter 0 for "<<f_0<<std::endl;
  std::cout<<"enter 1 for "<<f_1<<std::endl;
  std::cout<<"enter 2 for "<<f_2<<std::endl;
  std::cin>>n;

  if(n == 0) con_mat(f_0);
  else if(n==1) con_mat(f_1);
  else if(n==2) con_mat(f_2);
  else{
    std::cout<<"invalid input"<<std::endl;
  }
  return 0;
}


//functions


void con_mat(std::string file_name){
  //take input
  std::fstream file(file_name);
  if(!file){
    std::cout<<"error reading input file "<<std::endl;
  }

  int temp;
  std::vector<int> data;

  while(file>>temp){
     data.push_back(temp) ;
  }

  // make it 2d

  int total = 0;

  for(auto u: data){
    total+=u;
  }

  int g = sqrt(data.size());
  //std::cout<<g<<std::endl;
  // g = number of class

  //create a 2d arr of g*g aka confusion matrinx

  std::vector<std::vector<int>> mat(g, std::vector<int>(g));

  int idx = 0;

  for(int i=0; i<g; i++){
    for(int j =0; j<g; j++){
      mat[i][j] =data[idx++];
    }
  }


  //printing the metrix
  std::cout<<"printing confusion matrix"<<std::endl;
  for(int i=1; i<=g; i++){
   std:: cout<<" \t"<<"CLS-"<<i;
  }std::cout<<std::endl;
  int print_c_mat_idx =1;
  for(auto u: mat){
   std::cout<<"CLS-"<<print_c_mat_idx++<<" \t";
     for(auto j: u){
     std:: cout<<j<<" \t";
    }std:: cout<<std::endl;
  }
  std::cout<<std::endl<<std::endl;


  // create the points for each data porints
  std::vector<Class> class_data;

  for(int i=0; i<g; i++){
    Class temp;

    //tp done
    int temp_tp = mat[i][i];

    //fp done
    int temp_fp = 0;
    for(int k=0; k<g; k++){
      if(i==k){
        continue;
      }else{
        temp_fp+=mat[k][i];
      }
    }

    //fn

    int temp_fn = 0;
    for(int k=0;k<g; k++){
      if(i==k) continue;
      else{
        temp_fn += mat[i][k];
      }
    }

    
    int temp_tn = total - temp_tp - temp_fp - temp_fn;

    temp.TP = temp_tp;
    temp.FP = temp_fp;
    temp.FN = temp_fn;
    temp.TN = total - temp.TP - temp.FP - temp.FN;

    temp.total = total ;

    //calculate
    temp.calculation();

    class_data.push_back(temp);
  }


  //calculating the acc

  int total_tp = 0 ;

  for(auto u:class_data){
    total_tp += u.TP;
  }

  float acc = float(total_tp)/total;

  

  int class_idx = 1 ;
  for(auto u: class_data){
   std::cout<<"class -+ "<<class_idx++<<std::endl;
   u.print_mat_data();
   std::cout<<std::endl;
   u.print_data();
   std::cout<<std::endl;
    }


  std::cout<<"total accuracy : "<<acc<<std::endl;
  
}
