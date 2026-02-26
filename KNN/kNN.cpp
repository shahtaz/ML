#include<bits/stdc++.h>

using namespace std;



//other functions
//normalization
vector<double> normalization(vector<int>& arr);

double input_normalizatio(vector<int>& arr, double input);

//get the total dis vector
vector<double> cal_dis_vec(vector<double>& age, vector<double>& height, vector<double>& weight, double p_age, double p_height, double p_weight);

//calculate the dis between two points in 3d-mat 
double cal_dis(double a1, double b1, double c1, double a2, double b2, double c2);

//get the k index from the dis vector
vector<int> get_k_index(vector<double>& arr, int k);

int get_result(vector<int>& fit, vector<int>& k_index);

int main(){
    vector<int> age;
    vector<int> height;
    vector<int> weight;
    vector<int> fit;
    
    
    //read data from the file 
    ifstream file("data.txt");
    if(!file){
        cout<<"something is wrong and i can feel it"<<endl;
        return 1;
    }

    int temp;
    int count = 1;
    while(file>> temp){
        if(count == 5)count=1;

        if(count == 1)age.push_back(temp);
        else if(count == 2) height.push_back(temp);
        else if(count == 3) weight.push_back(temp);
        else if(count==4) fit.push_back(temp);

        count++;
    }
    file.close();
    //input done

    //cal the value of k
    int N = age.size();
    int k = sqrt(N);
    if(k%2==0)k++;


    //take input for prediction 
    int p_age;
    cout<<"enter age = ";
    cin>>p_age;

    int p_height;
    cout<<"enter height = ";
    cin>>p_height;

    int p_weight;
    cout<<"enter weight =";
    cin>>p_weight;


    // cout<<"age = "<< p_age<<"\theight = "<<p_height<<"\tweight ="<<p_weight<<endl;
    //cout<<"k-value ="<<k<<endl;

    //before calculating  the dis vec we need to normalize the data
    
    vector<double> norm_age = normalization(age);
    vector<double> norm_height = normalization(height);
    vector<double> norm_weight = normalization(weight);


    //pred - input normalization done;
    double norm_p_age = input_normalizatio(age,(double) p_age);
    double norm_p_height = input_normalizatio(height,(double) p_height);
    double norm_p_weight = input_normalizatio(weight,(double) p_weight);
    //normalization done

    // now calculate the distane between two points in the 3d mat

    vector<double> dis_vec = cal_dis_vec(norm_age, norm_height, norm_weight, norm_p_age, norm_p_height, norm_p_weight);

    vector<int> k_index = get_k_index(dis_vec, k);

    //get the result
    int p_fit = get_result(fit, k_index);
    //input donehow to


    cout<<"from the given  data the person fit is [ "<<p_fit<<" ]"<<endl;
}



//normalization
vector<double> normalization(vector<int>& arr){

    double arr_min = (*min_element(arr.begin(), arr.end()))*1.00;
    double arr_max = (*max_element(arr.begin(), arr.end()))*1.00;
    
    double diff = arr_max - arr_min;

    vector<double> res;

    for(int i=0; i<arr.size(); i++){
        if(diff== 0) res.push_back(0.0);
        else res.push_back(((arr[i]-arr_min)/diff)*1.00) ;
    }

    return res;
}

//input normalization
double input_normalizatio(vector<int>& arr, double input_data){

    double arr_min = (*min_element(arr.begin(), arr.end()))*1.00;
    double arr_max = (*max_element(arr.begin(), arr.end()))*1.00;
    
    double diff = arr_max - arr_min;
    if(diff == 0) return 0.00;
    return ((input_data - arr_min)/diff)*1.00;
}

//calculate the dis vector
vector<double> cal_dis_vec(vector<double>& age, vector<double>& height, vector<double>& weight, double p_age, double p_height, double p_weight){
    vector<double> res;

    for(int i=0; i<age.size(); i++)res.push_back(cal_dis(age[i], height[i], weight[i], p_age, p_height, p_weight));

    return res;
}

//calculate dis between two points in 3d mat
double cal_dis(double a1, double b1, double c1, double a2, double b2, double c2){
    return sqrt((pow((a1-a2),2) )+ (pow((b1-b2),2)) + (pow((c1-c2),2)));
}

//getting the lowest k index value based on lowest dis value
vector<int> get_k_index(vector<double>& arr, int k){
    vector<int> res;
    vector<int> visited(arr.size(), 0);

    for(int i=0; i<k; i++){
        double temp = DBL_MAX;
        int idx = 0;
        for(int j=0; j<arr.size(); j++){
            if(visited[j]==1) continue;
            if(arr[j]<temp){
                temp = arr[j];
                idx = j; 
            }
        }
        visited[idx] = 1;
        res.push_back(idx);
    }
    return res;
}


int get_result(vector<int>& fit, vector<int>& k_index){

    int one = 1;
    int zero = 0;

    int count_one  = 0;
    int count_zero = 0;

    for(auto u: k_index){
        if(fit[u]==one) count_one++;
        else if(fit[u]==zero)count_zero++;
    }
    if(count_one>count_zero) return 1;
    else return 0;
}