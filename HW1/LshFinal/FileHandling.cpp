#include <iostream>
#include "FileHandling.hpp"
#include "functionalities.hpp"

ifstream input_file;

ifstream query_file;

ofstream output_file;

map <int, string> ids;
map <int, string> query_ids;

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
      /*if (c == 'i')*/  id.push_back(vec[i]);        //Take the id
      vec.erase(vec.begin());
    }
    if (c == 'i') ids.insert({ii,id});          //Map the index with id
    else query_ids.insert({ii,id});
    vec.erase(vec.begin());

    return vec;
}
