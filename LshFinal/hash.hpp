#pragma once
#include <vector>
#include "FileHandling.hpp"


extern vector<vector<vector<long long unsigned int>>> hash_tables;          //All hash tables

extern vector<vector<double>> v;                                            //v vectors


extern vector<vector<int>> g;                                               //g functions

extern vector<int> r;                                                        //r vector


extern vector<vector<vector<double>>> h;                                     //h functions

extern vector<vector<double>> p;                                             //All points-vectors from input_file

extern int w;

extern vector <vector <long long unsigned int>> IDS;                        //The IDS for the querying trick

extern int TableSize;                                                       //The size of eaxh hash tale


void create_hash_tables();                                                  //Create all hash_tables and initiallize all required vectors
void create_hash_functions(int table);                                      //Create h's ang g's functions
long long int hash_query(vector<double> query,long long unsigned int *ID);  //Hash the query and take the bucket
