//to do
// read data [done]
// get two random points [done]
//initial [ done ]
// do the final calculation
//      1. get the new two points of the clusters
//      2. calculater the cluster again
//      3. print the cluster
//      
//      

#include<bits/stdc++.h>

using namespace std;

typedef struct {
  char name;
  int x;
  int y;
}point;



//functions
//pick two random idx
pair<int, int> random_idx(int n);
//calculate the initial clustering
pair<vector<point>, vector<point>> cal_init_clus(vector<point>& data, pair<int, int>& idx);
float cal_dis(point a, point b);
void print_cluster(pair<vector<point>, vector<point>>& cls);

pair<pair<float, float>,pair<float, float>> cal_new_point(pair<vector<point>, vector<point>>& cluster);

pair<vector<point>, vector<point>> cal_new_clus(vector<point>&data, pair<pair<float, float>, pair<float, float>>& new_points);

float cal_dis_2(float x1, float x2, float y1, float y2);










int main(){

  cout<<"hello world"<<endl;
  //read data
  string f_name = "input_data.txt";
  ifstream file(f_name);

  if(!file){
    cout<<"error at opening the input file"<<endl;
    return 1;
  }


  //temp data for input
  point temp;
  vector<point> data;
  while(file>>temp.name>>temp.x>>temp.y){
    data.push_back(temp);
  }


  // for(auto u: data) cout<<u.name<<u.x<<u.y<<endl;
  file.close();

  pair<int, int> idx = random_idx(data.size());

  cout<<idx.first<<'\t'<<idx.second<<endl;
  pair<vector<point>, vector<point>> init = cal_init_clus(data, idx);


  //first iteration
  cout<<"first iteration"<<endl;
  //now calculate the mean x, y of each cluster
  pair<pair<float, float>,pair<float, float>> new_point = cal_new_point(init);
  // got the new points in "new_points"
  pair<vector<point>, vector<point>> new_clus = cal_new_clus(data, new_point);

  //second iteration
  cout<<"second iteration"<<endl;cld
  pair<pair<float, float>,pair<float, float>> new_point_2 = cal_new_point(new_clus);
  pair<vector<point>, vector<point>> new_clus_2 = cal_new_clus(data, new_point_2);




  return 0;
}

pair<int, int> random_idx(int n){
    srand(time(0));

    int r1  = rand() % n;
    int r2 = rand() % n;
    while(r1==r2){
      r2 = rand() % n;
    }

    pair<int, int> idx;
    idx.first = r1;
    idx.second = r2;

    return idx;
  }

pair<vector<point>, vector<point>> cal_init_clus(vector<point>& data, pair<int, int>& idx){
  pair<vector<point>, vector<point>> res;

  for(auto u: data){
    float dis1 = cal_dis(u, data[idx.first]);
    float dis2 = cal_dis(u, data[idx.second]);

    if(dis1<dis2){
      res.first.push_back(u);
    }else{
      res.second.push_back(u);
    }

  }

  print_cluster(res);

  return res;
}

float cal_dis(point a, point b){
  float p = float (a.x - b.x);
  float q = float (a.y - b.y);
  return sqrt(p*p + q*q);
}

void print_cluster(pair<vector<point>, vector<point>>& cls){
  cout<<"first cluster"<<endl;
  cout<<"name\tX\tY"<<endl;
  for(auto u: cls.first){
    cout<<u.name<<"\t"<<u.x<<'\t'<<u.y<<endl;
  }

  cout<<"second cluster"<<endl;
  cout<<"name\tX\tY"<<endl;
  for(auto u: cls.second){
    cout<<u.name<<"\t"<<u.x<<'\t'<<u.y<<endl;
  }
}

pair<pair<float, float>,pair<float, float>> cal_new_point(pair<vector<point>, vector<point>>& cluster){
  pair<pair<float, float>,pair<float, float>> res;

  //for the first cluster
  float x1=0.0;
  float y1=0.0;
  for(auto u:cluster.first){
    x1+=float(u.x);
    y1+= float(u.y);
  }
  x1/=cluster.first.size();
  y1/=cluster.second.size();


  float x2 = 0.0;
  float y2 = 0.0;

  for(auto u:cluster.second){
    x2 += float(u.x);
    y2 += float(u.y);
  }

  x2/=cluster.second.size();
  y2/=cluster.second.size();

  res.first.first = x1;
  res.first.second = y1;

  res.second.first = x2;
  res.second.second = y2;
  

  //printing the new points
  cout<<"first points-->"<<res.first.first<<'\t'<<res.first.second<<endl;
  cout<<"first points-->"<<res.second.first<<'\t'<<res.second.second<<endl;

  return res;
}

pair<vector<point>, vector<point>> cal_new_clus(vector<point>&data, pair<pair<float, float>, pair<float, float>>& new_points){
  pair<vector<point>, vector<point>> new_cluster;

  for(auto u: data){
    float dis_1 = cal_dis_2(float(u.x), float(u.y), new_points.first.first, new_points.first.second );
    float dis_2 = cal_dis_2(float(u.x), float(u.y), new_points.second.first, new_points.second.second);

    if(dis_1<dis_2){
      new_cluster.first.push_back(u);
    }else{
      new_cluster.second.push_back(u);
    }
  }

  print_cluster(new_cluster);

  return new_cluster;
}
float cal_dis_2(float x1, float y1, float x2, float y2){
  float p = x1-x2;
  float q = y1 - y2;

  return (sqrt(p*p + q* q));
}