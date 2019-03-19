CC = g++
FLAGS = -std=c++11 -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
SOURCES = TNumVec.o TParser.o MyRadixSort.o main.o
EXECUTABLE = LAB1

all: build #clear

build: TParser.o TNumVec.o MyRadixSort.o main.o
	$(CC) $(FLAGS)  $(SOURCES) -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp
	
MyRadixSort.o:
	$(CC) $(FLAGS) -c MyRadixSort.cpp

TNumVec.o: TNumVec.cpp 
	$(CC) $(FLAGS) -c TNumVec.cpp

TParser.o: TParser.cpp
	$(CC) $(FLAGS) -c TParser.cpp
	
# clear:
# 	rm -f $(SOURCES)

clean:
	rm -f $(SOURCES) $(EXECUTABLE)