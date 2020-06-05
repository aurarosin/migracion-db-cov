ARGS=-O2 -lpqxx -lpq

main.o: main.cpp file_read.o postgres_con.o
	g++ -o main.o main.cpp ${ARGS} file_read.o postgres_con.o

file_read.o: file_read.h file_read.cpp
	g++ -c file_read.cpp -o file_read.o

postgres_con.o: postgres_con.h postgres_con.cpp
	g++ -c postgres_con.cpp -o postgres_con.o

clean:
	rm *.o

.PHONY: clean