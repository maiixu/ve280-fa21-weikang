all: test

test: test_14.o
	g++ -o test test_14.o
test_14.o: test_14.cpp
	g++ -c test_14.cpp
clean:
	rm -f test *.o