CC=g++
FLAGS = -Wall -ggdb
FIRST_FILES = first.cpp
FIRST_OBJECT = first.o

SECOND_FILES = second.cpp
SECOND_OBJECT = second.o

all: first second
first : $(FIRST_OBJECT)
	$(CC) $(FLAGS) $(FIRST_OBJECT) -o first.out
first.o : first.cpp
	$(CC) $(FLAGS) $(FIRST_FILES) -c 

second : $(SECOND_OBJECT)
	$(CC) $(FLAGS) $(SECOND_OBJECT) -o second.out
second.o : second.cpp
	$(CC) $(FLAGS) $(SECOND_FILES) -c 

clean:
	rm first.o first.out second.o second.out
