main.o: main.cpp
	g++ -o main.o main.cpp -lpqxx -lpq

clean:
	rm *.o

.PHONY: clean