/************************************
 * Semantic Rules to handle: 
 * 
1. An identifier cannot be declared multiple times in the same scope.   //declStmt  -- 7vik
2. An identifier must be declared before its use.      //declStmt   -- 7vik
3. The types and the number of parameters returned by a function must be the same as that //stmts
   of the parameters used in invoking the function.
4. The parameters being returned by a function must be assigned a value. If a parameter does  // module
    not get a value assigned within the function definition, it should be reported as an error.
5. The function that does not return any value, must be invoked appropriately. // stmt
6. Function input parameters passed while invoking it should be of the same type as those used in the function definition. //stmt
7. A switch statement with an integer typed identifier associated with it, //caseStmt
   can have case statement with case keyword followed by an integer only and the case statements must be followed by a default statement.
8. A switch statement with an identifier of type real is not valid and an error should be reported. //caseStmt
9. A switch statement with a boolean type identifier can have the case statements with labels true and false only. //caseStmt
   The switch statement then should not have a default statement.
10. Function overloading is not allowed.  // function redeclaration error: handled while filling
11. A function declaration for a function being used (say F1) by another (say F2) must precede the definition of the function using it(i.e. F2),
    only if the function definition of F1 does not precede the definition of F2.  //stmt
12. If the function definition of F1 precedes function definition of F2(the one which uses F1),
    then the function declaration of F1 is redundant and is not valid.  //stmt
13. A for statement must not redefine the variable that participates in the iterating over the range. //forStmt
14. The function cannot be invoked recursively.  //stmt
15. An identifier used beyond its scope must be viewed as undefined  //stmt
etc. (More semantics will be made available in the test cases) 

******************************************/

#include "semantic_analyser.h"
#include <assert.h>

bool hasSemanticError = false;


void semantic_analyser(astNode* root, GST* global_st)
{
    if(root != NULL)
    {
        assert(root->node_marker == program);
        
        astNode* temp = root->child;
        check_moduleDeclarations_semantic(temp, global_st);
        temp = temp->sibling;

        check_otherModules_semantic(temp, global_st);
        temp = temp->sibling;

        check_driverModule_semantic(temp, global_st);
        temp = temp->sibling;

        check_otherModules_semantic(temp, global_st);

        return;

    }

    else
    {
        printf("ERROR: Root node given to semantic analyser is NULL\n");
        exit(1);
    }
}

void check_moduleDeclarations_semantic(astNode* root, GST* global_st)
{
    if(root->node_marker == EPS)
        return;

    assert(root->node_marker == moduleDeclarations);

    astNode* temp = root->child;

    while(temp != NULL)
    {
        FUNC_TABLE_ENTRY* func = global_st_lookup(temp->tree_node->lexeme, global_st);

        if(func == NULL)
        {
            hasSemanticError = true;
            printf("Semantic error at line %d, No Defination found for declared function %s \n", temp->tree_node->line, temp->tree_node->lexeme);
        }
        else
        {
            func->is_declared = true;
        }
        
    }
    return;
}

void check_otherModules_semantic(astNode* root, GST* global_st)
{
    if(root->node_marker == EPS)
        return;
        
    assert(root->node_marker == otherModules);

    astNode* temp = root->child;

    while(temp != NULL)
    {
        check_module_semantic(temp, global_st);
        temp = temp->sibling;
    }
    return;
}

void check_driverModule_semantic(astNode* root, GST* global_st)
{
    assert(root->node_marker == driverModule);

    // astNode* temp = root->child;
    // check_moduleDef_semantic(temp, global_st);

    check_module_semantic(root, global_st);
    
    return;
}

void check_moduleDef_semantic(astNode* root, FUNC_TABLE_ENTRY* func_entry)
{
    assert(root->node_marker == moduleDef);

    astNode* temp = root->child;

    ID_SYMBOL_TABLE* id_table = func_entry->local_id_table;

    check_statements_semantic(temp->sibling, id_table);
    
    return;
}

void check_module_semantic(astNode* root, GST* global_st)
{
    assert(root->node_marker == module || root->node_marker == driverModule);

    astNode* temp = root->child;
    FUNC_TABLE_ENTRY* func_entry = global_st_lookup(temp->tree_node->lexeme, global_st);

    if (func_entry == NULL)
    {
        printf("ERROR in check module, function entry should have been there in symbol table\n");
        exit(1);
    }


    check_moduleDef_semantic(temp->sibling->sibling->sibling->sibling, func_entry);
    return; 
}

void check_statements_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == statements);

    astNode* temp = root->child;
    
    while(temp != NULL)
    {
        if (temp->node_marker == declareStmt)
            check_declareStmt_semantic(temp, id_table);
        else if (temp->node_marker == ioStmt)
            check_ioStmt_semantic(temp, id_table);
        else if (temp->node_marker == assignmentStmt)
            check_assignmentStmt_semantic(temp, id_table);
        else if (temp->node_marker == iterativeStmt)
            check_iterativeStmt_semantic(temp, id_table);
        else if (temp->node_marker = conditionalStmt)
            check_conditionalStmt_semantic(temp, id_table);
        else if (temp->node_marker == moduleReuseStmt)
            check_moduleReuseStmt_semantic(temp, id_table);
        else
        {
            printf("ERROR: Unidentified statement: %s\n", variables_array[temp->node_marker]);
            exit(1);
        }
            
        temp = temp->sibling;
    }

    return; 
}

void check_declareStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == declareStmt);
    
    // no semantic rules required, checks done during type checking
    return;
}


void check_ioStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == ioStmt);

    //no semantic 
    return;
}


void check_assignmentStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == assignmentStmt);

    astNode* op_node = root->child->child->sibling;

    check_var_semantic(op_node->child, id_table);
    check_var_semantic(op_node->child->sibling, id_table);
    return;
}


void check_iterativeStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == iterativeStmt);

    return;
}


void check_conditionalStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == conditionalStmt);

    return;
}


void check_moduleReuseStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == moduleReuseStmt);

    return;
}

void check_var_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == var);

    // if two nodes, then it is arr, bound checking
    if(root->child->sibling != NULL)
    {
        astNode* var_node = root->child;
        astNode* index_node = var_node->sibling;

        //finding the id table entry for var

        ID_TABLE_ENTRY* id_entry =  st_lookup(var_node->tree_node->lexeme, id_table);

        if (id_entry == NULL)
        {
            printf("SEMANTIC ERROR at line %d: undeclared variable %s", var_node->tree_node->line, var_node->tree_node->lexeme);
            hasSemanticError = true;
            return;
        }

        if(id_entry->datatype->arrtype->is_dynamic == true)
            return;
        
        else  //bound check
        {
            // I don'rt know what to do, touba aage kya karun :(
        }
        
    }
    return;
}