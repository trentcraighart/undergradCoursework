CC = gcc
CFLAGS = -O2 -Wno-unused-result

all: melt

melt: melt.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -rf melt
