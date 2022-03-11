all: lsh
lsh:lsh.o hash.o FileHandling.o functionalities.o search.o
	g++ --std=c++11 -O2 lsh.o hash.o functionalities.o FileHandling.o search.o -o lsh
lsh.o :lsh.cpp hash.hpp FileHandling.hpp search.hpp functionalities.hpp 
	g++ --std=c++11 -O2 -c lsh.cpp
hash.o :hash.cpp hash.hpp FileHandling.hpp search.hpp functionalities.hpp
	g++ --std=c++11 -O2 -c hash.cpp
FileHandling.o :FileHandling.cpp hash.hpp FileHandling.hpp  search.hpp functionalities.hpp
	g++ --std=c++11 -O2 -c FileHandling.cpp
search.o :search.cpp hash.hpp FileHandling.hpp search.hpp functionalities.hpp
	g++ --std=c++11 -O2 -c search.cpp
functionalities.o :functionalities.cpp hash.hpp FileHandling.hpp search.hpp functionalities.hpp
	g++ --std=c++11 -O2 -c functionalities.cpp
clean:
	rm lsh lsh.o hash.o FileHandling.o functionalities.o search.o
