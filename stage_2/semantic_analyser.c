/************************************
 * Semantic Rules to handle: 
 * 
1. An identifier cannot be declared multiple times in the same scope.   //declStmt  -- 7vik
2. An identifier must be declared before its use.      //declStmt   -- 7vik
3. The types and the number of parameters returned by a function must be the same as that // moduleReusetmt
   of the parameters used in invoking the function.
4. The parameters being returned by a function must be assigned a value. If a parameter does  // module
    not get a value assigned within the function definition, it should be reported as an error.
5. The function that does not return any value, must be invoked appropriately. // stmt
6. Function input parameters passed while invoking it should be of the same type as those used in the function definition. // moduleReuseStmt
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
#include <stdlib.h>

void semantic_analyser(astNode* root, GST* global_st)
{
    if(root != NULL)
    {
        assert(root->node_marker == program);
        astNode* temp = root->child;
        if(temp->node_marker == moduleDeclarations)
        {
            check_moduleDeclarations_semantic(temp, global_st);
	        temp = temp->sibling;
        }
	    else if(temp->node_marker == EPS)
	        temp = temp->sibling;
    
        if(temp->node_marker == otherModules)
        {
            check_otherModules_semantic(temp, global_st);
	        temp = temp->sibling;
        }
	    else if(temp->node_marker == EPS)
	        temp = temp->sibling;

        if(temp->node_marker == driverModule)
        {
            check_driverModule_semantic(temp, global_st);
	        temp = temp->sibling;
        }
	    else if(temp->node_marker == EPS)
	    	temp = temp->sibling;

        if(temp->node_marker == otherModules)
        {
            check_otherModules_semantic(temp, global_st);
        }
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
    //printf("Entered this zone\n");
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
            printf("Semantic error at line %d, No definition found for declared function %s \n", temp->tree_node->line, temp->tree_node->lexeme);
        }
        else    // the function is already defined later.
        {
            func->is_declared += 1;
        }
        
        temp = temp->sibling;
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
    astNode* temp = root->child;   //moduleDef node
    FUNC_TABLE_ENTRY* func_entry = global_st_lookup(root->tree_node->node_symbol, global_st);
    check_moduleDef_semantic(temp, func_entry);
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
    assert(root->node_marker == module);

    astNode* temp = root->child;  //name of function is here
    FUNC_TABLE_ENTRY* func_entry = global_st_lookup(temp->tree_node->lexeme, global_st);
    PARAMS *out_par = NULL;
    if (func_entry == NULL)
    {
        hasSemanticError = true;
        return;
        //printf("ERROR in check module, function entry should have been there in symbol table\n");
    }
    else // the function is defined
    {
        func_entry->is_declared += 1;
        out_par = func_entry->out_params;
        while(out_par != NULL)
        {
            if(out_par->is_assigned == 0)
            {
                hasSemanticError = true;
                printf("Semantic error in the definition of function '%s'. Output formal parameter '%s' not assigned any value in the body.\n", func_entry->func_name, out_par->param_name);
            }
            out_par = out_par->next;
        }
    }
    
    check_moduleDef_semantic(temp->sibling->sibling->sibling, func_entry);

    return; 
}

void check_statements_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    if(root->node_marker == EPS)
        return;

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
        else if (temp->node_marker == conditionalStmt)
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
    // no semantic rules required here as checks done during type checking
    return;
}


void check_ioStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == ioStmt);
    //no semantic rules required here; to be checked during code generation
    return;
}

// needs to be chenged, check whatsapp pics
void check_assignmentStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{

    if (root == NULL)
        return;
    //assert(root->node_marker == assignmentStmt);
    astNode* temp;
    if (root->node_marker == assignmentStmt)
    {
        temp = root->child;
        check_assignmentStmt_semantic(temp, id_table);
        return;
    }

    else
    {
        if (root->node_marker == var)
        {
            if (root->child->sibling != NULL)
            {   
                check_var_semantic(root, id_table);
            }
        }
        else
        {
            temp = root->child;
            while(temp != NULL)
            {
                check_assignmentStmt_semantic(temp, id_table);
                temp = temp->sibling;
            }
        }
        
    }
    
    
    return;
    // array assignment
    

}


void check_iterativeStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == iterativeStmt);
    astNode* temp = root->child;

    ID_SYMBOL_TABLE* id_child_table = NULL;
    
    if(temp->node_marker == ID) // it's for construct
    {
        temp = temp->sibling;   // temp points to range

        temp = temp->sibling;   // temp points to START
        id_child_table = id_table->kid_st[id_table->visited];
    
        temp = temp->sibling;   // temp points to statements construct
        check_statements_semantic(temp, id_child_table);

        temp = temp->sibling;   // temp points to END
        id_table->visited += 1;
    }

    else    // it's while construct
    {
        temp = temp->sibling;   // temp points to START
        id_child_table = id_table->kid_st[id_table->visited];
    
        temp = temp->sibling;   // temp points to statements construct
        check_statements_semantic(temp, id_child_table);

        temp = temp->sibling;   // temp points to END
        id_table->visited += 1;
    }

    return;
}


void check_conditionalStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == conditionalStmt);
    astNode* temp = root->child;

    ID_TABLE_ENTRY* id_entry = st_lookup(temp->tree_node->lexeme, id_table);
    TYPE* datatype;
    if(id_entry == NULL)
    {
        PARAMS* p = param_lookup(id_table->primogenitor->in_params, temp->tree_node->lexeme);
        if(p == NULL)
            p = param_lookup(id_table->primogenitor->out_params, temp->tree_node->lexeme);
        datatype = p->datatype;
    }

    else
    {
        datatype = id_entry->datatype;
    }
    

    if(datatype->simple == ARRAY) // How can the switch variable be an array variable?
    {
        printf("SEMANTIC ERROR at line %d: %s is an array variable.\n", temp->tree_node->line, temp->tree_node->lexeme);
        hasSemanticError = true;
	    return;
    }

    else if(datatype->simple == REAL) // Nah, still not over; this cannot be of type "real" as well.
    {
        printf("SEMANTIC ERROR at line %d: %s is a variable of type real.\n", temp->tree_node->line, temp->tree_node->lexeme);
        hasSemanticError = true;
	    return;
    }
    // I assume Satvik would handle the remaining cases associated with type for identifier.
    // Comment out anything from the above if-else if construct which is redundant.

    temp = temp->sibling;

    // now, we are on START
    ID_SYMBOL_TABLE* id_child_table = id_table->kid_st[id_table->visited];
    temp = temp->sibling;
    
    // we are now on caseStmts
    check_caseStmts_semantic(temp, id_child_table, id_entry);
    temp = temp->sibling;

    // we are now on default_nt
    check_default_nt_semantic(temp, id_child_table, id_entry);
    temp = temp->sibling;

    // we are now on END
    id_table->visited += 1;

    return;
}

void check_caseStmts_semantic(astNode* root, ID_SYMBOL_TABLE* id_child_table, ID_TABLE_ENTRY* id_entry)
{
    assert(root->node_marker == caseStmts);
    astNode* temp = root->child;

    // Boolean type switch variable should have "exactly" 2 cases- true and false
    if(id_entry->datatype->simple == BOOLEAN)
    {
        if(temp->sibling == NULL) // we need to have 2 cases, only one case present
        {
            printf("SEMANTIC ERROR at line %d: boolean conditional statement cannot have a single case.\n", temp->child->tree_node->line);
            hasSemanticError = true;
        }
        else if(temp->sibling->sibling != NULL) // we're having >=3 cases! Binary system: 0, 1, and ?? => Error
        {
            printf("SEMANTIC ERROR at line %d: boolean conditional statement cannot have more than two cases.\n", temp->sibling->sibling->child->tree_node->line);
            hasSemanticError = true;
        }
        // if we haven't entered any aforementioned condition, we now have 2 case statements in the construct

        else if(temp->child->node_marker == TRUE && temp->sibling->child->node_marker == TRUE)
        {
            printf("SEMANTIC ERROR at line %d: The two boolean conditions cannot have the same case variable TRUE.\n", temp->sibling->child->tree_node->line);
            hasSemanticError = true;
        }        

        else if(temp->child->node_marker == FALSE && temp->sibling->child->node_marker == FALSE)
        {
            printf("SEMANTIC ERROR at line %d: The two boolean conditions cannot have the same case variable FALSE.\n", temp->sibling->child->tree_node->line);
            hasSemanticError = true;
        }
    }
    
    while(temp != NULL)
    {
        check_caseStmt_semantic(temp, id_child_table, id_entry);
        temp = temp->sibling;
    }

    return;
}

void check_caseStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_child_table, ID_TABLE_ENTRY* id_entry)
{
    assert(root->node_marker == caseStmt);
    astNode* temp = root->child;

    // ARRAY! - No need of it, though, we would never enter this condition!
    if(id_entry->datatype->simple == ARRAY)
    {
        printf("SEMANTIC ERROR at line %d: %s is an array variable.\n", temp->tree_node->line, id_entry->lexeme);
        hasSemanticError = true;
    }

    // Type mismatch condition(s)
    else if(((id_entry->datatype->simple == INTEGER) && (temp->node_marker != NUM)) || ((id_entry->datatype->simple == BOOLEAN) && (temp->node_marker == NUM)))
    {
        printf("SEMANTIC ERROR at line %d: Types of switch variable %s and case entry %s mismatch.\n", temp->tree_node->line, id_entry->lexeme, temp->tree_node->lexeme);
        hasSemanticError = true;
    }

    temp = temp->sibling;   //we're on statements node
    check_statements_semantic(temp, id_child_table);

    return;
}

void check_default_nt_semantic(astNode* root, ID_SYMBOL_TABLE* id_child_table, ID_TABLE_ENTRY* id_entry)
{
    if(id_entry->datatype->simple == ARRAY) // ARRAY!
    {
        printf("SEMANTIC ERROR at line %d: %s is an array variable.\n", root->tree_node->line, id_entry->lexeme);
        hasSemanticError = true;
        return;
    }

    // Now, the type of switch variable is integer, but node marker says default not present
    else if(root->node_marker == EPS && id_entry->datatype->simple == INTEGER)
    {
        printf("SEMANTIC ERROR at line %d: A default statement must have been present here.\n",root->sibling->tree_node->line);
        hasSemanticError = true;
        return;
    }

    else if(root->node_marker == default_nt && id_entry->datatype->simple == BOOLEAN)   // Now, why default?
    {
        printf("SEMANTIC ERROR at line %d: A default statement shouldn't have been present here.\n", root->sibling->tree_node->line);
        hasSemanticError = true;
        return;
    }

    if(id_entry->datatype->simple == INTEGER)
        check_statements_semantic(root->child, id_child_table);

    return;
}

void check_moduleReuseStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == moduleReuseStmt);
    astNode* temp = root->child;

    GST* global_table = id_table->primogenitor->procreator;
    FUNC_TABLE_ENTRY* func_entry = global_st_lookup(temp->sibling->tree_node->lexeme, global_table);

    if(func_entry == NULL)  // what if the function is not defined?
    {
        printf("SEMANTIC ERROR at line %d: Function '%s' not defined.\n", temp->sibling->tree_node->line, temp->sibling->tree_node->lexeme);
        hasSemanticError = true;
        return;
    }
    // we reach here <=> the function is defined
    else if(func_entry->is_declared == 2) // the function is both defined and declared before the call- an error!
    {
        printf("SEMANTIC ERROR at line %d: Function '%s' has a redundant declaration.\n", temp->sibling->tree_node->line, temp->sibling->tree_node->lexeme);
        hasSemanticError = true;
    }

    else if(func_entry->is_declared == 0) // function neither declared nor defined before the call- an error!
    {
        printf("SEMANTIC ERROR at line %d: Function '%s' should have had a declaration before.\n", temp->sibling->tree_node->line, temp->sibling->tree_node->lexeme);
        hasSemanticError = true;
    }

    /*
    func_entry->is_declared == 1 with function entry non-NULL in GST => the following possible cases:
    1. The function is just declared before the call; its definition is about to come.
    2. Only the definition of the function is given before the call.
    Both of them are valid as per the specifications.
    */

    // The language does not support DIRECT recursion.
    FUNC_TABLE_ENTRY* rec_func = id_table->primogenitor;
    if(strcmp(rec_func->func_name, func_entry->func_name) == 0)
    {
        printf("SEMANTIC ERROR at line %d: The language does not support direct recursion.\n", temp->sibling->tree_node->line);
        hasSemanticError = true;
    }

    // now, the node marker for temp is either ASSIGNOP or EPS
    if(temp->node_marker == EPS && func_entry->out_params != NULL)  // the function returns some value(s)
    {
        printf("SEMANTIC ERROR at line %d: Function '%s' returns some value(s).\n", temp->sibling->tree_node->line, func_entry->func_name);
        hasSemanticError = true;
    }
    else if(temp->node_marker != EPS && func_entry->out_params == NULL)  // the function does not return any value
    {
        printf("SEMANTIC ERROR at line %d: Function '%s' does not return any value.\n", temp->tree_node->line, func_entry->func_name);
        hasSemanticError = true;
    }

    astNode* trav1 = temp->child;
    int count_ret1 = 0;

    PARAMS* trav2 = func_entry->out_params;
    int count_ret2 = 0;

    ID_TABLE_ENTRY* lookup_id;

    while(trav1 != NULL && trav1->node_marker != EPS)
    {
        count_ret1++;
        lookup_id = st_lookup(trav1->tree_node->lexeme, id_table);

        if(lookup_id != NULL && lookup_id->datatype->simple == ARRAY)
        {
            printf("SEMANTIC ERROR at line %d: Return actual parameter %s has type array.\n", trav1->tree_node->line, trav1->tree_node->lexeme);
            hasSemanticError = true;
        }
        trav1 = trav1->sibling;
    }
    while(trav2 != NULL)  // might need a modification in the condition here!
    {
        count_ret2++;
        trav2 = trav2->next;
    }

    if(count_ret1 != count_ret2)
    {
        printf("SEMANTIC ERROR at line %d: Mismatch in the number of return values in definition and usage of function '%s'.\n", temp->sibling->tree_node->line, func_entry->func_name);
        hasSemanticError = true;
    }
    else if(count_ret1 != 0 && count_ret2 != 0) /* count_ret1 equals count_ret2, now traverse again and match the types */
    {
        trav1 = temp->child;
        trav2 = func_entry->out_params;
        while(trav2 != NULL)
        {
            lookup_id = st_lookup(trav1->tree_node->lexeme, id_table);
            PARAMS *p = NULL;
            TYPE *dt = NULL;
            if (lookup_id == NULL)
            {
                p = param_lookup(id_table->primogenitor->in_params, trav1->tree_node->lexeme);
                if (p == NULL)
                    p = param_lookup(id_table->primogenitor->out_params, trav1->tree_node->lexeme);
                if (p == NULL)
                {   
                    printf("SEMANTIC ERROR at line %d: Undeclared variable %s.\n", trav1->tree_node->line, trav1->tree_node->lexeme);
                    hasSemanticError = true;
                    trav1 = trav1->sibling;
                    trav2 = trav2->next;
                    continue;
                }
                else
                    dt = p->datatype;
            }
            else
                dt = lookup_id->datatype;
            if(dt->simple != trav2->datatype->simple)
            {
                printf("SEMANTIC ERROR at line %d: Output variable %s should have type %s.\n", trav1->tree_node->line, trav1->tree_node->lexeme, variables_array[trav2->datatype->simple]);
                hasSemanticError = true;
            }
            trav1 = trav1->sibling;
            trav2 = trav2->next;
        }
    }

    // moving on to the list of input parameters.
    temp = temp->sibling->sibling;

    trav1 = temp->child;
    int count_inp1 = 0;

    trav2 = func_entry->in_params;
    int count_inp2 = 0;

    while(trav1 != NULL && trav1->node_marker != EPS && trav2 != NULL)
    {
        PARAMS *p = NULL;
        TYPE *dt = NULL;
        lookup_id = st_lookup(trav1->tree_node->lexeme, id_table);
        if (lookup_id == NULL)
        {
            p = param_lookup(id_table->primogenitor->in_params ,trav1->tree_node->lexeme);
            if (p == NULL)
                p = param_lookup(id_table->primogenitor->out_params ,trav1->tree_node->lexeme);
            if (p == NULL)
            {   
                printf("SEMANTIC ERROR at line %d: Undeclared variable %s.\n", trav1->tree_node->line, trav1->tree_node->lexeme);
                hasSemanticError = true;
                count_inp1++;
                count_inp2++;
                trav1 = trav1->sibling;
                trav2 = trav2->next;
                continue;
            }
            else
                dt = p->datatype;
        }
        else
            dt = lookup_id->datatype; 
        if(dt->simple != trav2->datatype->simple)
        {
            printf("SEMANTIC ERROR at line %d: Input variable %s should have type %s.\n", trav1->tree_node->line, trav1->tree_node->lexeme, variables_array[trav2->datatype->simple]);
            hasSemanticError = true;
        }
        else if(dt->simple == ARRAY && trav2->datatype->simple == ARRAY)
        {
            if(trav2->datatype->arrtype->base_type != dt->arrtype->base_type)
            {
                printf("SEMANTIC ERROR at line %d: Inconsistent type of array actual parameter %s due to base type mismatch.\n", trav1->tree_node->line, trav1->tree_node->lexeme);
                hasSemanticError = true;
            }
            if((trav2->datatype->arrtype->begin != dt->arrtype->begin) || (trav2->datatype->arrtype->end != dt->arrtype->end))
            {
                printf("SEMANTIC ERROR at line %d: Inconsistent type of array actual parameter %s due to improper begin and/or end index.\n", trav1->tree_node->line, trav1->tree_node->lexeme);
                hasSemanticError = true;
            }
        }
        count_inp1++;
        count_inp2++;
        trav1 = trav1->sibling;
        trav2 = trav2->next;
    }

    while(trav1->node_marker != EPS)
    {
        count_inp1++;
        trav1 = trav1->sibling;
    }

    while(trav2 != NULL)
    {
        count_inp2++;
        trav2 = trav2->next;
    }

    if(count_inp1 != count_inp2)
    {
        printf("SEMANTIC ERROR at line %d: Mismatch in the number of input values in definition and usage of function '%s'.\n", temp->child->tree_node->line, func_entry->func_name);
        hasSemanticError = true;
    }
    // Rest of the semantics should be dealt with during type checking phase.
    // Comment out any check if already dealt with previously.
    return;
}

