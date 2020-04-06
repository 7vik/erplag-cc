# all: hellor

# hellor: bool.o parser.o lexer.o hash.o
# 	gcc -o stage1exe bool.o parser.o lexer.o hash.o

# bool.o : bool.c
# 	gcc -c bool.c

# parser.o : parser.c
# 	gcc -c parser.c

# lexer.o : lexer.c
# 	gcc -c lexer.c

# hash.o : hash.c
# 	gcc -c hash.c


all: hellor

hellor: bool.o parser.o lexer.o hash.o ast.o symbol_table_id.o
	gcc -o stage2exe symbol_table_id.o ast.o bool.o parser.o lexer.o hash.o

ast: bool.o parser.o lexer.o hash.o ast.o
	gcc -o stage2exe bool.o ast.o parser.o lexer.o hash.o

bool.o : bool.c
	gcc -c bool.c

parser.o : parser.c
	gcc -c parser.c

lexer.o : lexer.c
	gcc -c lexer.c

hash.o : hash.c
	gcc -c hash.c

ast.o : ast.c
	gcc -c ast.c

symbol_table_id.o: symbol_table_id.c
	gcc -c symbol_table_id.c