CXX		:= g++
CC		:= gcc
LDFLAGS	:= -lm -lpthread
CFLAGS	:= -O0 -g -no-pie -I../include

TARGET	:= example6

SRC		:= $(wildcard *.c) $(wildcard *.h)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET)

.PHONY: all clean
