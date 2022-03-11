#pragma once
#include <vector>
#include <unordered_map>
#include "tools.hpp"
 
//unordered is better for lookup ,we dont need to sort
extern unordered_map <int,char> bits;               //Holds 0/1 values of the buckets
extern unordered_map <string, vector <int>> cube;   //Hypercubes master structure
extern vector <vector <int> > h;                    //Holds h numbers
extern vector<vector<double>> p;
extern int n;       
extern vector<vector<double>> v;                    //Holds points
extern int w;

extern int TableSize;


void f(int x);                                  //Randomly choose 1 or 0 to map h(p) , if already choosen for this x then do nothing.
string hash_query(vector<double> query);        //Returns the bucket that the closest neighboughrs of a query should be
void save_vectors();                            //Stores the points.
void create_h_functions();                      //Creates h functions and also maps buckets to {0,1} uniformly.