using namespace std;
#include <sstream>
#include "functionalities.hpp"
#include "FileHandling.hpp"
#include "hash.hpp"
#include "search.hpp"
#include <chrono>



int main(int argc, char *argv[])
{
  handle_arguments(argc, argv);
  create_hash_tables();                                         //Create all needed hash tables
  float sum = 0;
  for (int i = 0; i < L; i++) create_hash_functions(i);             //Create  all needed hash functions
  long unsigned int number_of_queries = number_of_lines('q');       //Take the number of total queries
  for (int i=0; i<number_of_queries; i++) {                          //For each query
    vector <double> query;
    string vec;
    vec.assign(vector_data('q',i));                                 //Take the query
    char words[vec.size()][15];
    int j=0, ctr=0;
    //This piece of code takes all numbers of the query and put eache of them in a cell of array words
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
    int dimension = ctr;
    //Create the query vector-point as a vector
    query.resize(dimension);
    for (j=0; j<dimension; j++) {
      query[j] = atof(words[j]);
    }

    //Start the process of the output
    output_file << "Query: "<<query_ids[i]<<"\n";
    auto start1 = std::chrono::system_clock::now();
    tuple_of_vectors a = knn(i+1,query);            //K approximate nearest neighbors
    auto end1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = end1-start1;

    auto start2 = std::chrono::system_clock::now();
    tuple_of_vectors b = bf(i+1,query);             //Brute force method
    auto end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2-start2;

    //Create the output file
    for (int i=0; i<a.v2.size(); i++){
      if(a.v2[i] == numeric_limits<float>::infinity()) break;
      output_file << "Nearest neighbor-" <<i<<": "<<ids[a.v1[i]]<<"\n";
      output_file << "distanceLSH:"<<a.v2[i]<<"\n";
      output_file << "distanceTrue:"<<b.v2[i]<<"\n";
      // sum += a.v2[i]/b.v2[i];
    }
    output_file << "tLSH: " << elapsed_seconds1.count() << "s\n";
    output_file << "tTrue: " << elapsed_seconds2.count() << "s\n";

    range_search(i+1,query);

  }
  // cout << "AVG = " << sum/number_of_queries - 1 << endl;      //Average error
  output_file.close();
  input_file.close();
}
