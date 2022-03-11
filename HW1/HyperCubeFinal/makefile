all: cube
cube:hypercube.o hash.o tools.o search.o
	g++ --std=c++11 -O2 hypercube.o hash.o tools.o search.o -o cube
hypercube.o :hypercube.cpp hash.hpp tools.hpp search.hpp
	g++ --std=c++11 -O2 -c hypercube.cpp
hash.o :hash.cpp hash.hpp tools.hpp search.hpp
	g++ --std=c++11 -O2 -c hash.cpp
tools.o :tools.cpp hash.hpp tools.hpp  search.hpp
	g++ --std=c++11 -O2 -c tools.cpp
search.o :search.cpp hash.hpp tools.hpp search.hpp
	g++ --std=c++11 -O2 -c search.cpp
clean:
	rm cube hypercube.o hash.o tools.o search.o
