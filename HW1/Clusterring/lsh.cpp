#include "lsh.hpp"
#include "functionalities.hpp"
#include "clusterring_functions.hpp"
#include <cmath>
#include <climits>


vector<vector<vector<long long unsigned int>>> hash_tables;

vector<vector<double>> v;

vector<vector<vector<double>>> h;

vector<vector<int>> g;

vector<int> r;

int w = 650;

int TableSize;


void create_hash_tables()
{
    TableSize = n/8;
    hash_tables.resize(L);                                    //L hash tables
    for (int i=0; i<L; i++) hash_tables[i].resize(TableSize);    //Each has size == n
    h.resize(L);                                                  //L "teams" of hash functions
    for (int i=0; i<L; i++) h[i].resize(k);                        //Each team has k hash functions
    for (int i=0; i<L; i++) {
      for (int j=0; j<k; j++) h[i][j].resize(n);                    //Each hash function is for one vector-point
    }
    g.resize(L);                                                    //L "teams" of g functions
    for (int i=0; i<L; i++) g[i].resize(n);                         //Each g is for one vector-point
    r.resize(k);
    v.resize(n);
}

void create_hash_functions(int table)
{
  srand(time(NULL));
  int dimension;
  string vec;
  for (int j = 0; j < k && table == 0; j++) {
      r[j] = rand()%(INT_MAX);                            //Initiallize the random r vector (only one time)
  }
  for (int i=0; i<p.size(); i++)  {                        //For each vector-point
    dimension = p[i].size();                                //Take the dimension
    for (int y = 0; y < k; y++) {                           //k times
        //Compute v
        v[i].resize(dimension);
        for (int j = 0; j < dimension; j++) {
            double a = normal_distribution_generator();
            v[i][j] = a;
        }
        double innerProduct = inner_product(p[i],v[i], dimension);                        //Compute inner product between of p and v
        float t = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/w));      //Take a random t
        double sum = innerProduct + t;
        h[table][y][i] = floor(double(sum/(double) w));                                 //Compute h
    }
    //Compute g (the bucket)
      long long unsigned int sum = 0;
      long long int number = 0;
      long long unsigned int M = 4294967291;
      //Calculate modulo partially to avoid overflows
      for (int j = 0; j < k; j++) {
          number = modulo(r[j]*h[table][j][i],M);
          sum += number;
      }

      sum = modulo(sum,M);
      sum = modulo(sum,TableSize);
      g[table][i] = sum;
      hash_tables[table][sum].push_back(i);           //Insert the vector-point to the right bucket of the right vector of hash table
  }
}

long long int hash_query(vector<double> query)
{
  int dimension = query.size();
  vector < long long unsigned int> h_function;
  h_function.resize(k);
  //Calculate each of k h functions
  for (int y = 0; y < k; y++) {
    vector<double> ndg;
    ndg.resize(dimension);
    //Create the v vector
    for (int i = 0; i < dimension; i++) {
        double a = normal_distribution_generator();
        ndg[i] = a;
    }
    double innerProduct = inner_product(query,ndg, dimension);
    float t = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/w));
    double sum = innerProduct + t;
    h_function[y] = floor(double(sum/(double) w));
  }
  //Calculate g function
  long long unsigned int g = 0;
  long long int number = 0;
  long long unsigned int M = 4294967291;
  for (int j = 0; j < k; j++) {
      number = modulo(r[j]*h_function[j],M);
      g += number;
  }
  g = modulo(g,M);
  g = modulo(g,TableSize);
  return g;
}


vector<int> range_search(int id, vector<double> query,float r)            //range search with lsh
{
  vector<int> b;
  vector<double> dist;
  bool f;
  for (int i = 0; i < L; i++) {                   //for each hash table
    int bucket = hash_query(query);               //Hash the query and take the bucket
    for (int j=0; j<hash_tables[i][bucket].size(); j++) {         //For each bucket
        if (exists(b,hash_tables[i][bucket][j]) || marked[hash_tables[i][bucket][j]]) continue;       //If we have checked or assigned it to a cluster ignore ite
        double euc_dist = euclidian_distance(query, p[hash_tables[i][bucket][j]]);
        if (euc_dist < r && euc_dist!=0) b.push_back(hash_tables[i][bucket][j]);          //If the distance is smaller than r keep it
    }
  }
  return b;
}
