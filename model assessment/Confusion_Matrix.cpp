#include<iostream>
#include<vector>
#include<map>
#include<math.h>

int main(){

  std::vector<int> instance = {1,2,3,4,5,6,7,8,9,10,11,12};

  std::vector<int> acc_class = {1,1,1,1,1,1,1,1,0,0,0,0};
  std::vector<int> pred_class = {0,0,1,1,1,1,1,1,1,0,0,0};

  std::map<int, std::string> result_map;

  result_map[1] ="TP"; //  true positive = correctly predicted positive case
  result_map[2] ="TN"; //  true negative = correctly predicted negative case

  result_map[3] ="FP"; // false positive = incorrectly predicted positive case
  result_map[4] ="FN"; // false negative = incorrectly predicted negative case

  std::vector<std::string> res_cal;

  for(int i=0; i<acc_class.size(); i++){
    if(acc_class[i] == 1 && pred_class[i]==1 ){
      // tf case
      res_cal.push_back(result_map[1]);
    }
    else if(acc_class[i]==0 && pred_class[i]==0){
      //tn case
      res_cal.push_back(result_map[2]);
    }
    else if(acc_class[i] == 0 && pred_class[i] == 1 ){
      //fp class
      res_cal.push_back(result_map[3]);
    }
    else if(acc_class[i]== 1 && pred_class[i]==0){
      // false negative case
      res_cal.push_back(result_map[4]);
    }
  }



  //printing the result
  //

  for(auto u: res_cal){
    std::cout<<u<<" ";
  }std::cout<<std::endl;


  //creating the reverse map

  std::map<std::string, int> rev_map;

  for(auto &u:result_map){
    rev_map[u.second] = 0;
  }

    
  for(auto &u: res_cal){
      rev_map[u] = rev_map[u] + 1 ;
  }


  for(auto &u: rev_map){
    std::cout<<u.first<<u.second<<std::endl;
  }


  //printing the confution matrix
  
  std::cout<<"true  positive [TP] = "<<rev_map["TP"]<<" \t false negative [FN] = "<<rev_map["FN"]<<std::endl;
  std::cout<<"False positive [FP] = "<<rev_map["FP"]<<" \t  true negative [TN] = "<<rev_map["TN"]<<std::endl;


  std::cout<<"-------------------------------------------\n";
  std::cout<<"prediction condition :"<<std::endl;
  std::cout<<"fit = "<< rev_map["TP"] + rev_map["FP"]<<" \tUnfit = "<<rev_map["FN"] + rev_map["TN"]<<std::endl;
  std::cout<<"-------------------------------------------\n";
 

  
  std::cout<<"-------------------------------------------\n";
  std::cout<<"actual condition :"<<std::endl;
  std::cout<<"fit = "<<rev_map["TP"] + rev_map["FN"]<<" \t unfir = "<<rev_map["FP"] + rev_map["TN"]<<std::endl;

  std::cout<<"-------------------------------------------\n";
 

  int tp = rev_map["TP"];
  int fn = rev_map["FN"];
  int fp = rev_map["FP"];
  int tn = rev_map["TN"];


  //accuracy test

  float acc = ( tp + tn )*1.00/(tp + tn + fp + fn);

  float precision = (tp*1.00)/(tp+fp);

  float sensitivity = (tp*1.00)/(tp+fn);

  float specificity = (tn*1.00)/(tn + fp);

  float recall = (tp*1.00)/(tp + fn);

  int beta = 1;

  float f_measure = ((1 + pow(beta, 2)) * precision * recall )/((pow(beta, 2)*precision)+recall);
  

  std::cout<<"accuracy\t= "<<acc<<std::endl;
  std::cout<<"precision\t= "<<precision<<std::endl;
  std::cout<<"sensitivity\t= "<<sensitivity<<std::endl;
  std::cout<<"specificity\t= "<<specificity<<std::endl;
  std::cout<<"recall\t = "<<recall<<std::endl;

  std::cout<<"f-measure ["<<beta<<"]\t = "<<f_measure<<std::endl;
  
  return  0;
}
