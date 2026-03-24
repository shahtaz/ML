
#include<iostream>
#include <string>
#include<vector>
#include<fstream>
#include<utility>
#include<map>
#include<string>



// var for data points

typedef struct{
  std::string day;
  std::string outlook;
  std::string temp;
  std::string humidity;
  std::string wind;
  std::string play;
}DATA;


//function prototype
std::vector<DATA> get_input(std::string f_name);
std::pair<int, int> get_yes_no(std::vector<DATA>& data);


//main calculation
std::map<std::string, std::map<std::string, float>>  get_table(std::vector<DATA>& data, int n);
std::map<std::string, std::map<std::string, float>>  calculate(std::vector<std::string>& vec, std::vector<std::string> &play);

void print_table(std::map<std::string, std::map<std::string, float>> &table);

int main(){

  std::cout<<"neive bayes"<<std::endl;

  //read data;

  std::string f_name = "input.txt";
  
  std::vector<DATA> input = get_input(f_name);


  //get the yes and no
  // pair.firt = yes | pair.second = no

  std::pair<int, int> yes_no = get_yes_no(input);

  std::cout<<"yes count = "<<yes_no.first<<std::endl;
  std::cout<<"no  count = "<<yes_no.second<<std::endl;


  //get the tables

  std::map<std::string, std::map<std::string, float>> outlook_table = get_table(input, 1);
  std::map<std::string, std::map<std::string, float>> temp_table = get_table(input, 2);
  std::map<std::string, std::map<std::string, float>> humidity_table = get_table(input, 3);
  std::map<std::string, std::map<std::string, float>> wind_table = get_table(input, 4);


  //printing the table
  print_table(outlook_table);
  print_table(temp_table);
  print_table(humidity_table);
  print_table(wind_table);

  //test phase start from here
  // 1. read test data
  // 2. look up table
  // 3. apply MAP rule
  // 4. show the predicted output

  DATA test;
  test.outlook = "Sunny";
  test.temp = "Cool";
  test.humidity = "High";
  test.wind = "Strong";


  // pair.first = yes +--+ pair.second = no
  
  std::pair<float, float> prob_outlook; 
  std::pair<float, float> prob_temp;
  std::pair<float, float> prob_humidity;
  std::pair<float, float> prob_wind;
  
  std::pair<float, float> prob_play;

  std::string y = "Yes";
  std::string n = "No";

  //calculate

  prob_outlook.first = (outlook_table[test.outlook][y]*1.00)/yes_no.first;
  prob_outlook.second = (outlook_table[test.outlook][n]*1.00)/yes_no.second;

  prob_temp.first = (temp_table[test.temp][y]*1.00)/yes_no.first;
  prob_temp.second = (temp_table[test.temp][n]*1.00)/yes_no.second;

  prob_humidity.first = (humidity_table[test.humidity][y]*1.00)/yes_no.first;
  prob_humidity.second = (humidity_table[test.humidity][n]*1.00)/yes_no.second;

  prob_wind.first = (wind_table[test.wind][y]*1.00)/yes_no.first;
  prob_wind.second = (wind_table[test.wind][n]*1.00)/yes_no.second;

  prob_play.first = (yes_no.first*1.00)/(yes_no.first + yes_no.second);
  prob_play.second = (yes_no.second*1.00)/(yes_no.first + yes_no.second);

  // do the map rule

  float pred_yes  = prob_outlook.first * prob_temp.first * prob_humidity.first * prob_wind.first * prob_play.first;
  
  float pred_no = prob_outlook.second * prob_temp.second * prob_humidity.second * prob_wind.second * prob_play.second;


  std::cout<<"P(yes) --> "<<pred_yes<<std::endl;
  std::cout<<"P(no)  --> "<<pred_no<<std::endl;

  if(pred_yes > pred_no){
    test.play = y;
  }else{
    test.play = n;
  }



  std::cout<<"final prediction = "<<test.play<<std::endl;

  
  return 0;
}


//functions


//fetch the data points
std::vector<DATA> get_input(std::string f_name){

  std::fstream file(f_name);
  if(!file){
    std::cout<<"error at reading file!!"<<std::endl;
  }

  std::string temp;
  std::vector<std::string> raw_data;
  
  while(std::getline(file, temp)){
    raw_data.push_back(temp);
  }

  //format the data

  std::vector<DATA>  data;

  int idx = 0;
  while(idx<raw_data.size()){
    DATA temp;

    temp.day = raw_data[idx++];
    temp.outlook = raw_data[idx++];
    temp.temp = raw_data[idx++];
    temp.humidity = raw_data[idx++];
    temp.wind = raw_data[idx++];
    temp.play = raw_data[idx++];

    data.push_back(temp);
     } 

  return data;
}

std::pair<int, int> get_yes_no(std::vector<DATA>& data){
  std::pair<int, int> res;

  std::string s_yes = "Yes";
  std::string s_no = "No";


  int yes = 0 ;
  int no = 0;

  for(auto &u: data){
    if(u.play == s_yes) yes++;
    else no++;
  }

  res.first = yes;
  res.second = no;


  return res;
}


std::map<std::string, std::map<std::string, float>>  get_table(std::vector<DATA>& data, int n){
  std::vector<std::string> outlook;
  std::vector<std::string> temp;
  std::vector<std::string> humidity;
  std::vector<std::string> wind;

  std::vector<std::string> play;

  for(auto &u: data){
    outlook.push_back(u.outlook);
    temp.push_back(u.temp);
    humidity.push_back(u.humidity);
    wind.push_back(u.wind);
    play.push_back(u.play);
  }

  if(n==1){
    //cal outlook
    return calculate(outlook, play);
  }else if(n==2){
    //cal temp;
    return calculate(temp, play);
  }else if(n == 3){
    //cal humidity
    return calculate(humidity, play);
  }else if(n==4){
    //cal wind
    return calculate(wind, play);
     }else{
    std::cout<<"invalid col value"<<std::endl;
  }
}


std::map<std::string, std::map<std::string, float>>  calculate(std::vector<std::string> &vec, std::vector<std::string> &play){

  std::map<std::string, std::map<std::string , float>> res;


  
  for(int i=0; i<play.size(); i++){
    res[vec[i]][play[i]]++;
  }

  for(auto &row: res){
    if(row.second.find("Yes")== row.second.end()){
      row.second["Yes"] = 0.0;
    }

    if(row.second.find("No")==row.second.end()){
      row.second["No"] = 0.0;
    }
  }

  return res;
}


void print_table(std::map<std::string, std::map<std::string, float>> &table){
  for(auto &row : table){
    std::cout<<row.first<<std::endl;
    for(auto &col : row.second){
      std::cout<<"\t-+ "<<col.first<<" +--+ "<<col.second<<std::endl; 
    }
  }
}
