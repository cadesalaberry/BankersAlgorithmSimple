CC=gcc
CC_FLAGS=-g -O2 -c -Wall
OBJECTS=banker.o

all:$(OBJECTS)
	$(CC) banker.o -o banker

$(OBJECTS):%.o:%.c
	$(CC) $(CC_FLAGS) $< -o $@

clean:
	rm *.o
	rm -rf banker
