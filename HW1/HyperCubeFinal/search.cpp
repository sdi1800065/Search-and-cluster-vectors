#include <iostream>
#include <limits>
#include <cmath>
#include "search.hpp"
#include "tools.hpp"
#include "hash.hpp"




tuple_of_vectors knn(int id, vector<double> query)
{
  tuple_of_vectors tupl;
  tupl.v1.resize(N);
  tupl.v2.resize(N);
  bool f;
  int checked_probes = 0,checked_points = 0;
  int dist = 1;
  int bit = 0;
  for (int i=0; i<N; i++) tupl.v2[i] = numeric_limits<float>::infinity();                //Initiallize with infinity the distance table
      string bucket = hash_query(query);                        //Hash the query and take each id
      while (checked_probes < probes && checked_points < M) { //for each probe
        if (cube.count(bucket) == 0) { //Bucket is not found
          if (bit == nChoosek(bucket.size(),dist)) {      //When you find all the possible combiantions hamming distance dist of our bucket
              dist++;
              bucket = hamming_distance(dist, bit, bucket);
          }
          else {
            bucket = hamming_distance(dist, bit, bucket);
          }
        }
        else {
          for (int j=0; j<cube[bucket].size(); j++) {
              if (checked_points > M) break;                              //If we have checked the maximum number of points stop the loop
              if (exists(tupl.v1,cube[bucket][j])) continue;              //If we have already checked this point continuw with the next one
              checked_points++;
               double euc_dist = euclidian_distance(query, p[cube[bucket][j]]);
               f = false;
               //Insert the point while keeping the vector sorted
               if (euc_dist < tupl.v2[N-1]){
                 for (int l=0; l<N; l++) {
                   if (euc_dist < tupl.v2[l]) {
                     int ll;
                     f = true;
                     for (ll=N-1; ll>l; ll--) {
                       tupl.v2[ll] = tupl.v2[ll-1];
                       tupl.v1[ll] = tupl.v1[ll-1];
                     }
                     tupl.v2[ll] = euc_dist;
                     tupl.v1[ll] = cube[bucket][j];
                   }
                   if (f) break;
                 }
               }
          }
          bucket = hamming_distance(dist,bit, bucket); //get a new bucket to search

        }
        checked_probes++; //increase probes
        bit++;
  }
  if(tupl.v2[0]==numeric_limits<float>::infinity())tupl=bf(id,query);     //in case nothing was found
  return tupl;
}



tuple_of_vectors bf(int id, vector<double> query)
{
  tuple_of_vectors tupl;
  tupl.v1.resize(N);
  tupl.v2.resize(N);
  bool f;

  for (int i=0; i<N; i++) tupl.v2[i] = numeric_limits<float>::infinity();    //Initiallize with infinity the distance table

  for (int i=0; i<p.size(); i++) {                                  //For each point vector
      double euc_dist = euclidian_distance(query, p[i]);          //Compute the euclidian distance
      f = false;
            //Check if belongs to top N and if so inserted in the vector while keeping it sorted
      if (euc_dist < tupl.v2[N-1]){
        for (int l=0; l<N; l++) {
          if (euc_dist < tupl.v2[l]) {
            int ll;
            f = true;
            for (ll=N-1; ll>l; ll--) {
              tupl.v2[ll] = tupl.v2[ll-1];
              tupl.v1[ll] = tupl.v1[ll-1];
            }
            tupl.v2[ll] = euc_dist;
            tupl.v1[ll] = i;
          }
          if (f) break;
        }
      }
  }
  return tupl;
}

vector<int> bf_range(int id, vector<double> query)
{
  vector<int>b;
  bool f;
  for (int i=0; i<p.size(); i++) {
      double euc_dist = euclidian_distance(query, p[i]);
      if (euc_dist < R){
        b.push_back(i);
      }
  }
  return b;
}

void range_search(int id, vector<double> query)
{
  vector<int> b;
  vector<double> dist;
  bool f;
  string bucket = hash_query(query);
  int checked_probes = 0,checked_points = 0, bit = 0, h_dist = 1;
  while (checked_probes < probes && checked_points < M) {
    //Same final conditions as in knn
    if (cube.count(bucket) == 0) { //Bucket is not found
      if (bit == nChoosek(bucket.size(),h_dist)) {      //When you find all the possible combiantions hamming distance dist of our bucket
          h_dist++;
          bucket = hamming_distance(h_dist, bit, bucket);
      }
      else {
        bucket = hamming_distance(h_dist, bit, bucket);
      }
    }
    else {
      for (int j=0; j<cube[bucket].size(); j++) {  //For each vector-point in this bucket
        if (exists(b,cube[bucket][j])) continue;  //If we have already checked this vector-point
        checked_points++;
        if (checked_points > M) break;
        double euc_dist = euclidian_distance(query, p[cube[bucket][j]]); //Compute the euclidian distance
        if (euc_dist < R) b.push_back(cube[bucket][j]); //If the distance is smaller than R
      }
      bucket = hamming_distance(h_dist,checked_probes, bucket);
    }
    checked_probes++;
  }
  output_file<<"R-near neighbors: \n";
  if (b.size() == 0) b = bf_range(id, query);
  for (int i = 0; i<b.size(); i++) {
    output_file <<"item_id_"<< b[i] << "\n";
  }
}
