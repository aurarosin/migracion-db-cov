ARGS=-O2 -w

run: main.o
	./main.o 127.0.0.1 5432 postgres 26a26f

main.o: main.cpp file_read.o postgres_con.o
	g++ ${ARGS} -o main.o main.cpp file_read.o postgres_con.o -lpqxx -lpq

file_read.o: file_read.h file_read.cpp
	g++ ${ARGS} -c file_read.cpp -o file_read.o

postgres_con.o: postgres_con.h postgres_con.cpp
	g++ ${ARGS} -c postgres_con.cpp -o postgres_con.o -lpqxx -lpq

clean:
	rm *.o

.PHONY: run clean