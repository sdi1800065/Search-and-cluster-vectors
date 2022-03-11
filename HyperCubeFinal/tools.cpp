#include "tools.hpp"
#include <string.h>
#include <random>
#include <map>
#include <chrono>
#include <algorithm>
#include <iomanip>


int k, M, N, R,probes;

ifstream input_file;

ifstream query_file;

ofstream output_file;

map <int, string> ids;
map <int, string> query_ids;


inline bool file_exists (const std::string& name) { //Check if a file exists
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void handle_arguments(int argc, char *argv[]) //Handle argc and argv
{
  //Deafault arguments
  k=14;
  M=10;
  probes=2;
  N=1;
  R=10000;
  if(argc<7 || argc >17)
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
    else if(temp.compare("-M")==0 || temp.compare("-M")==0)
    {
      if(argv[i+1]==nullptr)
      {
        std::cout<<"ERROR expected the number after M -M\n";
        exit(-1);
      }
      std::string temp2=argv[i+1];
      int j;
      for (j=0;j<temp2.length();j++)
      {
        if( temp2[j]<'0' || temp2[j]>'9')
        {
          std::cout<<"ERROR invalid intiger after -M, characters were detected\n";
          exit(-1);
        }
      }
      M=std::stoi(argv[i+1]);
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
    else if(temp.compare("–probes")==0 || temp.compare("-probes")==0)
    {
      if(argv[i+1]==nullptr)
      {
        std::cout<<"ERROR expected the number probes after -probes\n";
        exit(-1);
      }
      std::string temp2=argv[i+1];
      int j;
      for (j=0;j<temp2.length();j++)
      {
        if( temp2[j]<'0' || temp2[j]>'9')
        {
          std::cout<<"ERROR invalid intiger after -probes, characters were detected\n";
          exit(-1);
        }
      }
      probes=std::stoi(argv[i+1]);
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
  int tmp = number_of_lines('i');
  if(tmp<N){N=tmp;}
 // std::cout<<"K:"<<k<<" M:"<<M<<" N:"<<N<<" probes:"<<probes<<" R:"<<R<<"\n";
}
double normal_distribution_generator()             //Return a number from normal distribution
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
}


double inner_product(vector <double> v1, vector <double> v2, int dimension)                                  //Return the inner product of each vector
{
    double innerProduct = 0;
    for (int i = 0; i < dimension; i++) {
        innerProduct = innerProduct + v1[i]*v2[i];
    }
    return innerProduct;
}

long long unsigned int modulo(long long unsigned int a, long long unsigned int b)     //modulo (NOT) remainder, supports negative numbers
{
  return (a%b + b)%b;
}

string hamming_distance(int dist, int i, string bit_string) //compute hamming_distance
{
  string binary = bit_string;
  if (dist == 1) {                                      //If dist == 1 just change one bit
    if (binary[i] == '1') binary[i] = '0';
    else binary[i] = '1';
  }
  else {                                                  //Else
    vector <int> bit_index;
    for(int i=0; i<bit_string.size(); i++) bit_index.push_back(i);                //Push_back all indexes
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(bit_index.begin(), bit_index.end(), std::default_random_engine(seed)); //shuffle them
    for (int j = 0; j < dist; j++) {                                              //Change randomly dist bits
      if (binary[bit_index[j]] == '1') binary[bit_index[j]] = '0';
      else binary[bit_index[j]] = '1';
    }
  }
  return binary;
}

unsigned nChoosek( unsigned n, unsigned k )                   //n ana k
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

bool exists(vector<int> v, int a ) //Check if a exists in v
{
  for (int i=0; i<v.size(); i++) {
    if (v[i]==a) return true;
  }
  return false;
}

double euclidian_distance(vector<double> p1, vector<double> p2)        //Compute euclidian distance
{
  int dimension = p1.size();
  double dist = 0;
  for (int i=0; i<dimension; i++) {
      dist += (p1[i]-p2[i])*(p1[i]-p2[i]);
  }
  dist = sqrt(dist);
  return dist;
}

int number_of_lines(char c)
{
  int lines=0;
	string vec;
  if (c == 'i') {                                 //If the file is the input file
    while( getline(input_file,vec) ) ++lines;     //Count lines
  	input_file.clear();
  	input_file.seekg(0,ios::beg);
  }
  else {                                    //If is the query file
    while( getline(query_file,vec) ) ++lines;   //Count lines
  	query_file.clear();
  	query_file.seekg(0,ios::beg);
  }

	return lines;
}

string vector_data(char c,int ii)
{
    int dim = 0;
    string vec;
    if (c == 'i') getline(input_file,vec);          //If its the input file
    else {
      getline(query_file,vec);                      //Take the line
    }
    int i = 0;
    string id;
    while (vec[i]!=' '){                          //Remove each character from the id (The id is the first string, loop until you find the first space)
      id.push_back(vec[i]);        //Take the id
      vec.erase(vec.begin());
    }
    if (c == 'i') ids.insert({ii,id});          //Map the index with id
    else query_ids.insert({ii,id});
    vec.erase(vec.begin());

    return vec;
}