void check_var_semantic(astNode* root, ID_SYMBOL_TABLE* id_table)
{
    assert(root->node_marker == var);

    return;

    
    // if two nodes, then it is arr, bound checking
    if(root->child->sibling != NULL)
    {
        astNode* var_node = root->child;
        astNode* index_node = var_node->sibling;

        //finding the id table entry for var

        ID_TABLE_ENTRY* id_entry =  st_lookup(var_node->tree_node->lexeme, id_table);

        if (id_entry == NULL)
        {

            // // if satvik handles this, comment out below 2 lines
            // printf("SEMANTIC ERROR at line %d: undeclared variable %s", var_node->tree_node->line, var_node->tree_node->lexeme);
            // hasSemanticError = true;

            // won't check if array not declared
            return;
        }

        if(id_entry->datatype->arrtype->is_dynamic == true)
            return;
        
        else  //bound check: it would obviously enter 'else' in case the array is static
        {
            
            if (index_node->node_marker == ID)
                return;
            else
            {
                if(index_node->node_marker != NUM)
                {
                    printf("Semantic Error at line %d: Array index should be a number - found %s\n", index_node->tree_node->line, variables_array[index_node->node_marker]);
                    hasSemanticError = true;
                    return;
                }

                int low_index = id_entry->datatype->arrtype->begin;
                int high_index = id_entry->datatype->arrtype->end;

                if(low_index > high_index)
                {
                    printf("Semantic Error at line %d: The lower index of array %s, %d, is greater than the upper index, %d\n", var_node->tree_node->line, var_node->tree_node->lexeme, low_index, high_index);
                    hasSemanticError = true;
                }

                int index = atoi(index_node->tree_node->lexeme);
                if (index < low_index || index > high_index)
                {
                    printf("Semantic Error: Out of bound error at line %d - index should lie between %d and %d, got %s\n", index_node->tree_node->line, low_index, high_index, index_node->tree_node->lexeme);
                    hasSemanticError = true;
                }

                return;
            }
            
        }
        
    }
    return;
}

