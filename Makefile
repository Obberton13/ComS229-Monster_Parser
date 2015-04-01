MonsterParser: Dice.o NPC.o
	g++ -Wall Dice.o NPC.o -o MonsterParser -lboost_regex -lncurses

Dice.o: Dice.cpp Dice.h
	g++ -Wall -Werror -ggdb Dice.cpp -c

NPC.o: NPC.cpp NPC.h
	g++ -Wall -Werror -ggdb NPC.cpp -c

clean:
	rm *.o MonsterParser
