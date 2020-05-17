all: task1 task2 task3 rowhammer

task1: task1.c util.h
	$(CC) -o $@ $< -O2

task2: task2.c util.h
	$(CC) -o $@ $< -O2

task3: task3.c util.h
	$(CC) -o $@ $< -O2

rowhammer: rowhammer.c
	$(CC) -o $@ $< -O2 -pthread -lpthread

clean:
	rm -rf task1 task2 task3 rowhammer
