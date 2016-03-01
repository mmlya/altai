CC=gcc
LFLAGS = -lgsl -lgslcblas -lm
CFLAGS = -Wall -O3 #-g

all: mlya

mlya: utils.o parameters.o fate.o gad.o main.o utils.c gad.c parameters.c main.c
	$(CC) $(CFLAGS) utils.o parameters.o fate.o gad.o main.o -o mlya $(LFLAGS)

main.o: ssim.h main.c
	$(CC) $(CFLAGS) -c main.c

gad.c: gad.h
	$(CC) $(CFLAGS) -c gad.c

fate.c: fate.h
	$(CC) $(CFLAGS) -c fate.c

parameters.o: parameters.h
	$(CC) $(CFLAGS) -c parameters.c

utils.o: utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o *~

install:
	cp mlya /usr/local/bin

local:
	cp mlya ~/bin
