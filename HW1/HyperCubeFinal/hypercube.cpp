using namespace std;
#include <sstream>
#include "hash.hpp"
#include "search.hpp"
#include "tools.hpp"
#include <chrono>
#include <ctime>


int main(int argc, char *argv[])
{
  float sum = 0;

  std::cout<<"Handling arguments\n";
  handle_arguments(argc, argv);
  std::cout<<"Initializing and storing everything ,this might take a while \n";
  save_vectors();
  create_h_functions();

  long unsigned int number_of_queries = number_of_lines('q');
  std::cout<<"Searching \n";
  for (int i=0; i<number_of_queries; i++) {
    vector <double> query;
    string vec;
    //This piece of code takes all numbers of the query-point and put eache of them in a cell of array words
    vec.assign(vector_data('q',i));
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
    int dimension = ctr;
    query.resize(dimension);
    for (j=0; j<dimension; j++) {
      query[j] = atof(words[j]);
    }
    output_file << "Query: "<<query_ids[i]<<"\n";
    auto start1 = std::chrono::system_clock::now();
    tuple_of_vectors a = knn(i+1,query);                    //Searching with Hypercube
    auto end1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = end1-start1;

    auto start2 = std::chrono::system_clock::now();
    tuple_of_vectors b = bf(i+1,query);                   //Searching with Brute Force
    auto end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2-start2;


    for (int i=0; i<a.v2.size(); i++){                 //Printing results into the output file
      if(a.v2[i] == numeric_limits<float>::infinity()) break;
      output_file << "Nearest neighbor-" <<i<<": "<<ids[a.v1[i]]<<"\n";
      output_file << "distanceHypercube:"<<a.v2[i]<<"\n";
      output_file << "distanceTrue:"<<b.v2[i]<<"\n";
      //sum += a.v2[i]/b.v2[i];
    }
    output_file << "tHC: " << elapsed_seconds1.count() << "s\n";
    output_file << "tTrue: " << elapsed_seconds2.count() << "s\n";

    range_search(i+1,query);
  }
  std::cout<<"Done! \n";
}
