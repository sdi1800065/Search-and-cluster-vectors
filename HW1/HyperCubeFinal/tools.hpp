#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

extern int k, M, N, R,probes;

extern ifstream input_file;

extern ifstream query_file;

extern ofstream output_file;

//map is used for ids to be able to accept both int and string id form
extern map <int, string> ids;
extern map <int, string> query_ids;

int number_of_lines(char c);  //getting the number of lines from a file
string vector_data(char c, int i); //Get each query

void handle_arguments(int argc, char *argv[]); //handle arguments
unsigned nChoosek( unsigned n, unsigned k ); //n ana k
double normal_distribution_generator();        //Return a number from normal distribution
double inner_product(vector <double> v1, vector <double> v2, int dimension); //Return the inner product of each vector
long long unsigned int modulo(long long unsigned int a, long long unsigned int b); //modulo (NOT) remainder, supports negative numbers
double euclidian_distance(vector<double> p1, vector<double> p2);        //Compute euclidian distance
string hamming_distance(int dist, int i, string bit_string);//compute hamming_distance
bool exists(vector<int> v, int a );  //Check if a exists in v
