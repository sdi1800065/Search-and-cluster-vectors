all: cluster
cluster: cluster.o clusterring_functions.o functionalities.o hypercube_func.o lsh.o silhouette.o
	g++ --std=c++11 -O2 cluster.o clusterring_functions.o functionalities.o hypercube_func.o lsh.o silhouette.o -o cluster
cluster.o :cluster.cpp
	g++ --std=c++11 -O2 -c cluster.cpp
clusterring_functions.o :clusterring_functions.cpp
	g++ --std=c++11 -O2 -c clusterring_functions.cpp
functionalities.o :functionalities.cpp
	g++ --std=c++11 -O2 -c functionalities.cpp
hypercube_func.o :hypercube_func.cpp
	g++ --std=c++11 -O2 -c hypercube_func.cpp
lsh.o :lsh.cpp
	g++ --std=c++11 -O2 -c lsh.cpp
silhouette.o :silhouette.cpp
	g++ --std=c++11 -O2 -c silhouette.cpp
clean:
	rm cluster cluster.o clusterring_functions.o functionalities.o hypercube_func.o lsh.o silhouette.o
