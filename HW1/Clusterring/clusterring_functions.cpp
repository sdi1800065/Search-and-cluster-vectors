#include <ctime>
#include <limits>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "clusterring_functions.hpp"
#include "functionalities.hpp"
#include "hypercube_func.hpp"
#include "lsh.hpp"

vector <vector <double>> centers;
vector <vector <int>> clusters;

int times = 0;

void kmeans_plusplus()                                    //Centroid initiallization with kmeans++
{
  srand(time(NULL));
  int center = rand()%p.size();                                   //Take the first center randomly
  int t = 1;
  centers.resize(K);
  for (int i=0; i<K; i++) centers[i].resize(p[center].size());
  for (int i=0; i<p[center].size(); i++) {
      centers[t-1][i] = p[center][i];             //Save the center
  }
  vector < vector <double>> all_vectors;
  //all_vectors is a copy of p
  all_vectors.resize(p.size());
  all_vectors = p;
  all_vectors.erase(all_vectors.begin() + center);
  float max;
  while (t!=K) {                                      //While we do not have found all needed centers
      vector <float> dist;
      dist.resize(all_vectors.size());
      int sum = 0;
        max = -1;
      for (int i=0; i<all_vectors.size(); i++) {                                //For each remaining vector-point
          float min_dist = numeric_limits<float>::infinity();
          int min_center;
          for (int j=0; j<centers.size() && j<t; j++)  {                               //For each centroid
              float euc_dist = euclidian_distance(centers[j], all_vectors[i]);
              //If it's smaller keep it
              if (euc_dist < min_dist) {
                min_dist = euc_dist;
                min_center = j;
              }
          }
          dist[i] = min_dist;
          if (dist[i] > max) max = dist[i];                                             //Find max in order to normalize
      }
      vector <double> P;
      P.resize(p.size()-t);                                                               //P vector
      for (int i =0; i<all_vectors.size(); i++) {
        dist[i] = dist[i]/ max;                                                           //Normalize
        P[i] = 0;
        for (int ii=0; ii<i; ii++) P[i] += dist[ii]*dist[ii];                             //Conpute P[i]
      }
      float x = ((long double)rand()/RAND_MAX)*(P[p.size()-t - 1]-0) + 0;                 //Pick x
      int new_centroid;
      for (int r=1; r<p.size()-t; r++) {                                                  //Find the r
        if (P[r-1] < x && P[r] >= x) {
            new_centroid = r;
            break;
        }
      }
      t++;      //We found another centroid
      for (int i=0; i<all_vectors[new_centroid].size(); i++) {
          centers[t-1][i] = all_vectors[new_centroid][i];
      }
      all_vectors.erase(all_vectors.begin() + new_centroid);
  }
}

void Lloyds_assignment()
{
  clusters.resize(0);
  clusters.resize(K);

  for (int i=0; i<p.size(); i++) {                                  //For each vector-point
      float min_dist = numeric_limits<float>::infinity();
      int min_center;
      for (int j=0; j<centers.size(); j++) {                        //For each centroid
          float euc_dist = euclidian_distance(p[i], centers[j]);
          if (euc_dist < min_dist && euc_dist!=0) {         //Find centroid with minimum distance
            min_dist = euc_dist;
            min_center = j;
          }
      }
      clusters[min_center].push_back(i);      //Assign the vector point to this centroid
  }

}

