all: p3

p3: simulation.o p3.o
	g++ -o p3 simulation.o p3.o

simulation.o: simulation.cpp
	g++ -c simulation.cpp

p3.o: p3.cpp
	g++ -c p3.cpp

clean:
	rm -f p3 *.o
