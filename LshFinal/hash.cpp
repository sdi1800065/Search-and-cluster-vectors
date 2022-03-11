#include "hash.hpp"
#include "FileHandling.hpp"
#include "functionalities.hpp"
#include <ctime>
#include <climits>
#include <cmath>

vector<vector<vector<long long unsigned int>>> hash_tables;

vector<vector<double>> v;


vector<vector<vector<double>>> h;

vector<vector<int>> g;

vector<int> r;

vector<vector<double>> p;

int w = 650;

int TableSize;

vector <vector <long long unsigned int>> IDS;

void create_hash_tables()
{
    int n = number_of_lines('i');
    TableSize = n/8;
    hash_tables.resize(L);                              //L hash tables
    for (int i=0; i<L; i++) hash_tables[i].resize(TableSize);   //Each has size == n
    h.resize(L);                                        //L "teams" of hash functions
    for (int i=0; i<L; i++) h[i].resize(k);             //Each team has k hash functions
    for (int i=0; i<L; i++) {                           //Each hash function is for one vector-point
      for (int j=0; j<k; j++) h[i][j].resize(n);
    }
    g.resize(L);                                      //L "teams" of g functions
    for (int i=0; i<L; i++) g[i].resize(n);           //Each g is for one vector-point
    r.resize(k);                                  //r vector
    p.resize(n);
    IDS.resize(L);
    for (int i=0; i<L; i++) IDS[i].resize(n);
    v.resize(n);
}


void create_hash_functions(int table)
{
  srand(time(NULL));
  int dimension;
  string vec;
  for (int j = 0; j < k && table == 0; j++) {               //Initiallize the random r vector (only one time)
      r[j] = rand()%(INT_MAX);
  }
  for (int i=0; i<p.size(); i++)  {                       //For each vector-point
    if (table == 0) {                                     //Only th first time store alll vector-points

        vec.assign(vector_data('i',i));                   //Take the vector
        dimension = vec.size();
        p[i].resize(dimension);

    }

    else dimension = p[i].size();     //If its not the first time we have already the dimension

    for (int y = 0; y < k; y++) {                 //k times
        if (table == 0) {                         //Only thi first time
          //This piece of code takes all numbers of the vector-point and put eache of them in a cell of array words
          char words[vec.size()][15];
          int j=0, ctr=0;
          for(int l=0;l<=vec.size();l++){
              if(vec[l]==' '||vec[l]=='\0'){
                words[ctr][j]='\0';
                ctr++;
                j=0;
              }
              else{
                words[ctr][j]=vec[l];
                j++;
              }
          }
          dimension = ctr;
          p[i].resize(dimension);
          for (j=0; j<dimension; j++) {
            p[i][j] = atof(words[j]);     //Create the vector-point
          }
	      }
          v[i].resize(dimension);
          //Create the v vector
          for (int j = 0; j < dimension; j++) {
              double a = normal_distribution_generator();
              v[i][j] = a;
          }
        //Compute the h function
        double innerProduct = inner_product(p[i],v[i], dimension);
        float t = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/w));
        double sum = innerProduct + t;
        h[table][y][i] = floor(double(sum/(double) w));
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
      IDS[table][i] = sum;
      sum = modulo(sum,TableSize);
      g[table][i] = sum;
      hash_tables[table][sum].push_back(i);     //Insert the vector-point to the right bucket of the right vector of hash table
  }
}

long long int hash_query(vector<double> query, long long unsigned int *ID)
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
  *ID = g;
  g = modulo(g,TableSize);
  return g;
}
