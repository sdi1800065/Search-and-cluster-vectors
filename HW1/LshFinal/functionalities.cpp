#include "functionalities.hpp"
#include "FileHandling.hpp"
#include <string.h>
#include <random>
#include <map>
#include <chrono>
#include <iomanip>


int k, L, N, R;

inline bool file_exists (const std::string& name) {   //Check if a file exists
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void handle_arguments(int argc, char *argv[])             //Handle argc and argv
{
  k=4;
  L=5;                      //Deafault arguments
  N=1;
  R=10000;
  if(argc<7 || argc >15)
  {
    std::cout<<"ERROR missing arguments or too many arguments \n";
    exit(-1);
  }
  std::string temp;
  for (int i = 0; i < argc; i++) {
    temp=argv[i];
    std::string temp=argv[i];
    if(temp.compare("–k")==0 || temp.compare("-k")==0)
    {
      if(argv[i+1]==nullptr)
      {
        std::cout<<"ERROR expected the number k after -k\n";
        exit(-1);
      }
      std::string temp2=argv[i+1];
      int j;
      for (j=0;j<temp2.length();j++)
      {
        if( temp2[j]<'0' || temp2[j]>'9')
        {
          std::cout<<"ERROR invalid intiger after -k, characters were detected\n";
          exit(-1);
        }
      }
      k=std::stoi(argv[i+1]);
    }
    else if(temp.compare("-L")==0 || temp.compare("-L")==0)
    {
      if(argv[i+1]==nullptr)
      {
        std::cout<<"ERROR expected the number after L -L\n";
        exit(-1);
      }
      std::string temp2=argv[i+1];
      int j;
      for (j=0;j<temp2.length();j++)
      {
        if( temp2[j]<'0' || temp2[j]>'9')
        {
          std::cout<<"ERROR invalid intiger after -L, characters were detected\n";
          exit(-1);
        }
      }
      L=std::stoi(argv[i+1]);
    }
    else if(temp.compare("–i")==0 || temp.compare("-i")==0)
    {
      if(argv[i+1]==nullptr)
      {
        std::cout<<"ERROR Expected name of query_file after -i,file not given or the given file doesnt exist\n";
        exit(-1);
      }
      if(!file_exists(argv[i+1]))
      {
        std::cout<<"ERROR Expected name of input_id after -i ,file not given or the given file doesnt exist\n";
        exit(-1);
      }
      input_file.open(argv[i+1]);
    }
    else if(temp.compare("–q")==0 || temp.compare("-q")==0)
    {
      if(argv[i+1]==nullptr)
      {
        std::cout<<"ERROR Expected name of query_file after -q,file not given or the given file doesnt exist\n";
        exit(-1);
      }
      if(!file_exists(argv[i+1]))
      {
        std::cout<<"ERROR Expected name of query_file after -q,file not given or the given file doesnt exist\n";
        exit(-1);
      }
      query_file.open(argv[i+1]);
    }
    else if(temp.compare("-ο")==0 || temp.compare("-o")==0)
    {
      if(argv[i+1]==nullptr)
      {
        std::cout<<"ERROR Expected name of output_file after -o,file not given or the given file doesnt exist\n";
        exit(-1);
      }
      /*if(!file_exists(argv[i+1]))
      {
        std::cout<<"ERROR Expected name of output_file after -o,file not given or the given file doesnt exist\n";
        exit(-1);
      }*/
      output_file.open(argv[i+1]);
    }
    else if(temp.compare("-R")==0 || temp.compare("-R")==0)
    {
      if(argv[i+1]==nullptr)
      {
        std::cout<<"ERROR expected the number R after -R\n";
        exit(-1);
      }
      std::string temp2=argv[i+1];
      int j;
      for (j=0;j<temp2.length();j++)
      {
        if( temp2[j]<'0' || temp2[j]>'9')
        {
          std::cout<<"ERROR invalid intiger after -R, characters were detected\n";
          exit(-1);
        }
      }
      R=std::stoi(argv[i+1]);
    }
    else if(temp.compare("-Ν")==0 || temp.compare("-N")==0)
    {
      if(argv[i+1]==nullptr)
      {
        std::cout<<"ERROR expected the number N after -N\n";
        exit(-1);
      }
      std::string temp2=argv[i+1];
      int j;
      for (j=0;j<temp2.length();j++)
      {
        if( temp2[j]<'0' || temp2[j]>'9')
        {
          std::cout<<"ERROR invalid intiger after -N, characters were detected\n";
          exit(-1);
        }
      }
      N=std::stoi(argv[i+1]);
    }
  }
  if(output_file.is_open() == 0 || input_file.is_open() == 0 || output_file.is_open()==0)
  {
    std::cout<<"ERROR input or output files are missing\n";
    exit(-1);
  }
}

double normal_distribution_generator()                                                    //Return a number from normal distribution
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
}

double inner_product(vector <double> v1, vector <double> v2, int dimension)                                 //Return the inner product of each vector
{
    double innerProduct = 0;
    for (int i = 0; i < dimension; i++) {
        innerProduct = innerProduct + v1[i]*v2[i];
    }
    return innerProduct;
}

long long unsigned int modulo(long long unsigned int a, long long unsigned int b)               //modulo (NOT) remainder, supports negative numbers
{
  return (a%b + b)%b;
}
bool exists(vector<int> v, int a )                          //Check if a exists in v
{
  for (int i=0; i<v.size(); i++) {
    if (v[i]==a) return true;
  }
  return false;
}

double euclidian_distance(vector<double> p1, vector<double> p2)       //Compute euclidian distance
{
  int dimension = p1.size();
  double dist = 0;
  for (int i=0; i<dimension; i++) {
      dist += (p1[i]-p2[i])*(p1[i]-p2[i]);
  }
  dist = sqrt(dist);
  return dist;
}
