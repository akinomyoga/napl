napl: main.o naplvm.o gencode.o parser.o lexer.o tree.o
	g++ -g -o bin/napl bin/main.o bin/naplvm.o bin/gencode.o bin/parser.o bin/lexer.o bin/tree.o

main.o: src/main.cpp
	g++ -g -c -std=c++14 -o bin/main.o src/main.cpp

naplvm.o: src/napl_vm.cpp
	g++ -g -c -std=c++14 -o bin/naplvm.o src/napl_vm.cpp

gencode.o: src/napl_gencode.cpp
	g++ -g -c -std=c++14 -o bin/gencode.o src/napl_gencode.cpp

lexer.o: src/lex.yy.c
	g++ -g -c -std=c++14 -o bin/lexer.o src/lex.yy.c

parser.o: src/y.tab.c
	g++ -g -c -std=c++14 -o bin/parser.o src/y.tab.c

tree.o: src/napl_tree.cpp
	g++ -g -c -std=c++14 -o bin/tree.o src/napl_tree.cpp
