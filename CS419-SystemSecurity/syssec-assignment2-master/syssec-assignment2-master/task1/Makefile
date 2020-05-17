CXX		:= g++
CC		:= gcc
LDFLAGS	:= -lm -lpthread
CFLAGS	:= -O1 -g -no-pie -I../include -Wno-unused-result

TARGET	:= flush-reload

SRC		:= $(wildcard *.c) $(wildcard *.h)

$(TARGET): $(TARGET).c $(SRC:%.c) $(SRC:%.h)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET)

.PHONY: all clean
