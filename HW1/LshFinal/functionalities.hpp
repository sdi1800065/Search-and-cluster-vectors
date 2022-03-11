#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

extern int k, L, N, R;            //Arguments of the program (number of h functions, number of hash tables, number of nearest neighbors, radial for range search)

extern map <int, string> ids;     //Each index maps to the name of the query (input file)
extern map <int, string> query_ids;     //Each index maps to the name of the query (query_file)

bool exists(vector<int> v, int a );                                       //Check if an integer exists in a vector
double euclidian_distance(vector<double> p1, vector<double> p2);          //Compute the euclidian distance between 2 vectors
void handle_arguments(int argc, char *argv[]);                            //Hanlde the argc and argv
double normal_distribution_generator();                                   //Generate a number taken fron normal distribution
double inner_product(vector <double> v1, vector <double> v2, int dimension);      //Compute the inner product of 2 vectors
long long unsigned int modulo(long long unsigned int a, long long unsigned int b);    //Modulo (NOT remainder)
