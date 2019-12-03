CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

all: playdom player unittest-bug1 unittest-bug2 unittest-bug3 unittest-bug4 unittest-bug5 unittest-bug7 unittest-bug8 unittest-bug9 unittest-bug10 unittestresults

unittest-bug1: dominion.o unittest-bug1.c
	gcc -o unittest-bug1 unittest-bug1.c -g dominion.o rngs.o $(CFLAGS)

unittest-bug2: dominion.o unittest-bug2.c
	gcc -o unittest-bug2 unittest-bug2.c -g dominion.o rngs.o $(CFLAGS)

unittest-bug3: dominion.o unittest-bug3.c
	gcc -o unittest-bug3 unittest-bug3.c -g dominion.o rngs.o $(CFLAGS)

unittest-bug4: dominion.o unittest-bug4.c
	gcc -o unittest-bug4 unittest-bug4.c -g dominion.o rngs.o $(CFLAGS)

unittest-bug5: dominion.o unittest-bug5.c
	gcc -o unittest-bug5 unittest-bug5.c -g dominion.o rngs.o $(CFLAGS)

unittest-bug7: dominion.o unittest-bug7.c
	gcc -o unittest-bug7 unittest-bug7.c -g dominion.o rngs.o $(CFLAGS)

unittest-bug8: dominion.o unittest-bug8.c
	gcc -o unittest-bug8 unittest-bug8.c -g dominion.o rngs.o $(CFLAGS)

unittest-bug9: dominion.o unittest-bug9.c
	gcc -o unittest-bug9 unittest-bug9.c -g dominion.o rngs.o $(CFLAGS)

unittest-bug10: dominion.o unittest-bug10.c
	gcc -o unittest-bug10 unittest-bug10.c -g dominion.o rngs.o $(CFLAGS)

unittestresults: unittest-bug1 unittest-bug2 unittest-bug3 unittest-bug4 unittest-bug5 unittest-bug7 unittest-bug8 unittest-bug9 unittest-bug10
	./unittest-bug1 >> unittestresult.out
	./unittest-bug2 >> unittestresult.out
	./unittest-bug3 >> unittestresult.out
	./unittest-bug4 >> unittestresult.out
	./unittest-bug5 >> unittestresult.out
	./unittest-bug7 >> unittestresult.out
	./unittest-bug8 >> unittestresult.out
	./unittest-bug9 >> unittestresult.out
	./unittest-bug10 >> unittestresult.out
	gcov -b -f dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f unittest-bug1 unittest-bug2 unittest-bug3 unittest-bug4 unittest-bug5 unittest-bug7 unittest-bug8 unittest-bug9 unittest-bug10