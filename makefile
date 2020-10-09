all: SearchNewBooks

SearchNewBooks: SearchNewBooks.o
	g++ -Wall -Werror SearchNewBooks.o -o SearchNewBooks

SearchNewBooks.o: SearchNewBooks.cc
	g++ -Wall -Werror -c SearchNewBooks.cc
