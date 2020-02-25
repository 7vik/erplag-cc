all: hello

hello: perform
	./output t1.txt abc.txt

perform: bool.o parser.o lexer.o hash.o
	gcc -o output bool.o parser.o lexer.o hash.o

bool.o : bool.c
	gcc -c bool.c

parser.o : parser.c
	gcc -c parser.c

lexer.o : lexer.c
	gcc -c lexer.c

hash.o : hash.c
	gcc -c hash.c