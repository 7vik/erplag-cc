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

CC=gcc-5.4
all: compile_all

hellor: bool.o parser.o lexer.o hash.o ast.o symbol_table.o semantic_analyser.o
	gcc -o stage2exe symbol_table.o ast.o bool.o parser.o lexer.o hash.o semantic_analyser.o

compile_all: driver.o code_gen.o symbol_table.o ast.o parser.o lexer.o hash.o bool.o semantic_analyser.o
	gcc -o compiler driver.c code_gen.c symbol_table.c ast.c parser.c lexer.c hash.c bool.c semantic_analyser.c
 
hellos: bool.o parser.o lexer.o hash.o ast.o symbol_table.o
	gcc -o stage2exe symbol_table.o ast.o parser.o lexer.o hash.o bool.o

ast: bool.o parser.o lexer.o hash.o ast.o
	gcc -o stage2exe bool.o ast.o parser.o lexer.o hash.o

assembler: bool.o parser.o lexer.o hash.o ast.o code_gen.o symbol_table.o semantic_analyser.o
	gcc -o stage2exe code_gen.o bool.o ast.o parser.o lexer.o hash.o symbol_table.o semantic_analyser.o

code: code.o
	gcc -o code code.o

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

code.o: code.asm
	nasm -felf64 code.asm

driver.o: driver.c
	gcc -c driver.c

clean:
	rm *.o
