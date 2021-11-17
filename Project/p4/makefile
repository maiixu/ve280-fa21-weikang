all: p4

p4: card.o rand.o deck.o hand.o player.o blackjack.o
	g++ -o p4 card.o rand.o deck.o hand.o player.o blackjack.o

card.o: card.cpp
	g++ -c card.cpp

rand.o: rand.cpp
	g++ -c rand.cpp

deck.o: deck.cpp
	g++ -c deck.cpp

hand.o: hand.cpp
	g++ -c hand.cpp

player.o: player.cpp
	g++ -c player.cpp

blackjack.o: blackjack.cpp
	g++ -c blackjack.cpp

clean:
	rm -f p4 *.o
