CC = g++
FLAGS = -std=c++11
COMPILE_FLAGS = $(FLAGS) -c
all: StoreCalculator.out assets.out province.out city.out store.out

StoreCalculator.out: StoreCalculator.o tools.o
	$(CC) StoreCalculator.o tools.o $(FLAGS) -o StoreCalculator.out

assets.out: assets.o tools.o
	$(CC) assets.o tools.o $(FLAGS) -o assets.out

province.out: province.o tools.o
	$(CC) province.o tools.o $(FLAGS) -o province.out

city.out: city.o tools.o
	$(CC) city.o tools.o $(FLAGS) -o city.out

store.out: store.o tools.o
	$(CC) store.o tools.o $(FLAGS) -o store.out

StoreCalculator.o: StoreCalculator.cpp tools.h
	$(CC) $(COMPILE_FLAGS) StoreCalculator.cpp

assets.o: assets.cpp tools.h
	$(CC) $(COMPILE_FLAGS) assets.cpp

province.o: province.cpp tools.h
	$(CC) $(COMPILE_FLAGS) province.cpp

city.o: city.cpp tools.h
	$(CC) $(COMPILE_FLAGS) city.cpp

tools.o: tools.cpp tools.h
	$(CC) $(COMPILE_FLAGS) tools.cpp

.PHONY: clean

clean:
				rm *.o
				rm *.out