/*
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Invalid argument count. Expected 3 arguments as in './executable testcase parse_outfile'.");
        printf("\nAborting Execution!!\n");
        exit(2);
    }
    FILE* test_fp = fopen(argv[1], "r");
    FILE* test_parse_fp = fopen(argv[2], "w");
    populate_ht(hash_table, KEYWORDS_FILE);
    int line_count = 1;
    TWIN_BUFFER *twin_buff = (TWIN_BUFFER *) malloc(sizeof(TWIN_BUFFER));
    init_buffer(test_fp, twin_buff);
    GRAMMAR* grammar = generate_grammar();
    first_follow *ff = get_first_follow_table(grammar);
    TABLE *parse_table = (TABLE *) malloc(sizeof(TABLE));
    create_parse_table(ff, parse_table, grammar);

    STACK *stack = NULL;
    PARSE_TREE *tree;
    parse(grammar, test_fp, parse_table, &tree, stack, twin_buff, &line_count);
    fprintf(test_parse_fp, "%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s%20s\n\n", "LEXEME", "LINE_NO", "VALUE (if num)", "TOKENAME",  "PARENT", "IS LEAF?", "NODE SYMBOL", "RULE_NUMBER");
    print_parse_tree(tree, test_parse_fp);
    print_parse_tree_json(tree, "output_parse_tree.json");
    printf("Printed Parse Tree in file '%s'.\n", argv[2]);
    astNode* ast_root = buildAST(tree);
    print_ast_json(ast_root, "output_ast_tree.json");

    // Test Symbol table
    GST *st = create_global_st();
    traverse_the_multiverse(ast_root, st);
    gst_print(st);

    semantic_analyser(ast_root, st);

    fclose(test_fp);
    fclose(test_parse_fp);
    free(twin_buff);
    free(parse_table);
    return 0;
}
*/