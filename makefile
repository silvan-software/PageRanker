CC      = g++
CFLAGS  = -std=gnu++0x 
LDFLAGS = 

all: PageRanker

PageRanker: main.o PageRanker.o RankedPage.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o : main.cpp
	$(CC) -c $(CFLAGS) $<

PageRanker.o: PageRanker.cpp PageRanker.h
	$(CC) -c $(CFLAGS) $<

RankedPage.o: RankedPage.cpp RankedPage.h
	$(CC) -c $(CFLAGS) $<

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm PageRanker
