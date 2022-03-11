#include <iostream>
#include <limits>
#include <cmath>
#include "search.hpp"
#include "functionalities.hpp"
#include "hash.hpp"

tuple_of_vectors knn(int id, vector<double> query)
{
  tuple_of_vectors tupl;
  tupl.v1.resize(N);
  tupl.v2.resize(N);
  bool f;
  long long unsigned int ID;
  int j;
  for (int i=0; i<N; i++) tupl.v2[i] = numeric_limits<float>::infinity();                 //Initiallize with infinity the distance table
  int items_found = 0;
  bool redo = false;
  for (int i=0; i<L; i++) {                                               //For each hash table
   int bucket = hash_query(query, &ID);                                   //Hash the query and take each id
      for (j=0; j<hash_tables[i][bucket].size(); j++) {                   //For each vector-point in this bucket
           if (exists(tupl.v1,hash_tables[i][bucket][j])) continue;       //If we have already checked this vector-point
           if (ID != IDS[i][hash_tables[i][bucket][j]] && !redo) {        //Perfrom the querying trick
             continue;
           }
           else {
             items_found++;
           }

          double euc_dist = euclidian_distance(query, p[hash_tables[i][bucket][j]]);        //Compute the euclidian distance
          f = false;
          //Check if blongs to top N and if so inserted in the vector while keeping it sorted
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
                tupl.v1[ll] = hash_tables[i][bucket][j];
              }
              if (f) break;
            }
          }

      }


      if (i == L - 1) {                         //If we have checked all hash tables
        if (items_found < N) {                  //If we did not find the number of neighbors that we wanted
          redo = true;                          //Redo the loop without the quering trick
          i = -1;
        }
      }
  }
  if(tupl.v2[0]==numeric_limits<float>::infinity())tupl=bf(id,query); //in case nothing was found
  return tupl;
}

void range_search(int id, vector<double> query)
{
  vector<int> b;
  vector<double> dist;
  bool f;
  long long unsigned int ID;
  for (int i = 0; i < L; i++) {                 //For each hash table
    int bucket = hash_query(query,&ID);                       //Hash the query and take the bucket
    for (int j=0; j<hash_tables[i][bucket].size(); j++) {     //For each vector-point in this bucket
        if (exists(b,hash_tables[i][bucket][j])) continue;    //If we have already checked this vector-point
        double euc_dist = euclidian_distance(query, p[hash_tables[i][bucket][j]]);  //Compute the euclidian distance
        if (euc_dist < R) b.push_back(hash_tables[i][bucket][j]);         //If the distance is smaller than R
    }
  }
  output_file<<"R-near neighbors: \n";
  for (int i = 0; i<b.size(); i++) {
    output_file <<"item_id_"<< ids[b[i]] << "\n";
  }
}

tuple_of_vectors bf(int id, vector<double> query)
{
  tuple_of_vectors tupl;
  tupl.v1.resize(N);
  tupl.v2.resize(N);
  bool f;

  for (int i=0; i<N; i++) tupl.v2[i] = numeric_limits<float>::infinity();               //Initiallize the N-size vector with infinity

  for (int i=0; i<p.size(); i++) {                                                  //For each point vector
      double euc_dist = euclidian_distance(query, p[i]);                            //Compute the euclidian distance
      f = false;
      //Check if blongs to top N and if so inserted in the vector while keeping it sorted
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
