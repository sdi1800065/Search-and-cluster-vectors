#include "hash.hpp"
#include "tools.hpp"
#include <ctime>
#include <climits>
#include <cmath>
#include <random>
#include <chrono>
#include <unordered_map>
#include <iostream>
#include <iomanip>

//unordered is better for lookup ,we dont need to sort
unordered_map <int,char> bits;                      //Holds 0/1 values of the buckets
unordered_map <string, vector <int>> cube;          //Hypercubes master structure
vector <vector <int> > h;                           //Holds h numbers
vector<vector<double>> p;                           //Holds points
vector<vector<double>> v;

int n;
//After many tests 3500 seems to have the best results
int w = 4000;

//Stores the points.
void save_vectors()
{
  n = number_of_lines('i');
  p.resize(n);
  int dimension;
  string vec;
  for (int i=0; i<p.size(); i++)  {
    vec.assign(vector_data('i',i));
    dimension = vec.size();
    p[i].resize(dimension);
    for (int y = 0; y < k; y++) {
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
          p[i][j] = atof(words[j]);
        }
    }
  }
}

//Creates h functions and also maps buckets to {0,1} uniformly.
void create_h_functions()
{
  h.resize(k);
  srand(time(NULL));
  v.resize(n);
  for (int i=0; i<k; i++) h[i].resize(n);
  int dimension = p[0].size();
  for (int i=0; i<p.size(); i++) {       //For each vector-point
    string bit_string;
    for (int y = 0; y<k; y++) {           //k times
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
      h[y][i] = floor(double(sum/(double) w));

      //Coinflip
      f(h[y][i]);
      char c = bits[h[y][i]];
      //Gather coinflips to get the bucket key
      bit_string.push_back(c);
    }
    //if a bucket for this key has already been created push back the id , else make a new bucket and push back the id
    if ( cube.count(bit_string) > 0 ) {
        cube[bit_string].push_back(i);
    }
    else {
      vector < int > v;
      v.push_back(i);
      cube[bit_string] = v;
    }
  }
}

//Randomly choose 1 or 0 to map h(p) , if already choosen for this x then do nothing.
void f(int x)
{
    if ( bits.count(x) > 0 ) {

    }
     else {
       char c;
       int r = rand()%2;
       if (r == 0) c = '0';
       else c = '1';
       bits.insert({x, c});
    }

}

//Returns the bucket that the closest neighboughrs of a query should be
string hash_query(vector<double> query)
{
  int dimension = query.size();
  string bit_string;
  for (int i=0; i<k; i++) {
    vector<double> ndg;
    ndg.resize(dimension);
    //Create the v vector
    for (int i = 0; i < dimension; i++) {
        double a = normal_distribution_generator();
        ndg[i] = a;
    }
    //Calculate h
    double innerProduct = inner_product(query,ndg, dimension);
    float t = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/w));
    double sum = innerProduct + t;
    long long unsigned int h = floor(double(sum/(double) (w)));
    //Coinflip
    f(h);
    char c = bits[h];
    //Gather coinflips to get the bucket key
    bit_string.push_back(c);
  }
  return bit_string;
}
