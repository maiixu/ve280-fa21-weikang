all:whole_story

whole_story:storyTeller.o node.o
	g++ -o whole_story storyTeller.o node.o
	
storyTeller.o: storyTeller.cpp
	g++ -c storyTeller.cpp
	
node.o: node.cpp
	g++ -c node.cpp
	
clean:
	rm -f whole_story *.o