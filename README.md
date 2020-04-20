# erplag-cc

ERPLAG-CC is a compiler for the language "ERPLAG". (see specs), written in C.

ERPLAG is derived from names of these 6 Turing Award Winners:

```
E = Edsger W Dijkstra (1972)
R = Ritchie, Dennis (1983)
P = Patterson, David (2017)
L = Lamport, Leslie (2013)
A = Allen, Elizabeth (2006)
G = Geoffrey Hinton (2018)
```

This project is part of our course requirement for CS-F363 "Compiler Construction", and mentored by Prof. Vandana Agarwal. 

# How to run (to test for different pointer problem)
```
$ cd stage_2
$ make assembler
$ ./stage2exe satvik_testcase.txt delete.asm new.new
```

In the console output, look for the 2 pointers just below two lines starting with `BIG` near the top of the output.


# References:

- https://www.cs.cmu.edu/~aplatzer/course/Compilers/waitegoos.pdf: Seems to be an excellent reference for implementation.

# Note:

- One can also visualize a json file at https://diveshuttam.github.io/CS-F363/graphics/visualize

# How to build ID symbol table

- observe symbol_table_id.c and symbol_table_id.h on ayush_branch.
- make 
- ./stage2exe t5.txt test.txt
- This will print the symbol table on console

# Resources for NASM

- Excellent tutorial: https://cs.lmu.edu/~ray/notes/nasmtutorial/
- Official documentation: https://www.nasm.us/doc/
- Use of scanf: https://stackoverflow.com/questions/10973650/how-to-use-scanf-in-nasm 3rd answer, very helpful
- Use of printf: https://stackoverflow.com/questions/20808039/print-a-string-out-by-letter-in-assembler-nasm first answer
- Excellent sample programs, highly commented. https://www.csee.umbc.edu/portal/help/nasm/sample.shtml
- Debugging guide: https://www.cs.umb.edu/~cheungr/cs341/Using_gdb_for_Assembly.pdf
- Floating: https://www.reddit.com/r/learnprogramming/comments/2sv4x1/assembly_x8664_homework_float_inputs_reading/
