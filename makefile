CC = gcc

CFLAGS = -Wall

TARGET = rmdup

all: rmdup lsdir

rmdup: rmdup.h rmdup.c
	$(CC) $(CFLAGS) -o rmdup rmdup.c && mv rmdup bin

lsdir: lsdir.h lsdir.c
	$(CC) $(CFLAGS) -o lsdir lsdir.c && mv lsdir bin

clean:
	$(RM) bin/*
