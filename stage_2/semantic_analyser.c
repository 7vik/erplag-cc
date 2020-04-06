/************************************
 * Semantic Rules to handle: 
 * 
An identifier cannot be declared multiple times in the same scope.
An identifier must be declared before its use.
The types and the number of parameters returned by a function must be the same as that of the parameters used in invoking the function.
The parameters being returned by a function must be assigned a value. If a parameter does not get a value assigned within the function definition, it should be reported as an error.
The function that does not return any value, must be invoked appropriately.
Function input parameters passed while invoking it should be of the same type as those used in the function definition.
A switch statement with an integer typed identifier associated with it, can have case statement with case keyword followed by an integer only and the case statements must be followed by a default statement.
A switch statement with an identifier of type real is not valid and an error should be reported.
A switch statement with a boolean type identifier can have the case statements with labels true and false only. The switch statement then should not have a default statement.
Function overloading is not allowed.
A function declaration for a function being used (say F1) by another (say F2) must precede the definition of the function using it(i.e. F2), only if the function definition of F1 does not precede the definition of F2.
If the function definition of F1 precedes function definition of F2(the one which uses F1), then the function declaration of F1 is redundant and is not valid.
A for statement must not redefine the variable that participates in the iterating over the range.
The function cannot be invoked recursively.
An identifier used beyond its scope must be viewed as undefined
etc. (More semantics will be made available in the test cases)

******************************************/

#include "semantic_analyser.h"

bool hasSemanticError = false;


void semantic_analyser(astNode* root, GST* global_st)
{
    if(root != NULL)
    {
        // invoke module analyser on each module
    }
}
