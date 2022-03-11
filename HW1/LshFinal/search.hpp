#include <vector>
#pragma once
using namespace std;

struct tuple_of_vectors{
  vector<int> v1;     //The index of each ponit
  vector<float> v2;   //The distance between the query and the point
};

void range_search(int id, vector<double> query);        //Range search for  Nearest neighbors
tuple_of_vectors knn(int id, vector<double> query);     //K approximate method nearest neighbor
tuple_of_vectors bf(int id, vector<double> query);      //Brute force method
