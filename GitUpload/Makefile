all: iscas

iscas: iscas.o bench_parser.o dijkstra.o 
	g++ -o iscas iscas.o bench_parser.o dijkstra.o -std=c++11

iscas.o: iscas.cpp bench_parser.h dijkstra.h
	g++ -c iscas.cpp -std=c++11

bench_parser.o: bench_parser.cpp bench_parser.h
	g++ -c bench_parser.cpp -std=c++11

dijkstra.o: dijkstra.cpp dijkstra.h
	g++ -c dijkstra.cpp -std=c++11

clean:
	rm -f iscas *.o

