napl: main.o naplvm.o gencode.o
	g++ -o bin/napl bin/main.o bin/naplvm.o bin/gencode.o

main.o: src/main.cpp
	g++ -c -std=c++14 -o bin/main.o src/main.cpp

naplvm.o: src/napl_vm.cpp
	g++ -c -std=c++14 -o bin/naplvm.o src/napl_vm.cpp

gencode.o: src/napl_gencode.cpp
	g++ -c -std=c++14 -o bin/gencode.o src/napl_gencode.cpp