void reverse_assignment()
{
  clusters.resize(0);
  clusters.resize(K);
  bool flag = true;
  bool f=false;
  double r = min_distance_among_centers();
  vector<vector<double>> all_vectors = p;
  while (flag) {
    int sum = 0;
    vector <vector <int>> temp_clusters;
    temp_clusters.resize(K);
    vector <int> b;
    for (int i=0; i<centers.size(); i++) {                                      //For each centroid
      if (method == "LSH") b = range_search(0,centers[i],r);                     //For LSH method call renge searc for LSH
      else b = range_searchHC(0,centers[i],r);                                   //For Hypercube method call renge searc for Hypercube
      sum += b.size();
       for (int j=0; j<b.size(); j++) {


         if (times == 0) {                                //This is because the first time this function is executed the centers are points of the dataset and so I want them not to get selected to join clusters
                                                                      //The other times the centers are artificial
            //Erase the centroids of our vector
            for (int ll=0; ll<centers.size(); ll++) {
              all_vectors.erase(all_vectors.begin()+b[ll]-1);
              if (centers[ll] == p[b[j]]) {
                f = true;
                break;
              }
            }
            if (f) continue;
         }


         marked[b[j]-1] = true;                                         //The vector-point is assigned so map it to true
         temp_clusters[i].push_back(b[j]);
         //If a vector-point has been selected from more than 1 centroids calculate the distances per 2 and assign the vector point to the best centroid
           for (int ll=0; ll<i; ll++) {
             if (exists(temp_clusters[ll],b[j])) {
               float dist1 = euclidian_distance(centers[i],p[b[j]]);
               float dist2 = euclidian_distance(centers[ll],p[b[j]]);
               if (dist1 <= dist2) {
                   int index = get_index(b[j], temp_clusters[ll]);
                   temp_clusters[ll].erase(temp_clusters[ll].begin() + index);                                  //Erase from the previous cluster
               }
                else {
                  int index = get_index(b[j], temp_clusters[i]);
                  temp_clusters[i].erase(temp_clusters[i].begin() + index);                                   //Erase from the previous cluster
                }
             }
          }
          all_vectors.erase(all_vectors.begin()+b[j]-1);
      }
      clusters[i]=temp_clusters[i];
    }
    r *= 2;
    if (sum < 20) flag = false;                               //If the new assigned vector-points are less  than 20 stop the loop
  }
  for (int i=0; i<p.size(); i++) {                              //For remaining unassiged vector-points assign them with the dummy way
    if (marked[i] == true) continue;
    float min_dist = numeric_limits<float>::infinity();
    int min_center;
    for (int j=0; j<centers.size(); j++) {
        float euc_dist = euclidian_distance(p[i], centers[j]);
        if (euc_dist < min_dist && euc_dist!=0) {
          min_dist = euc_dist;
          min_center = j;
        }
    }
    clusters[min_center].push_back(i);
  }
  for (int i=0; i<p.size(); i++) marked[i] = false;                     //Now they are all mapped to false for next run
  times++;
}

double min_distance_among_centers()                               //Find the minimum distance among all centers
{
  double min_dist = numeric_limits<float>::infinity();
  for (int i=0; i<centers.size(); i++) {
    for (int j=i; j<centers.size(); j++) {
        double euc_dist = euclidian_distance(centers[i],centers[j]);
        if (euc_dist < min_dist) min_dist = euc_dist;
    }
  }
  return min_dist;
}


bool update_centroids()                                     //Update centroids and check if they have been chenged
{
  vector <vector <double>> new_centroids;
  new_centroids.resize(K);
  new_centroids;
  int dimension = p[0].size();
  for (int i=0; i<clusters.size(); i++) {
    vector <double> mean_vector(dimension,0);                     //Initiallize to 0
    //Find the new centroids by computing the mean vectors of all vectors
    for (int j=0; j<clusters[i].size(); j++) {
        for (int index = 0; index<dimension; index++) {
          mean_vector[index] += p[clusters[i][j]][index];
        }
    }
    for (int index=0; index<dimension; index++) {
        mean_vector[index] /= float (clusters[i].size());
    }
    new_centroids[i] = mean_vector;
  }
  //Check if they have been changed
  bool are_same = true;
  for (int i=0; i<K; i++) {
    vector <vector <double>> temp = centers;
     centers[i] = new_centroids[i];
    if (temp[i]!=new_centroids[i]) are_same = false;
  }
  return are_same;

}
