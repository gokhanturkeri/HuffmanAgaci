hepsi: derle calistir
Nesneler :=   ./lib/Sikistirici.o	./lib/Ayiklayici.o

derle:
	g++ -I ./include/ -o ./lib/Sikistirici.o -c ./src/Sikistirici.cpp
	g++ -I ./include/ -o ./lib/Ayiklayici.o -c ./src/Ayiklayici.cpp
	g++ -I ./include/ -o ./bin/test $(Nesneler) ./src/test.cpp
	
calistir:
	./bin/test