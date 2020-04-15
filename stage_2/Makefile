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

hellor: bool.o parser.o lexer.o hash.o ast.o symbol_table.o semantic_analyser.o
	gcc -o stage2exe symbol_table.o ast.o bool.o parser.o lexer.o hash.o semantic_analyser.o
 
hellos: bool.o parser.o lexer.o hash.o ast.o symbol_table.o
	gcc -o stage2exe symbol_table.o ast.o parser.o lexer.o hash.o bool.o

ast: bool.o parser.o lexer.o hash.o ast.o
	gcc -o stage2exe bool.o ast.o parser.o lexer.o hash.o

assembler: bool.o parser.o lexer.o hash.o ast.o code_gen.o symbol_table.o
	gcc -o stage2exe code_gen.o bool.o ast.o parser.o lexer.o hash.o symbol_table.o


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

symbol_table.o: symbol_table.c
	gcc -c symbol_table.c

semantic_analyser.o: semantic_analyser.c
	gcc -c semantic_analyser.c

code_gen.o: code_gen.c
	gcc -c code_gen.c


clean:
	rm ast.o symbol_table.o hash.o bool.o parser.o lexer.o
