CXX		:= g++
CC		:= gcc
LDFLAGS	:=
CFLAGS	:= -O2 -g

TARGET	:= ptrace

SRC		:= $(wildcard *.c) $(wildcard *.h)

$(TARGET): $(TARGET).c $(SRC:%.c) $(SRC:%.h)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET)

.PHONY: all clean
