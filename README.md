# erplag-cc

**erplag-cc** is a compiler for the language `ERPLAG`. (see [specs](erplag_specs.pdf)), written in C. The compiler generates assembly code that can be run on a Linux machine. `(NASM, v2.14.0, 64-bit)`

The name `erplag` is derived from names of these 6 Turing Award Winners:

```
E = Edsger W Dijkstra (1972)
R = Ritchie, Dennis (1983)
P = Patterson, David (2017)
L = Lamport, Leslie (2013)
A = Allen, Elizabeth (2006)
G = Geoffrey Hinton (2018)
```

## Build

Run `make` to link and create the compiler executable
```
$ make
```
Execute the compiler with an erplag file, `test.erplag`, and store the assembly code into `code.asm`  
```
$ ./compiler test.erplag code.asm
```
Finally, use [nasm](https://www.nasm.us/pub/nasm/releasebuilds/?C=M;O=D) to run the assembly code
```
$ nasm -felf64 code.asm && gcc -o exec code.o && ./exec
```

## Compilation Steps

The compilation is broken into the following steps. (see [Dragon Book](https://en.wikipedia.org/wiki/Compilers:_Principles,_Techniques,_and_Tools)):

* [Lexer](lexer.c) (tokenizer)
* [Parser](parser.c) (and syntax checking)
* [Abstract Syntax Tree](ast.c) (with ~60% compression)
* [Symbol Table](symbol_table.c) (and static type checking)
* [Semantic Analysis](semantic_analyser.c)
* [Code Generation](code_gen.c) (and runtime checking)

Visualization for each of these steps is available. For instance, this is how a part of the Syntax Tree looks like:

<img src="https://github.com/7vik/erplag-cc/blob/master/ast_visual.png" width="500" height="300">

## Features:

Some salient features of `ERPLAG` are:
- Scientific notation support for real numbers
- Dynamically created and bounded arrays
- Multiple function return values 
- Indirect recursive calls
- Direct, user-prompt input support for arrays

Other features like loops, conditionals, scopes, declarations are similar to their Pascal/C counterparts.

## Authors

* Ayush Jain (<f20170093@pilani-bits-pilani.ac.in>)
* Satvik Golechha (<f20170117@pilani-bits-pilani.ac.in>)
* Bharat Bhargava (<f20170025@pilani-bits-pilani.ac.in>)

## Notes:

- A big thanks to [Divesh](https://github.com/diveshuttam) for his amazing AST visualiser.
- [This](https://www.cs.cmu.edu/~aplatzer/course/Compilers/waitegoos.pdf) was an excellent reference.
- A nice [tutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/) for nasm.
- nasm [docs](https://www.nasm.us/doc/).
- nasm debugging [guide](https://www.cs.umb.edu/~cheungr/cs341/Using_gdb_for_Assembly.pdf)

## License
[MPL-2.0](https://github.com/7vik/erplag-cc/blob/master/LICENSE)
