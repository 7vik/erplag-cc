// gcc symbol_table.c ast.c parser.c lexer.c hash.c bool.c

#include "symbol_table.h"
#include "type.h"
#include<stdlib.h>                                      // int atoi(), char *strcat()
#include<string.h>                                      // char *strcpy()
#define ST_ABS(N) ((N<0)?(-N):(N))                      // because of my awesome hashing function
#define malloc_error { printf("Malloc error. Terminating.\n\n"); exit(5); }
#define IN_PARAM_OFFSET 1
#define OUT_PARAM_OFFSET 13


bool hasSemanticError = false;
unsigned int current_offset = 0;
unsigned int error_line = 0;

// hash function: implementing hash, patent pending ;)
int st_hash(char *s261)
{
    int n261 = 261;
    int h261 = 261;
    while ((n261 = *s261++))
        h261 = (261 - 216 - 16 + 2) * h261 + n261;
    return (ST_ABS(h261 % ST_ID_SIZE));
}

// we initialize our symbol table of identifiers
ID_SYMBOL_TABLE *create_id_st(ID_SYMBOL_TABLE *papa)
{
    ID_SYMBOL_TABLE *id_table = (ID_SYMBOL_TABLE *) malloc(sizeof(ID_SYMBOL_TABLE));
    for (int iterator = 0; iterator < ST_ID_SIZE; ++iterator)
        id_table->id_table[iterator] = NULL;                        // no symbols initially in the table
    id_table->total_ids = 0;
    id_table->kid_table_count = 0;
    id_table->visited = 0;
    if (papa != NULL)
        id_table->primogenitor = papa->primogenitor;
    for (short int i = 0; i < ST_KID_NUM; ++i)
        id_table->kid_st[i] = NULL;
    id_table->id_st_parent = papa;
    return id_table;
}

// now, we insert id to our ST of identifiers
// ID entry should have been populated.
void st_insert_id_entry(ID_TABLE_ENTRY *sym, ID_SYMBOL_TABLE *st)
{
    int key = st_hash(sym->lexeme);     // calculate the hash to find out where to insert this entry
    if (st->id_table[key] == NULL)      // if there is no collision,
        st->id_table[key] = sym;        // just add it
    else                                // collision resolved by
    {
        ID_TABLE_ENTRY *temp = st->id_table[key];       // going to the end of list
        while (temp->next)
            temp = temp->next;
        temp->next = sym;                               // and adding it there
    }
    st->total_ids += 1;                                 // finally, increment total kids,
    sym->offset = current_offset++;                     // and the offset
    if (sym->datatype->simple == ARRAY)                 // unless if it's an array,
    {
        sym->datatype->arrtype->begin_offset = current_offset++;            // in which case,
        sym->datatype->arrtype->end_offset   = current_offset++;            // fill the offsets
    }
    return;
}

char *show_type(TYPE *t)
{
    if (t->simple == INTEGER) return "INTEGER";
    if (t->simple == REAL   ) return "REAL";
    if (t->simple == BOOLEAN) return "BOOLEAN";
    if (t->simple == ARRAY  )
    {
        char *array_type_str = (char *) malloc(42);
        strcpy(array_type_str, "ARRAY {");
        //
        int x1 = t->arrtype->begin_offset;
        int x2 = t->arrtype->end_offset;
        int l1 = snprintf( NULL, 0, "%d", x1);
        int l2 = snprintf( NULL, 0, "%d", x2);
        char* str1 = malloc( l1 + 1 );                              // very small malloc, so trusting C and
        char* str2 = malloc( l2 + 1 );                              // not putting malloc_error
        snprintf( str1, l1 + 1, "%d", x1);
        snprintf( str2, l2 + 1, "%d", x2);
        //
        strcat(array_type_str, str1);
        strcat(array_type_str, ",");
        strcat(array_type_str, str2);
        strcat(array_type_str, "} of ");
        strcat(array_type_str, variables_array[t->arrtype->base_type]);
        free(str1);
        free(str2);
        return array_type_str;
    }
    return NULL;
}

// helper function to print a symbol table of identifiers
void id_st_print(ID_SYMBOL_TABLE *st)
{
    if (st == NULL) return;
    printf("pointer inside print: %p\n", &(*(st)));
    printf("visited %d, %p\n", st->visited, &(st->visited));
    if (st->id_st_parent == NULL)
        printf("\tID ST with %d ids:\n\n", st->total_ids);
    else
        printf("\t\tInner ID_ST with %d ids:\n\n", st->total_ids);
    for(int i = 0; i < ST_ID_SIZE; i++)
    {
        ID_TABLE_ENTRY *temp = st->id_table[i];
        while(temp)
        {
            printf("\t\t%s\t:\t%s\t:%d\n", temp->lexeme, show_type(temp->datatype), temp->offset);
            temp = temp->next;
        }
    }
    for (int j = 0; j < st->kid_table_count; ++j)
        id_st_print(st->kid_st[j]);
    
    return;
}

// non-recursive ID symbol table lookup
ID_TABLE_ENTRY *st_lookup_nr(char *name, ID_SYMBOL_TABLE *st)
{
    // first, compute the key where the variable would be stored
    int key = st_hash(name);
    ID_TABLE_ENTRY *temp = st->id_table[key];
    while(temp)
    {
        if(strcmp(temp->lexeme, name) == 0)   // symbol found
            return temp;                    // return it
        temp = temp->next;
    }
    return NULL;
}

// lookup the symbol table of identifiers for name, and return the symbol if found
ID_TABLE_ENTRY *st_lookup(char *name, ID_SYMBOL_TABLE *st)
{
    // first, compute the key where the variable would be stored

    if (st == NULL)
        return NULL;
    int key = st_hash(name);
    ID_TABLE_ENTRY *temp = st->id_table[key];
    while(temp)
    {
        if(strcmp(temp->lexeme, name) == 0)   // symbol found
            return temp;                    // return it
        temp = temp->next;
    }
    if (st->id_st_parent == NULL)
        return NULL;                                // not found in any parents
    else
    {
        return st_lookup(name, st->id_st_parent);         // assuming scope only broadens with nesting, uncomment as per the requirement
    }
}

int get_width(TYPE *t)
{
    // printf("IN GET WITDH\n");
   int size = t->simple == INTEGER  ? 4
            : t->simple == REAL     ? 8
            : t->simple == BOOLEAN  ? 1
            : t->simple == ARRAY    ?   t->arrtype->base_type == INTEGER? (4 * (t->arrtype->end - t->arrtype->begin + 1))
                                :       t->arrtype->base_type == REAL   ? (8 * (t->arrtype->end - t->arrtype->begin + 1))
                                :       t->arrtype->base_type == BOOLEAN? (1 * (t->arrtype->end - t->arrtype->begin + 1))
                                :       0
            : 0;
    // printf("OUT GET WITDH\n");
    if (size > 1000 || size < -1000) return 1;
    return size;
}

// populating a id symbol table entry
ID_TABLE_ENTRY *create_symbol(astNode *node, TYPE *type)
{
    assert(strcmp(node->tree_node->token_name, "ID") == 0);             //this should have ID info
    ID_TABLE_ENTRY *new = (ID_TABLE_ENTRY *) malloc(sizeof(ID_TABLE_ENTRY));
    if (!new)
        malloc_error
    new->lexeme = node->tree_node->lexeme;
    new->datatype = type;
    new->width = get_width(type);
    new->next = NULL;
    new->is_declared = false;
    // new->offset will be filled in later, no point in initializing
    return new;
}

TYPE *get_type(astNode *n)          
{
    // printf("GET TYPE of %s\n", n->node_marker);
    TYPE *new = (TYPE *) malloc(sizeof(TYPE));
    if (!new)
        malloc_error
    new->simple = string_to_enum(n->sibling->tree_node->node_symbol);
    if (new->simple == ARRAY)
    {
        new->arrtype = (ARRAY_TYPE_DATA *) malloc(sizeof(ARRAY_TYPE_DATA));
        if (!(new->arrtype))
            malloc_error
    }
    else
        new->arrtype = NULL;
    return new;
}

int is(astNode *node, char *comp)
{
    if (strcmp(node->tree_node->node_symbol, comp) == 0)
        return 1;
    return 0;
}

PARAMS *param_lookup(PARAMS *plist, char *var)
{
    if (plist == NULL)
        return NULL;
    if (strcmp(plist->param_name, var) == 0)
        return plist;
    return param_lookup(plist->next, var);
}

int get_type_expr(astNode *ex, ID_SYMBOL_TABLE *id_st)
{
    if (ex->node_marker == ID)
    {
        ID_TABLE_ENTRY *i = st_lookup(ex->tree_node->lexeme, id_st);
        if (i == NULL)
        {
            PARAMS *p1 = param_lookup(id_st->primogenitor->in_params ,ex->tree_node->lexeme);
            PARAMS *p2 = param_lookup(id_st->primogenitor->out_params ,ex->tree_node->lexeme);
            if (p1 == NULL && p2 == NULL)
            {
                if (error_line < ex->tree_node->line)
                    printf("Semantic Error on line %d. Variable '%s' not declared.\n", ex->tree_node->line, ex->tree_node->lexeme);
                error_line = ex->tree_node->line;
                hasSemanticError = true;
            }
            else if (p1 != NULL) return p1->datatype->simple;
            else if (p2 != NULL) return p2->datatype->simple;
        }
        else
            return i->datatype->simple;
    }
    if (ex->node_marker == RNUM)
        return REAL;
    if (ex->node_marker == NUM)
        return INTEGER;
    if (ex->node_marker == TRUE || ex->node_marker == FALSE)
        return BOOLEAN;
    if (ex->node_marker ==  LE||ex->node_marker ==  GE||ex->node_marker ==  LT||ex->node_marker ==  GT||ex->node_marker ==  EQ||ex->node_marker ==  NE||0)
    {
        // printf("REE1\n");
        int t1 = get_type_expr(ex->child, id_st);
        // printf("REE2 %s\n", variables_array[t1]);
        int t2 = get_type_expr(ex->child->sibling, id_st); 
        // printf("REE3 %s\n", variables_array[t2]);
        if (t1 != t2 && t1 != 0 && t2 != 0)
        {
            if (ex->tree_node->line > error_line)
                printf("Semantic Error on line %d. Type Mismatch Error.\n",ex->tree_node->line);
            error_line = ex->tree_node->line;
            hasSemanticError = true;
        }
        else
            return BOOLEAN;
    }
    if (ex->node_marker == AND ||ex->node_marker == OR||0)
    {
        // printf("FRT1\n");
        int t1 = get_type_expr(ex->child, id_st);
        // printf("FRT2 %s\n", variables_array[t1]);
        int t2 = get_type_expr(ex->child->sibling, id_st); 
        // printf("FRT3 %s\n", variables_array[t2]);
        if (t1 != t2 && t1 != 0 && t2 != 0)
        {
            if (ex->tree_node->line > error_line)
                printf("Semantic Error on line %d. Type Mismatch Error.\n",ex->tree_node->line);
            error_line = ex->tree_node->line;
            hasSemanticError = true;
        }
        else
            return BOOLEAN;
    }
    if (ex->node_marker ==  PLUS    || (ex->node_marker ==  MINUS && ex->child->sibling != NULL)   || ex->node_marker ==  DIV     || ex->node_marker ==  MUL     ||0 )
    {
        // printf("FRT1\n");
        int t1 = get_type_expr(ex->child, id_st);
        // printf("FRT2\n");
        int t2 = get_type_expr(ex->child->sibling, id_st); 
        // printf("FRT3\n");
        if (t1 != t2 && t1 != 0 && t2 != 0)
        {
            // printf("ENTERIF\n");
            if (ex->tree_node->line > error_line)
                printf("Semantic Error on line %d. Type Mismatch Error.\n",ex->tree_node->line);
            error_line = ex->tree_node->line;
            hasSemanticError = true;
        }
        else
            return get_type_expr(ex->child, id_st);
    }
    if (ex->node_marker == MINUS && ex->child->sibling == NULL)
        return  get_type_expr(ex->child, id_st);
    if (ex->node_marker == var)
    {
        if (ex->child->sibling == NULL)     // not an array element
            return get_type_expr(ex->child, id_st);
        else                                // array element
        {
            // printf("WHYTHO2?\n");
            ID_TABLE_ENTRY *i = st_lookup(ex->child->tree_node->lexeme, id_st);
            if (i == NULL)
            {
                PARAMS *p = param_lookup(id_st->primogenitor->in_params ,ex->child->tree_node->lexeme);
                if (p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params ,ex->child->tree_node->lexeme);
                if (p == NULL)
                {
                    if (ex->child->tree_node->line > error_line)
                        printf("Semantic Error on line %d. Variable '%s' not declared.\n", ex->child->tree_node->line, ex->child->tree_node->lexeme);
                    error_line = ex->tree_node->line;
                    hasSemanticError = true;
                    return 0;
                }
                else if (p->datatype->simple != ARRAY)
                {
                    if (ex->tree_node->line > error_line)
                        printf("Semantic Error on line %d. Variable '%s' is not an array.\n", ex->tree_node->line, ex->child->tree_node->lexeme);
                    error_line = ex->tree_node->line;
                    hasSemanticError = true;
                }
                else if (get_type_expr(ex->child->sibling, id_st) != INTEGER)
                {
                    if (ex->tree_node->line > error_line)
                        printf("Semantic Error on line %d. Array index not an integer.\n", ex->tree_node->line);
                    error_line = ex->tree_node->line;
                    hasSemanticError = true;
                }
                else
                {
                    return p->datatype->arrtype->base_type;
                }
            }
            else if (i->datatype->simple != ARRAY)
            {
                if (ex->tree_node->line > error_line)
                    printf("Semantic Error on line %d. Variable '%s' is not an array.\n", ex->tree_node->line, ex->child->tree_node->lexeme);
                error_line = ex->tree_node->line;
                hasSemanticError = true;
            }
            else if (get_type_expr(ex->child->sibling, id_st) != INTEGER)
            {
                if (ex->tree_node->line > error_line)
                    printf("Semantic Error on line %d. Array index not an integer.\n", ex->tree_node->line);
                error_line = ex->tree_node->line;
                hasSemanticError = true;
            }
            else
            {
                return i->datatype->arrtype->base_type;
            }
        }
    }
    if (ex->node_marker == ARRAY)
        return ARRAY;
    // printf("BAZINGA %s %s\n", variables_array[ex->node_marker], ex->tree_node->lexeme);
    return 0;      // hopefully never
}

void traverse_the_universe(astNode *n, ID_SYMBOL_TABLE *id_st)
{
    // printf("->\t%s\n", n->tree_node->node_symbol);
    printf("st %d\n", id_st->visited);
    if (is(n, "moduleDef"))
        traverse_the_universe(n->child->sibling, id_st);
    if (is(n, "statements"))
    {
        for(astNode *temp = n->child; temp; temp = temp->sibling)
        {
            traverse_the_universe(temp, id_st);
        }
    }
    if (is(n, "declareStmt"))
    {
        astNode *temp = n->child;
        while(temp->node_marker != EPS) temp = temp->sibling;   // so temp is EPS
        astNode *type_node = temp;
        astNode *range_node = temp->sibling->child;        // at rangeArr
        for(temp = n->child; temp->node_marker != EPS; temp = temp->sibling)
        {
            ID_TABLE_ENTRY *i = st_lookup_nr(temp->tree_node->lexeme, id_st);
            if (i != NULL)
            {
                // if (error_line < temp->tree_node->line)
                    printf("Semantic Error at line %d. Variable '%s' redeclared.\n", temp->tree_node->line, temp->tree_node->lexeme);
                error_line = temp->tree_node->line;
                hasSemanticError = true;
            }
            TYPE *t = get_type(type_node);
            if (t->simple == ARRAY)
            {
                t->arrtype->base_type = range_node->sibling->node_marker;
                if (range_node->child->node_marker != NUM || range_node->child->sibling->node_marker != NUM)
                    t->arrtype->is_dynamic = true;                  // it's a dynamic array
                else
                {
                    t->arrtype->is_dynamic = false;                 // static array
                    t->arrtype->begin = atoi(range_node->child->tree_node->lexeme);
                    t->arrtype->end = atoi(range_node->child->sibling->tree_node->lexeme);
                }
            }
            ID_TABLE_ENTRY *id = create_symbol(temp, t);
            st_insert_id_entry(id, id_st);
        }
    }
    if (is(n, "assignmentStmt"))
        traverse_the_universe(n->child, id_st);
    if (is(n, "ASSIGNOP"))
    {
        // printf("AAYA\n");
        astNode *lhs = n->child;
        astNode *rhs = n->child->sibling;
        if (lhs->node_marker == ARRAY || (lhs->node_marker == var && lhs->child->sibling != NULL))
        {
            // first do a ID table recursive lookup
            ID_TABLE_ENTRY *i = st_lookup(lhs->child->tree_node->lexeme, id_st);
            PARAMS *p = NULL;
            if (i == NULL)      // then check for parameters
            {
                p = param_lookup(id_st->primogenitor->in_params ,lhs->child->tree_node->lexeme);
                if (p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params ,lhs->child->tree_node->lexeme);
            }
            // if (i == NULL && p == NULL) // finally do a recursive lookup  (no this concept is flawed)
            //     i = st_lookup(lhs->child->tree_node->lexeme, id_st);
            
            if (i == NULL && p == NULL)
            {
                if (error_line < lhs->child->tree_node->line)
                    printf("Semantic Error on line %d. Variable '%s' not declared.\n", lhs->child->tree_node->line, lhs->child->tree_node->lexeme);
                error_line = n->child->tree_node->line;
                hasSemanticError = true;
            }
            // and type must match before assignment
            if (i != NULL && (i->datatype->arrtype->base_type != get_type_expr(rhs, id_st)))
            {
                if (error_line < lhs->child->tree_node->line)
                    printf("Semantic Error on line %d. Type Mismatch Error.\n",lhs->child->tree_node->line);
                error_line = n->child->tree_node->line;
                hasSemanticError = true;
            }
            
            //printf("%d here\n", p->datatype->arrtype->base_type);
            if (p != NULL && (p->datatype->arrtype->base_type != get_type_expr(rhs, id_st)))
            {
                if (error_line < lhs->child->tree_node->line)
                    printf("Semantic Error on line %d. Type Mismatch Error.\n",lhs->child->tree_node->line);
                error_line = n->child->tree_node->line;
                hasSemanticError = true;
            }
        }
        else    // not an array
        {
            PARAMS *p = NULL;
            ID_TABLE_ENTRY *i = NULL;
            if (lhs->node_marker == var)
            {
                // printf("DOD1\n");
                p = param_lookup(id_st->primogenitor->out_params ,lhs->child->tree_node->lexeme);
                i = st_lookup(lhs->child->tree_node->lexeme, id_st);   
                // printf("DOD2\n");         
            }
            else        // not var
            {
                // printf("DOD3\n");
                p = param_lookup(id_st->primogenitor->out_params ,lhs->tree_node->lexeme);
                i = st_lookup(lhs->tree_node->lexeme, id_st);
                // hopefully we can't assign to input params
                // printf("DOD4\n");
            }
            if (p == NULL && i == NULL)
            {
                if (error_line < lhs->tree_node->line)
                    printf("Semantic Error on line %d. Varriable '%s' not declared.\n", lhs->tree_node->line, lhs->tree_node->lexeme);
                error_line = lhs->tree_node->line;
                hasSemanticError = true;
            }

            if (p == NULL && i != NULL)
            {
                // types must match before assignment
                if (i->datatype->simple != get_type_expr(rhs, id_st))
                {
                    if (error_line < lhs->tree_node->line)
                        printf("Semantic Error on line %d. Type Mismatch Error.\n",lhs->tree_node->line);
                    error_line = lhs->tree_node->line;
                    hasSemanticError = true;
                }
                else;
                    //printf("");
            }
            if (p != NULL && i == NULL)
            {
                // types must match before assignment
                if (p->datatype->simple != get_type_expr(rhs, id_st))
                {
                    if (error_line < lhs->tree_node->line)
                        printf("Semantic Error on line %d. Type Mismatch Error.\n",lhs->tree_node->line);
                    error_line = lhs->tree_node->line;
                    hasSemanticError = true;
                }
                else;
                    //printf("");
            }
            if (p != NULL && i != NULL)
            {
                ; // ask bharat how to handle this
            }
        }
    }
    if (is(n, "iterativeStmt") && is(n->child, "ID"))   // for lup
    {
        // first, the iterator must have been declared beforehand
        ID_TABLE_ENTRY *i = st_lookup(n->child->tree_node->lexeme, id_st);
        if (i == NULL)
        {
            if (error_line < n->child->tree_node->line)
                printf("Semantic Error on line %d. For loop iterator '%s' not defined before use.\n", n->child->tree_node->line, n->child->tree_node->lexeme);
            error_line = n->child->tree_node->line;
            hasSemanticError = true;
        }
        else
        {
            // then, the range may be static,
            if (is(n->child->sibling->child, "NUM") && is(n->child->sibling->child->sibling, "NUM"))
            {
                // if both are static, they must be positive and all
                if (atoi(n->child->sibling->child->tree_node->lexeme) < 0)
                {
                    if (error_line < n->child->tree_node->line)
                        printf("Semantic Error on line %d. For loop begin bound is negative.\n", n->child->tree_node->line);
                    error_line = n->child->tree_node->line;
                    hasSemanticError = true;
                }
                if (atoi(n->child->sibling->child->tree_node->lexeme) > atoi(n->child->sibling->child->sibling->tree_node->lexeme))
                {
                    if (error_line < n->child->tree_node->line)
                        printf("Semantic Error on line %d. For loop index must end after it starts.\n", n->child->tree_node->line);
                    error_line = n->child->tree_node->line;
                    hasSemanticError = true;
                }
            }
            else
            {
                if (error_line < n->child->tree_node->line)
                    printf("Semantic Error on line %d. For loop bounds must be NUMs.\n", n->child->tree_node->line);
                error_line = n->child->tree_node->line;
                hasSemanticError = true;
            }
            // create a new ID ST
            id_st->kid_st[id_st->kid_table_count++] = create_id_st(id_st);
            // and continue traversal from there
            traverse_the_universe(n->child->sibling->sibling->sibling, id_st->kid_st[id_st->kid_table_count - 1]);
        }
    }
    if (is(n, "iterativeStmt") && (1 - is(n->child, "ID")))   // while lup
    {
        // i think while loops will have more checks than this (@bharat)
        int t1 = get_type_expr(n->child, id_st);
        if (t1 != BOOLEAN)
        {
            if (error_line < n->child->tree_node->line)
                    printf("Semantic Error on line %d. While condition ain't a boolean.\n", n->child->tree_node->line);
                error_line = n->child->tree_node->line;
                hasSemanticError = true;
        }
        // create a new ID ST
        id_st->kid_st[id_st->kid_table_count++] = create_id_st(id_st);
        // and continue traversal from there
        traverse_the_universe(n->child->sibling->sibling, id_st->kid_st[id_st->kid_table_count - 1]);
    }
    if (is(n, "ioStmt"))
    {
        if (n->child->node_marker == GET_VALUE)
        {
            // it's a get_value, so must have been declared beforehand
            PARAMS *p = param_lookup(id_st->primogenitor->out_params ,n->child->child->tree_node->lexeme);
            ID_TABLE_ENTRY *i1 = st_lookup(n->child->child->tree_node->lexeme, id_st);
            if (i1 == NULL && p == NULL)
            {
                if (error_line < n->child->tree_node->line)
                    printf("Semantic Error on line %d. Variable '%s' not declared.\n", n->child->tree_node->line, n->child->child->tree_node->lexeme);
                error_line = n->child->tree_node->line;
                hasSemanticError = true;
            }
        }
        else                // it's a printOp
        {
            if (n->child->child->node_marker == ID || n->child->child->node_marker == var)     // only if it's an ID (or an array)
            {
                ID_TABLE_ENTRY *i1 = st_lookup(n->child->child->child->tree_node->lexeme, id_st);
                PARAMS *p1 = param_lookup(id_st->primogenitor->in_params ,n->child->child->child->tree_node->lexeme);
                PARAMS *p2 = param_lookup(id_st->primogenitor->out_params ,n->child->child->child->tree_node->lexeme);
                if (i1 == NULL && p1 == NULL && p2 == NULL)
                {
                    printf("Semantic Error on line %d. Variable '%s' not declared.\n", n->child->child->child->tree_node->line, n->child->child->child->tree_node->lexeme);
                    hasSemanticError = true;
                }
            }
            else
                ;       // do nothing 
        }
    }
    if (is(n, "conditionalStmt"))
    {
        // the switch must have been declared beforehand
        ID_TABLE_ENTRY *i = st_lookup(n->child->tree_node->lexeme, id_st);
        if (i == NULL)
        {
            if (error_line < n->child->tree_node->line)
                printf("Semantic Error on line %d. Switch '%s' not defined before use.\n", n->child->tree_node->line, n->child->tree_node->lexeme);
            error_line = n->child->tree_node->line;
            hasSemanticError = true;
        }
        else
        {
            // create a new ID ST
            id_st->kid_st[id_st->kid_table_count++] = create_id_st(id_st);
            // and continue traversal from there
            traverse_the_universe(n->child->sibling->sibling, id_st->kid_st[id_st->kid_table_count - 1]);
        }
    }
    if (is(n, "caseStmts"))
        for (astNode *temp = n->child; temp; temp = temp->sibling)
            traverse_the_universe(temp, id_st);
    if (is(n, "caseStmt"))
        traverse_the_universe(n->child->sibling, id_st);
    if (is(n, "moduleReuseStmt") && n->child->node_marker == EPS)
    {
        FUNC_TABLE_ENTRY *f = global_st_lookup(n->child->sibling->tree_node->lexeme, id_st->primogenitor->procreator);
        if (f == NULL)
        {
            // printf("Semantic Error at line %d. Function %s not defined before use.\n", n->child->sibling->tree_node->line, n->child->sibling->tree_node->lexeme);
            hasSemanticError = true;
        }
        else
        {
             PARAMS *p = f->in_params;
            for(astNode *temp = n->child->sibling->sibling->child; p != NULL && temp != NULL; p = p->next, temp = temp->sibling)
                if (get_type_expr(temp, id_st) != p->datatype->simple)
                {
                    // printf("Semantic Error at line %d. Wrong type given to function input.\n", n->child->sibling->sibling->child->tree_node->line);
                    hasSemanticError = true;
                }
        }
    }
    if (is(n, "moduleReuseStmt") && n->child->node_marker != EPS)
    {
        FUNC_TABLE_ENTRY *f = global_st_lookup(n->child->sibling->tree_node->lexeme, id_st->primogenitor->procreator);
        if (f == NULL)
        {
            if (error_line < n->child->sibling->tree_node->line)
                // printf("Semantic Error at line %d. Function %s not defined before use.\n", n->child->sibling->tree_node->line, n->child->sibling->tree_node->lexeme);
            error_line = n->child->sibling->tree_node->line;
            hasSemanticError = true;
        }
        else
        {
            PARAMS *p = f->in_params;
            // check for input parameters
            for(astNode *temp = n->child->sibling->sibling->child; p != NULL && temp != NULL; p = p->next, temp = temp->sibling)
                if (get_type_expr(temp, id_st) != p->datatype->simple)
                {
                    // printf("Semantic Error at line %d. Wrong type given to function input.\n", n->child->sibling->sibling->child->tree_node->line);
                    hasSemanticError = true;
                }
            // and output parameters
            p = f->out_params;
            for(astNode *temp = n->child->child; p != NULL && temp != NULL; p = p->next, temp = temp->sibling)
                if (get_type_expr(temp, id_st) != p->datatype->simple)
                {
                    // printf("Semantic Error at line %d. Wrong type given to function output.\n", n->child->child->tree_node->line);
                    hasSemanticError = true;
                }
        }
    }
    return;
}

void lite()
{
    return;
}

// traverse the ast, fill the GST (while performing some checks)
void traverse_the_multiverse(astNode *n, GST *st)
{
    // printf("aaya1%s\n", n->tree_node->node_symbol);
    if (is(n,"program"))
    {
        astNode *d = NULL;
        for(astNode *temp = n->child; temp; temp = temp->sibling)
        {
            if (is(temp, "driverModule"))
            {
                d = temp;       // run driver at last
                continue;
            }
            traverse_the_multiverse(temp,st);
        }
        traverse_the_multiverse(d, st);

    }

    if (is(n, "moduleDeclarations"))
        for (astNode *temp = n->child; temp; temp = temp->sibling)
            // st_insert_func_entry(create_function(temp, NULL, NULL, NULL), st);
            lite();
    /*
    if (is(n, "otherModules") && n->sibling != NULL)
    {
        for (astNode *m = n->child; m; m = m->sibling)
        {
            PARAMS *p1 = create_param(m->child->sibling->child);
            PARAMS *p2 = create_param(m->child->sibling->sibling->child);
            printf("aaya2\n");
            ID_SYMBOL_TABLE *id_st = create_id_st(NULL);
            FUNC_TABLE_ENTRY *f = create_function(m->child, p1, p2, id_st);
            st_insert_func_entry(f, st);
            traverse_the_universe(m->child->sibling->sibling->sibling, id_st);
            f->activation_record_size = current_offset;
            // printf("ALA\t%d", current_offset);
        }
    }
    */
    if (is(n, "driverModule"))
    {
        ID_SYMBOL_TABLE *id_st = create_id_st(NULL);
        printf("visited in st: %d\n", id_st->visited);
        FUNC_TABLE_ENTRY *fnew = create_function(NULL, NULL, NULL, id_st);
        st_insert_func_entry(fnew, st);
        // printf("mil\n");
        traverse_the_universe(n->child, id_st);
        fnew->activation_record_size = current_offset;
        // printf("ALA\t%d", current_offset);
        // printf("gaya\n");
    }
    if (is(n, "otherModules"))// && n->sibling == NULL)
    {
        for (astNode *m = n->child; m; m = m->sibling)
        {
            PARAMS *p1 = create_param(m->child->sibling->child);
            // printf("aaya2\n");
            PARAMS *p2 = NULL;
            if (m->child->sibling->sibling->child->node_marker == EPS)  // no output
                p2 = NULL;
            else
                p2 = create_param(m->child->sibling->sibling->child);
            ID_SYMBOL_TABLE *id_st = create_id_st(NULL);
            FUNC_TABLE_ENTRY *f = create_function(m->child, p1, p2, id_st);
            st_insert_func_entry(f, st);
            traverse_the_universe(m->child->sibling->sibling->sibling, id_st);
            f->activation_record_size = current_offset;
        }
    }
    if (is(n, "EPS"))
        return;         // bliss

    return;
}

PARAMS *create_param(astNode *plist)
{
    PARAMS *new = (PARAMS *) malloc(sizeof(PARAMS));
    if (!new)
        malloc_error
    new->param_name = plist->child->tree_node->lexeme;
    new->datatype = get_type(plist->child);
    // new->offset will be filled later, no point in initializing
    TYPE *t = new->datatype;
    astNode *temp = plist->child->sibling->child;       // on rangeArr
    if (t->simple == ARRAY)
    {
        t->arrtype->base_type = temp->sibling->node_marker;
        if (temp->child->node_marker != NUM || temp->child->sibling->node_marker != NUM)
            t->arrtype->is_dynamic = true;                  // it's a dynamic array
        else
        {
            t->arrtype->is_dynamic = false;                 // static array
            t->arrtype->begin = atoi(temp->child->tree_node->lexeme);
            t->arrtype->end = atoi(temp->child->sibling->tree_node->lexeme);
        }
        t->arrtype->begin_offset = 0;            // don't fill param 
        t->arrtype->end_offset   = 0;            // offets now
    }
    new->is_assigned = false;
    if (plist->sibling)
        new->next = create_param(plist->sibling);
    else
        new->next = NULL;
    return new;
}

// fill offsets into a linked list of parameters
void fill_param_offsets(PARAMS *p, unsigned int off)
{
    unsigned int offset = off;                               // initialize offset
    for (PARAMS *pt = p; pt != NULL; pt = pt->next)         // traverse the parameters, 
    {                                                      // and give each one an
        pt->offset = offset++;                            // offset, and
        if (pt->datatype->simple == ARRAY)               // if it's an array,
        {                                               // take its type,
            ARRAY_TYPE_DATA *a = pt->datatype->arrtype;// and 
            a->begin_offset = offset++;               // give offsets to 
            a->end_offset = offset++;                // begin and end too
        }   
    }
    return;
}

// we initialize our global symbol table
GST* create_global_st()
{
    GST *st = (GST *) malloc(sizeof(GST));
    if (!st)
        malloc_error
    for (int iterator = 0; iterator < GST_SIZE; ++iterator)
        st->func_table[iterator] = NULL;                        // no functions in the table
    st->total_functions = 0;
    return st;
}

// now, we insert function table entry to our global ST
// The corresponding structure 'sym' should have been populated earlier.
void st_insert_func_entry(FUNC_TABLE_ENTRY *f, GST *st)
{
    int key = st_hash(f->func_name);          // calculate the hash to find out where to insert this entry
    if (st->func_table[key] == NULL)      // if there is no collision,
        st->func_table[key] = f;        // just add it
    else                                // collision resolved by
    {
        FUNC_TABLE_ENTRY *temp = st->func_table[key];       // going to the end of list
        while (temp->next)
            temp = temp->next;
        temp->next = f;                               // and adding it there
    }
    st->total_functions += 1;
    f->procreator = st;
    current_offset = 1;                 // set the correct offset (just in case, not needed)
    fill_param_offsets(f->in_params, IN_PARAM_OFFSET);                      // and fill in the input and 
    fill_param_offsets(f->out_params, OUT_PARAM_OFFSET);                    // output parameter offsets
    return;
}

void v_print_params(PARAMS *pl, char *fn)
{
    PARAMS *temp = pl;
    while(temp)
    {
        char *scope = fn;                                       // first, calculate
        unsigned int width = get_width(temp->datatype);             // all the things
        char *is_array = temp->datatype->simple == ARRAY ?      // that we are
                                "yes" : "no";                   // required to print
        char *sd = temp->datatype->simple != ARRAY ?
                            "---" :  temp->datatype->arrtype->is_dynamic == true ?
                                                            "dynamic" : "static";
        unsigned int type = temp->datatype->arrtype == NULL ?
                    temp->datatype->simple : temp->datatype->arrtype->base_type;
        unsigned int offset = temp->offset;
        printf("%15s %15s %10u %10s %15s %10s %10u %10u\n",
                temp->param_name,
                scope,
                width,
                is_array,
                sd,
                variables_array[type],
                offset,
                0);
	    temp = temp->next;
    }
    return;
}

// print the ID ST as per requirements
void v_id_st_print(ID_SYMBOL_TABLE *st, unsigned int depth)
{
    // printf("H2\n");
    if (st == NULL)                                                 // for a null table,
        return;                                                     // don't bother
    for(int i = 0; i < ST_ID_SIZE; i++)                             // else, traverse
    {
        ID_TABLE_ENTRY *temp = st->id_table[i];                     // for each id entry,
        while(temp)
        {
            char *scope = st->primogenitor->func_name;              // first, calculate
            unsigned int width = temp->width;                           // all the things
            char *is_array = temp->datatype->simple == ARRAY ?      // that we are
                                    "yes" : "no";                   // required to print
            char *sd = temp->datatype->simple != ARRAY ?
                                "---" :  temp->datatype->arrtype->is_dynamic == true ?
                                                                "dynamic" : "static";
            unsigned int type = temp->datatype->arrtype == NULL ?
                        temp->datatype->simple : temp->datatype->arrtype->base_type;
            unsigned int offset = temp->offset;
            printf("%15s %15s %10u %10s %15s %10s %10u %10u\n",
                    temp->lexeme,
                    scope,
                    width,
                    is_array,
                    sd,
                    variables_array[type],
                    offset,
                    depth);
            temp = temp->next;
        }
    }
    for (int j = 0; j < st->kid_table_count; ++j)                   // finally, print all kid
        v_id_st_print(st->kid_st[j], 1 + depth);                                 // tables with depth
    return;
}

// print the GST as per requirements
void v_gst_print(GST *st)
{
    // first, print the header
    printf("Symbol Table:\n");
    printf(
            "%15s %15s %10s %10s %15s %10s %10s %10s\n",
            "variable_name",
            "scope (module)",
            "width",
            "isArray",
            "static/dynamic",
            "type",
            "offset",
            "nesting"
            );
    // and finally, traverse over all the functions,
    for(int i = 0; i < GST_SIZE; i++)
    {
        FUNC_TABLE_ENTRY *temp = st->func_table[i];
        while(temp)
        {
            // print their parameters,
            v_print_params(temp->in_params, temp->func_name);
            v_print_params(temp->out_params, temp->func_name);
            // and print their local ID ST with depth 1
            v_id_st_print(temp->local_id_table, 1);
            temp = temp->next;
        }
    }
    return;
}


// helper function to print the global symbol table
void gst_print(GST *st)
{
    printf("\nPrinting GST with %d function(s):\n", st->total_functions);
    for(int i = 0; i < GST_SIZE; i++)
    {
        FUNC_TABLE_ENTRY *temp = st->func_table[i];
        while(temp)
        {
            printf("\n\tPrinting Function Table for '%s':\n", temp->func_name);
	        print_params(temp->in_params);	            // defined below
	        print_params(temp->out_params);
            id_st_print(temp->local_id_table);
            temp = temp->next;
        }
    }
    return;
}

// helper function to print the parameter lists of global symbol table
void print_params(PARAMS *list)
{
    PARAMS *temp = list;
    printf("\tParam(s) = ");
    while(temp)
    {
        char *pn = temp->param_name;
        char *ty = show_type(temp->datatype);
        printf("%s : %s (%u), ",pn, ty, temp->offset);
	    temp = temp->next;
    }
    putchar('\n');
    return;
}

// lookup the global symbol table for function, and return the entry if found
FUNC_TABLE_ENTRY *global_st_lookup(char *name, GST *st)
{
    // first, compute the key where the variable would be stored in GST
    int key = st_hash(name);
    FUNC_TABLE_ENTRY *temp = st->func_table[key];
    while(temp)
    {
        if(strcmp(temp->func_name, name) == 0)   // entry found
            return temp;
        temp = temp->next;
    }
    return NULL;  // function with the specified name not defined (no need to recurse)
}

// populating a global symbol table entry, will be created when we define a function
FUNC_TABLE_ENTRY *create_function(astNode *node, PARAMS *inp_par, PARAMS *out_par, ID_SYMBOL_TABLE *st)
{
    // printf("IN2\n");
    FUNC_TABLE_ENTRY *new = (FUNC_TABLE_ENTRY *) malloc(sizeof(FUNC_TABLE_ENTRY));
    if (!new)
        malloc_error
    if (node == NULL)       // for the driver function
    {
        new->func_name = "driverModule";
        new->in_params = NULL;
        new->out_params = NULL;
        new->local_id_table = st;
        if (st != NULL)
            st->primogenitor = new;
        new->next = NULL;
        new->is_declared = 1;
    }
    else
    {
        assert(strcmp(node->tree_node->token_name, "ID") == 0);             //this should have ID info
        new->func_name = node->tree_node->lexeme;
        new->in_params = inp_par;
        new->out_params = out_par;
        new->width = get_total_width(st);
        new->local_id_table = st;
        if (st != NULL)
            st->primogenitor = new;
        new->next = NULL;
        new->is_declared = 0;
    }
    return new;
}

int get_total_width(ID_SYMBOL_TABLE *st)
{
    if(st == NULL)	// No symbol table of identifiers <=> no local variables of function
	return 0;

    int total = 0;
    ID_TABLE_ENTRY *temp = NULL;
    for(int i = 0; i < ST_ID_SIZE; i++)	// summing up the widths of each identifier in the current ST.
    {
        temp = st->id_table[i];
        while(temp)
	{
	    total += temp->width;
    	    temp = temp->next;
        }
    }

    for(int j = 0; j < st->kid_table_count; j++)
	total += get_total_width(st->kid_st[j]);

    return total;
}

// make assember
// 

#include "code_gen.h"

VARS vars;

int array_available_addr = 0;
int label_count = 0;
char* registers_array[] = {"rdi", "rsi", "rdx", "rcx", "r8",
                    "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
// change this after satvik implements
//refer to temp_funccall.asm by @bharat
//int stack_count = 0;


char* generate_label(void)
{
    char* label = (char*) malloc((sizeof(100*sizeof(char))));
    sprintf(label, "label%d", label_count);
    label_count++;
    return label;
}

char* generate_func_label(char* func_name)
{
    char* label = (char*) malloc((sizeof(100*sizeof(char))));
    sprintf(label, "%s:", func_name);
    return label;
}
void print_return(FILE* fp)
{

    fprintf(fp, "main_end:\n");
    fprintf(fp, "mov rsp, rbp\n");
    fprintf(fp, "pop rbp\n");
    fprintf(fp, "mov rax, 0\n");
    fprintf(fp, "ret\n");
}

void print_externs(FILE* fp)
{
    fprintf(fp, "global main\n");
    fprintf(fp, "extern printf\n");
    fprintf(fp, "extern scanf\n");
    fprintf(fp, "extern puts\n");
    fprintf(fp, "extern exit\n");

    fprintf(fp, "\nsection  .text\n\n");

    return;
}

void print_data_section(FILE* fp)
{
    fprintf(fp, "section .data\n\n");

    fprintf(fp, "int_inMsg    db        \"Enter an integer value\" , 10, 0\n"); 
    fprintf(fp, "real_inMsg   db        \"Enter a real value\", 10, 0\n");
    fprintf(fp, "bool_inMsg   db        \"Enter a boolean value\", 10, 0\n");
    fprintf(fp, "arr_inMsg    db        \"Enter %%d elements of %%s type for array range %%d to %%d\", 10, 0\n");
    fprintf(fp, "intFormat     db        \"%%d\", 0\n");
    fprintf(fp, "type_int      db        \"integer\", 0\n");
    fprintf(fp, "type_real     db        \"real\", 0\n");
    fprintf(fp, "type_bool     db        \"boolean\", 0\n");    
    fprintf(fp, "intFormat_in  db        \"%%d\", 0\n");
    fprintf(fp, "intFormat_out db        \"%%d \", 0\n");
    fprintf(fp, "realFormat_in db        \"%%lf\", 10, 0\n");
    fprintf(fp, "realFormat_out db       \"%%lf\", 0\n");
    fprintf(fp, "strFormat_in   db       \"%%s\", 0\n");
    fprintf(fp, "strFormat_out   db       \"%%s\", 10, 0\n");
    fprintf(fp, "true_label     db        \"true \", 0\n");
    fprintf(fp, "false_label     db        \"false \", 0\n");
    fprintf(fp, "arr_outMsg   db        \"Printing array: \", 0\n");
    fprintf(fp, "errorMsg1    db        \"RUN TIME ERROR: End index %%d of Array less than start index %%d at line %%d. Aborting\", 10, 0\n");
    fprintf(fp, "errorMsg2    db        \"RUN TIME ERROR: Index %%d out of bounds %%d and %%d at line %%d. Aborting.\", 10, 0\n");
    fprintf(fp, "new_line       db       10, 0\n");
    fprintf(fp, "var1         dd        3\n");
    fprintf(fp, "var2         dd        6\n");
    fprintf(fp, "array_available_addr   dq   0\n");
    fprintf(fp, "\n\n\n");

    return;
}

void print_bss_section(FILE* fp, VARS vars)
{
    fprintf(fp, "\t\tsection .bss\n\n");

    char buff[100];
    for(int i = 0; i < vars.num_byte_vars; i++)
    {
        sprintf(buff, "varb%d:   resb    1\n", i + 1);
        fprintf(fp, "%s\n", buff);
    }

    for(int i = 0; i < vars.num_double_vars; i++)
    {
        sprintf(buff, "vard%d:   resd    1\n", i + 1);
        fprintf(fp, "%s\n", buff);
    }

    for(int i = 0; i < vars.num_quad_words; i++)
    {
        sprintf(buff, "varq%d:   resq    1\n", i + 1);
        fprintf(fp, "%s\n", buff);
    }

    for(int i = 0; i < vars.num_word_vars; i++)
    {
        sprintf(buff, "varw%d:   resw    1\n", i + 1);
        fprintf(fp, "%s\n", buff);
    }

    fprintf(fp, "int_array:         resd        100\n");
    fprintf(fp, "real_array:        resq        100\n");
    fprintf(fp, "bool_array:        resb        100\n");

    fprintf(fp, "array_buffer:      resq        1000\n");

    fprintf(fp, "\n\n");
}

void initialise_file(FILE* fp)
{
    print_data_section(fp);

    // for one double var
    vars.num_double_vars++;
    print_bss_section(fp, vars);
    print_externs(fp);
    return;   
}

void bound_check(FILE* fp, int start_offset, int end_offset, int index, int line)
{
    char* error_label = generate_label();
    char* exit_label = generate_label();
    fprintf(fp, "; bound checking\n");
    fprintf(fp, "\tpush r13\n");
    fprintf(fp, "\tpush r14\n");
    fprintf(fp, "\txor r13, r13\n");
    fprintf(fp, "\txor r14, r14\n");
    fprintf(fp, "\tmov r13d, [rbp - %d]\n", start_offset * 8);
    fprintf(fp, "\tmov r14d, [rbp - %d]\n", end_offset * 8);
    fprintf(fp, "\tcmp r13d, %d\n", index);
    fprintf(fp, "\tjg %s\n", error_label);
    fprintf(fp, "\tcmp r14d, %d\n", index);
    fprintf(fp, "\tjl %s\n", error_label);
    fprintf(fp, "\tjmp %s\n", exit_label);

    fprintf(fp, "\t%s: \n", error_label);
    fprintf(fp, "\tlea rdi, [errorMsg2]\n");
    // "errorMsg2    db        \"RUN TIME ERROR: Index %%d out of
    // bounds %%d and %%d at line %%d. Aborting.\"
    fprintf(fp, "\tmov rsi, %d\n", index);
    fprintf(fp, "\tmov rdx,  r13\n");
    fprintf(fp, "\txor rcx, rcx\n");
    fprintf(fp, "\tmov rcx, r14\n");
    fprintf(fp, "\tmov r8, %d\n", line);
    fprintf(fp, "\txor rax, rax\n");
    fprintf(fp, "\tcall printf\n");
    fprintf(fp, "\tjmp main_end\n");
    fprintf(fp, "%s:\n", exit_label);
}

// for A[k] kind
void bound_check_dynamic(FILE* fp, int start_offset, int end_offset, int index_offset, int line)
{
    char* error_label = generate_label();
    char* exit_label = generate_label();
    fprintf(fp, "; bound checking\n");
    fprintf(fp, "\tpush r13\n");
    fprintf(fp, "\tpush r14\n");
    fprintf(fp, "\txor r13, r13\n");
    fprintf(fp, "\txor r14, r14\n");
    fprintf(fp, "\txor r15, r15\n");
    fprintf(fp, "\tmov r13d, [rbp - %d]\n", start_offset * 8);
    fprintf(fp, "\tmov r14d, [rbp - %d]\n", end_offset * 8);
    fprintf(fp, "\tmov r15d, [rbp - %d]\n", index_offset * 8);
    fprintf(fp, "\tcmp r13d, r15d\n");
    fprintf(fp, "\tjg %s\n", error_label);
    fprintf(fp, "\tcmp r14d, r15d\n");
    fprintf(fp, "\tjl %s\n", error_label);
    fprintf(fp, "\tjmp %s\n", exit_label);

    fprintf(fp, "\t%s: \n", error_label);
    fprintf(fp, "\tlea rdi, [errorMsg2]\n");
    // "errorMsg2    db        \"RUN TIME ERROR: Index %%d out of
    // bounds %%d and %%d at line %%d. Aborting.\"
    fprintf(fp, "\tmov rsi, r15\n");
    fprintf(fp, "\tmov rdx,  r13\n");
    fprintf(fp, "\txor rcx, rcx\n");
    fprintf(fp, "\tmov rcx, r14\n");
    fprintf(fp, "\tmov r8, %d\n", line);
    fprintf(fp, "\txor rax, rax\n");
    fprintf(fp, "\tcall printf\n");
    fprintf(fp, "\tjmp main_end\n");
    fprintf(fp, "%s:\n", exit_label);
}

void take_input(FILE* fp, int type, int offset)
{
    // for int
    int temp = offset * 8;
    if(type == INTEGER || type == BOOLEAN)
    {
        fprintf(fp, "\tmov rdi, intFormat_in\n");
        fprintf(fp, "\tlea rsi, [rbp - %d]\n", temp);
        fprintf(fp, "\tcall scanf\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "\tmov rdi, realFormat_in\n");
        fprintf(fp, "\tlea rsi, [rbp - %d]\n", temp);
        fprintf(fp, "\tcall scanf\n");
    }
    
}



void prompt_user(FILE* fp, int type)
{
    // fprintf(fp, "push rbp\n");

    if (type == INTEGER)
        fprintf(fp, "\tmov rdi, int_inMsg\n");
    else if (type == BOOLEAN)
        fprintf(fp, "\tmov rdi, bool_inMsg\n");
    else if (type == REAL)
        fprintf(fp, "\tmov rdi, real_inMsg\n");
    else
    {
        printf("ERROR\n");
        exit(1);
    }
    
    fprintf(fp, "\tcall printf\n");
    // fprintf(fp, "pop rbp\n\n");
}


void print_id(FILE* fp, int type, int offset)
{
    // for int
    int temp = offset * 8;
    if(type == INTEGER)
    {
        fprintf(fp, "\tmov rdi, intFormat_out\n");
        fprintf(fp, "\txor rsi, rsi\n");
        fprintf(fp, "\tmov esi, [rbp - %d]\n", temp);
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "\tmov rdi, realFormat_out\n");
        fprintf(fp, "\txor rsi, rsi\n");
        fprintf(fp, "\tmov esi, [rbp - %d]\n", temp);
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n\n");
    }

    else if(type == BOOLEAN)
    {
        char* f_label = generate_label();
        char* p_label = generate_label();
        fprintf(fp, "\tlea rdi, [strFormat_in]\n");
        fprintf(fp, "\tmov sil, [rbp - %d]\n\n", temp);
        fprintf(fp, "\tcmp sil, 0\n");
        fprintf(fp, "\tjz %s\n", f_label);
        fprintf(fp, "\tlea rsi, [true_label]\n");
        fprintf(fp, "\tjmp %s\n\n", p_label);
        fprintf(fp, "%s: \n", f_label);
        fprintf(fp, "\tlea rsi, [false_label]\n\n");
        fprintf(fp, "%s: \n", p_label);
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n");
        fprintf(fp, "\n\n");
    }
    
}

void print_array_id(FILE* fp, int type, int base_offset, int start_offset, int index)
{
    // for int
    fprintf(fp, "\txor rsi, rsi\n");
    fprintf(fp, "\tmov r13, [rbp - %d]\n", base_offset * 8);
    fprintf(fp, "\txor r14, r14\n");
    fprintf(fp, "\txor r15, r15\n");
    fprintf(fp, "\tmov r14d, %d\n", index);
    fprintf(fp, "\tmov r15d, [rbp - %d]\n", start_offset * 8);
    fprintf(fp, "\tsub r14d, r15d\n");
    fprintf(fp, "\tmov esi, [r13 + r14 * 8]\n");

    if(type == INTEGER)
    {
        fprintf(fp, "\tmov rdi, intFormat_out\n");
        
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n\n");
    }

    else if(type == REAL)
    {
        printf("Real not handled\n");
        exit(1);
    }

    else if(type == BOOLEAN)
    {
        char* f_label = generate_label();
        char* p_label = generate_label();
        fprintf(fp, "\tlea rdi, [strFormat_in]\n");
        fprintf(fp, "\tcmp esi, 0\n");
        fprintf(fp, "\tjz %s\n", f_label);
        fprintf(fp, "\tlea rsi, [true_label]\n");
        fprintf(fp, "\tjmp %s\n\n", p_label);
        fprintf(fp, "%s: \n", f_label);
        fprintf(fp, "\tlea rsi, [false_label]\n\n");
        fprintf(fp, "%s: \n", p_label);
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n");
        fprintf(fp, "\n\n");
    }
    
}

void print_array_id_dynamic(FILE* fp, int type, int base_offset, int start_offset, int index_offset)
{
    // for int

    fprintf(fp, "\txor rsi, rsi\n");
    fprintf(fp, "\tmov r13, [rbp - %d]\n", base_offset * 8);
    fprintf(fp, "\txor r14, r14\n");
    fprintf(fp, "\txor r15, r15\n");
    fprintf(fp, "\tmov r14d, [rbp - %d]\n", index_offset * 8);
    fprintf(fp, "\tmov r15d, [rbp - %d]\n", start_offset * 8);
    fprintf(fp, "\tsub r14d, r15d\n");
    fprintf(fp, "\tmov esi, [r13 + r14 * 8]\n");

    if(type == INTEGER)
    {
        fprintf(fp, "\tmov rdi, intFormat_out\n");
        
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n\n");
    }

    else if(type == REAL)
    {
        printf("Real not handled\n");
        exit(1);
    }

    else if(type == BOOLEAN)
    {
        char* f_label = generate_label();
        char* p_label = generate_label();
        fprintf(fp, "\tlea rdi, [strFormat_in]\n");
        fprintf(fp, "\tcmp esi, 0\n");
        fprintf(fp, "\tjz %s\n", f_label);
        fprintf(fp, "\tlea rsi, [true_label]\n");
        fprintf(fp, "\tjmp %s\n\n", p_label);
        fprintf(fp, "%s: \n", f_label);
        fprintf(fp, "\tlea rsi, [false_label]\n\n");
        fprintf(fp, "%s: \n", p_label);
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n");
        fprintf(fp, "\n\n");
    }
    
}

// type is enum in this case
void ask_for_array(FILE* fp, int base_offset, int lower_offset, int upper_offset, int type)
{
    printf("%d %d %d\n", base_offset, lower_offset, upper_offset);
    // fprintf(fp, "push rbp\n");
    fprintf(fp, "; prompts user for input\n");
    fprintf(fp, "\tmov ecx, [rbp - %d]\n", lower_offset);
    fprintf(fp, "\tmov r8d, [rbp - %d]\n", upper_offset);
    fprintf(fp, "\tmov esi, r8d\n");
    fprintf(fp, "\tsub esi, ecx\n");
    fprintf(fp, "\tinc esi\n");
    fprintf(fp, "\tmov rdi, arr_inMsg\n");

    if (type == INTEGER)
        fprintf(fp, "mov rdx, type_int\n");
    else if (type == REAL)
        fprintf(fp, "mov rdx, type_real\n");
    else if (type == BOOLEAN)
        fprintf(fp, "mov rdx, type_bool\n");
    else
    {
        printf("Error in ask for array function\n");
        exit(1);
    }
    fprintf(fp, "\txor rcx, rcx\n");
    fprintf(fp, "\txor r8, r8\n");
    fprintf(fp, "\tmov ecx, [rbp - %d]\n", lower_offset);
    fprintf(fp, "\tmov r8d, [rbp - %d]\n", upper_offset);
    fprintf(fp, "\tcall printf\n\n");

    char* array_input_label  = generate_label();
    fprintf(fp, "\t; stores the count\n\n");
    fprintf(fp, "\txor r12, r12\n");
    fprintf(fp, "\txor r13, r13\n");
    fprintf(fp, "\tmov r12d, [rbp - %d]\n", upper_offset);
    fprintf(fp, "\tmov r13d, [rbp - %d]\n", lower_offset);
    fprintf(fp, "\tsub r12d, r13d\n");
    fprintf(fp, "\tinc r12d\n");
    fprintf(fp, "\txor r13, r13\n\n");  
    fprintf(fp, "\t%s:\n", array_input_label);

    if(type == INTEGER)
    {
        fprintf(fp, "lea rdi, [intFormat_in]\n");
       
    }

    else if(type == REAL)
    {
        fprintf(fp, "lea rdi, [realFormat_in]\n");
    }

    else if(type == BOOLEAN)
    {
        fprintf(fp, "lea rdi, [intFormat_in]\n");
    }

    else
    {
        printf("ERROR in ask for array\n");
        exit(1);
    }
    fprintf(fp, "\txor r14, r14\n");
    fprintf(fp, "\tmov r14d, [rbp - %d]\n", base_offset);
    fprintf(fp, "\tlea rsi, [r14 + r13 * 8]\n");
    fprintf(fp, "\tcall scanf\n\n");

    fprintf(fp, "\tinc r13d\n");
    fprintf(fp, "\tcmp r13d, r12d\n");
    fprintf(fp, "\tjne %s\n", array_input_label);
    // fprintf(fp, "pop rbp\n");
    fprintf(fp, "\n\n");


}

// type is enum in this case
void print_array(FILE* fp, int base_offset, int lower_offset, int upper_offset, int type)
{
    
    // fprintf(fp, "push rbp\n");

    fprintf(fp, "; printing array\n");
    fprintf(fp, "lea rdi, [arr_outMsg]\n");
    fprintf(fp, "call printf\n");

    char* array_output_label = generate_label();
    fprintf(fp, "; stores the count\n\n");
    fprintf(fp, "xor r12, r12\n");
    fprintf(fp, "xor r13, r13\n");
    fprintf(fp, "mov r12d, [rbp - %d]\n", upper_offset);
    fprintf(fp, "mov r13d, [rbp - %d]\n", lower_offset);
    fprintf(fp, "sub r12d, r13d\n");
    fprintf(fp, "inc r12d\n");
    fprintf(fp, "xor r13, r13\n\n");  
    fprintf(fp, "%s:\n", array_output_label);

    if(type == INTEGER)
    {
        fprintf(fp, "\tlea rdi, [intFormat_out]\n");
        fprintf(fp, "\txor r14, r14\n");
        fprintf(fp, "\tmov r14d, [rbp - %d]\n", base_offset);
        fprintf(fp, "\tmov rsi, [r14 + r13 * 8]\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "lea rdi, [realFormat_out]\n");
        fprintf(fp, "\txor r14, r14\n");
        fprintf(fp, "\tmov r14d, [rbp - %d]\n", base_offset);
        fprintf(fp, "\tlea rsi, [r14 + r13 * 8]\n");
        
    }

    else if(type == BOOLEAN)
    {
        char* f_label = generate_label();
        char* p_label = generate_label();
        fprintf(fp, "\tlea rdi, [strFormat_in]\n");
        fprintf(fp, "\txor r14, r14\n");
        fprintf(fp, "\tmov r14d, [rbp - %d]\n", base_offset);
        fprintf(fp, "\tmov rsi, [r14 + r13 * 8]\n");

        fprintf(fp, "\tcmp sil, 0\n");
        fprintf(fp, "\tjz %s\n", f_label);
        fprintf(fp, "\tlea rsi, [true_label]\n");
        fprintf(fp, "\tjmp %s\n\n", p_label);
        fprintf(fp, "%s: \n", f_label);
        fprintf(fp, "\tlea rsi, [false_label]\n\n");

        fprintf(fp, "%s: \n", p_label);

    }

    else
    {
        printf("ERROR in ask for array\n");
        exit(1);
    }
    
    fprintf(fp, "\tcall printf\n\n");
    fprintf(fp, "\tinc r13d\n");
    fprintf(fp, "\tcmp r13d, r12d\n");
    fprintf(fp, "\tjne %s\n", array_output_label);
    fprintf(fp, "\tlea rdi, [new_line]\n");
    fprintf(fp, "\tcall printf\n");

    // fprintf(fp, "pop rbp\n");
    fprintf(fp, "\n\n");


}

// evaluates the rhs and stores the result in RCX
void evaluate_expr(astNode *ex, ID_SYMBOL_TABLE *id_st, FILE *fp)
{
    if(ex->node_marker == var)
    {
        evaluate_expr(ex->child, id_st, fp);
    }
    if (ex->node_marker == ID)
    {
        printf("here\n");
        printf("var: %s\n", ex->tree_node->lexeme);
        ID_TABLE_ENTRY *i = st_lookup(ex->tree_node->lexeme, id_st);
        printf("here2\n");
        if (i == NULL)
        {
            printf("ayush\n");
            PARAMS *p = param_lookup(id_st->primogenitor->in_params ,ex->tree_node->lexeme);
            if(p == NULL)
                p = param_lookup(id_st->primogenitor->out_params ,ex->tree_node->lexeme);
            
            int offset = p->offset;
            fprintf(fp, "\txor rcx, rcx\n");
            fprintf(fp, "\tmov ecx, [rbp - %d + 208]\n", offset * 8);

            // else if (p1 != NULL) return p1->datatype->simple;
            // else if (p2 != NULL) return p2->datatype->simple;
        }
        else        // is in ID_ST
        {
            printf("here\n");
            if(i->datatype->simple != ARRAY)
            {
                int offset = i->offset;
                fprintf(fp, "\txor rcx, rcx\n");
                fprintf(fp, "\tmov ecx, [rbp - %d]\n", offset * 8);
                return;
            }
            
            
        }
    }

    if (ex->node_marker == RNUM)
    {
        ;
    }
    if (ex->node_marker == NUM)
    {
        char* num = ex->tree_node->lexeme;
        fprintf(fp, "\tmov rcx, %s\n", num);
    }

    if (ex->node_marker == TRUE || ex->node_marker == FALSE)
    {
        if(ex->node_marker == TRUE)
            fprintf(fp, "\tmov rcx, 1\n");
        else
            fprintf(fp, "\tmov rcx, 0\n");
        
    }

    if (ex->node_marker ==  LE||ex->node_marker ==  GE||ex->node_marker ==  LT||ex->node_marker ==  GT||ex->node_marker ==  EQ||ex->node_marker ==  NE)
    {   
        evaluate_expr(ex->child, id_st, fp);
        
        fprintf(fp, "\tpush rcx\n");
        fprintf(fp, "\tpush rcx\n");
        evaluate_expr(ex->child->sibling, id_st, fp);
        fprintf(fp, "\tpop rdx\n");
        fprintf(fp, "\tpop rdx\n");

        fprintf(fp, "\tcmp rdx, rcx\n");

        char* flag = generate_label();
        char* over = generate_label();

        if(ex->node_marker ==  GE)
            fprintf(fp, "\tjge %s\n", flag);
        if(ex->node_marker ==  LT)
            fprintf(fp, "\tjl %s\n", flag);
        if(ex->node_marker ==  GT)
            fprintf(fp, "\tjl %s\n", flag);
        if(ex->node_marker ==  EQ)
            fprintf(fp, "\tje %s\n", flag);
        if(ex->node_marker ==  NE)
            fprintf(fp, "\tjne %s\n", flag);
        if(ex->node_marker ==  LE)
            fprintf(fp, "\tjle %s\n", flag);
        
        fprintf(fp, "\tmov rcx, 0\n");
        fprintf(fp, "jmp %s\n", over);
        fprintf(fp, "%s:\n", flag);
        fprintf(fp, "\tmov rcx, 1\n");
        fprintf(fp, "%s:", over);

    }

    if (ex->node_marker == AND ||ex->node_marker == OR)
    {
        evaluate_expr(ex->child, id_st, fp);
        
        fprintf(fp, "\tpush rcx\n");
        fprintf(fp, "\tpush rcx\n");
        evaluate_expr(ex->child->sibling, id_st, fp);
        fprintf(fp, "\tpop rdx\n");
        fprintf(fp, "\tpop rdx\n");

        if(ex->node_marker == AND)
            fprintf(fp, "and rcx, rdx\n");
        else
            fprintf(fp, "or rcx, rdx\n");
    }

    if (ex->node_marker ==  PLUS    || (ex->node_marker ==  MINUS && ex->child->sibling != NULL)   || ex->node_marker ==  DIV     || ex->node_marker ==  MUL)
    {
        evaluate_expr(ex->child, id_st, fp);
        
        fprintf(fp, "\tpush rcx\n");
        fprintf(fp, "\tpush rcx\n");
        evaluate_expr(ex->child->sibling, id_st, fp);
        fprintf(fp, "\tpop rdx\n");
        fprintf(fp, "\tpop rdx\n");

        if(ex->node_marker == PLUS)
        {
            fprintf(fp, "\tadd rdx, rcx\n");
            fprintf(fp, "\tmov rcx, rdx\n");
            return;
        }
        else if(ex->node_marker == MINUS)
        {
            fprintf(fp, "\tsub rdx, rcx\n");
            fprintf(fp, "\tmov rcx, rdx\n");
            return;
        }
        else if(ex->node_marker == MUL)
        {
            fprintf(fp, "\timul rdx, rcx\n");
            fprintf(fp, "\tmov rcx, rdx\n");
            return;
        }

        else
        {
            // store dividend in rax, divisor in rbx --> quotient in rax, remainedr in rdx
            //@bharat debug this
            fprintf(fp, "\tmov rax, rdx\n");
            fprintf(fp, "\tmov rbx, rcx\n"); 
            fprintf(fp, "\txor rdx, rdx\n");    
            fprintf(fp, "\tdiv rbx\n"); 
            fprintf(fp, "\tmov rcx, rax\n");
        }
    
    }

    if (ex->node_marker == MINUS && ex->child->sibling == NULL)
    {
        evaluate_expr(ex->child, id_st, fp);
        fprintf(fp, "\timul rcx, -1\n");
        return;
    }

    if (ex->node_marker == var)
    {
        if (ex->child->sibling == NULL)     // not an array element
            evaluate_expr(ex->child, id_st, fp);
        else                                // array element
        {
            ID_TABLE_ENTRY *i = st_lookup(ex->child->tree_node->lexeme, id_st);
            if (i == NULL)
            {
                PARAMS *p = param_lookup(id_st->primogenitor->in_params ,ex->child->tree_node->lexeme);
                if (p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params ,ex->child->tree_node->lexeme);
                

                int base_offset = p->offset;
                int start_offset = p->datatype->arrtype->begin_offset;
                int end_offset = p->datatype->arrtype->end_offset;
                int index = atoi(ex->child->sibling->tree_node->lexeme);
                int line = ex->child->sibling->tree_node->line;
                
                bound_check(fp, start_offset, end_offset, index, line);
                fprintf(fp, "\txor rax, rax\n");
                fprintf(fp, "\txor rdx, rdx\n");
                fprintf(fp, "\tmov eax, [rbp - %d + 208]\n", base_offset * 8);
                fprintf(fp, "\tmov edx, [rbp - %d + 208]\n", start_offset * 8);
                fprintf(fp, "\tmov ebx, %d\n", index);
                fprintf(fp, "\tsub ebx, edx\n");
                fprintf(fp, "\txor rcx, rcx\n");
                fprintf(fp, "\tmov ecx, [rax + rbx * 8]\n");
                return;
                //return value 
            }
            else
            {
                int base_offset = i->offset;
                int start_offset = i->datatype->arrtype->begin_offset;
                int end_offset = i->datatype->arrtype->end_offset;
                int index = atoi(ex->child->sibling->tree_node->lexeme);
                int line = ex->child->sibling->tree_node->line;
                
                bound_check(fp, start_offset, end_offset, index, line);
                fprintf(fp, "\txor rax, rax\n");
                fprintf(fp, "\txor rdx, rdx\n");
                fprintf(fp, "\tmov eax, [rbp - %d]\n", base_offset * 8);
                fprintf(fp, "\tmov edx, [rbp - %d]\n", start_offset * 8);
                fprintf(fp, "\tmov ebx, %d\n", index);
                fprintf(fp, "\tsub ebx, edx\n");
                fprintf(fp, "\txor rcx, rcx\n");
                fprintf(fp, "\tmov ecx, [rax + rbx * 8]\n");
                return;
            }
        }
    }
    /*
    {
    }
    */
    /*
    
    if (ex->node_marker == var)
    {
        if (ex->child->sibling == NULL)     // not an array element
            return get_type_expr(ex->child, id_st);
        else                                // array element
        {
            // printf("WHYTHO2?\n");
            ID_TABLE_ENTRY *i = st_lookup(ex->child->tree_node->lexeme, id_st);
            
        
        }
    }
    if (ex->node_marker == ARRAY)
        return ARRAY;
    */
    return;
}

// trav a single function and generate the ASM code
void generate_the_universe(astNode *n, ID_SYMBOL_TABLE *id_st, FILE* fp)
{
    printf("visited: %d\n", id_st->visited);
    // printf("aasdfasdf\n");
    printf("SMALL\t%s\n", variables_array[n->node_marker]);
    if (is(n, "moduleDef"))
    {
        generate_the_universe(n->child->sibling, id_st, fp);
    }
    if (is(n, "statements"))
    {
        for(astNode *temp = n->child; temp; temp = temp->sibling)
        {
            generate_the_universe(temp, id_st, fp);
        }
    }
    if (is(n, "declareStmt"))
    {
        astNode* temp = n->child;

        while(temp->node_marker != EPS)
        {
            // if (stack_count % 2 == 0)
            //     fprintf(fp, "\tsub rsp, 16\n");
            // stack_count++;

            // if array 
            ID_TABLE_ENTRY* id_entry = st_lookup(temp->tree_node->lexeme, id_st);

            if(id_entry->datatype->simple == ARRAY)
            {
                int offset = id_entry->offset;
                // if (stack_count % 2 == 0)
                //     fprintf(fp, "\tsub rsp, 16\n");
                // stack_count++;
                // if (stack_count % 2 == 0)
                //     fprintf(fp, "\tsub rsp, 16\n");
                // stack_count++;

                //storing base address of this array: part of array_buffer
                fprintf(fp, "\txor r14, r14\n");
                fprintf(fp, "\tmov r14d, [array_available_addr]\n");
                fprintf(fp, "\tlea rax, [array_buffer + r14 * 8]\n");
                fprintf(fp, "\tmov [rbp - %d], rax\n\n", offset * 8);

                // if static array
                if (id_entry->datatype->arrtype->is_dynamic == false)
                {
                    int start = id_entry->datatype->arrtype->begin;
                    int end = id_entry->datatype->arrtype->end;

                    //increment array_available_addr by the used memory

                    // calculate array size

                    int array_size = end - start + 1;
                    fprintf(fp, "mov r14d, r14d\n");
                    fprintf(fp, "\tmov r14d, [array_available_addr]\n");
                    fprintf(fp, "\tadd r14, %d\n", array_size);
                    fprintf(fp, "\tmov [array_available_addr], r14\n\n");
                    // load the start and end at their offset

                    int start_offset_scaled = id_entry->datatype->arrtype->begin_offset * 8;
                    int end_offset_scaled  = id_entry->datatype->arrtype->end_offset * 8;
                    
                    fprintf(fp, "; loading array offsets\n");
                    fprintf(fp, "mov r13, %d\n", start);
                    fprintf(fp, "mov [rbp - %d], r13\n", start_offset_scaled);
                    fprintf(fp, "mov r13, %d\n", end);
                    fprintf(fp, "mov [rbp - %d], r13\n\n", end_offset_scaled);
                    
                }

                else
                {

                    astNode* node = n->child;
                    while(node->node_marker != ARRAY)
                    {
                        node = node->sibling;
                    }

                    // now go to 
                    node = node->child->child;
                    astNode* rchild = node->sibling;
                    int start_offset = id_entry->datatype->arrtype->begin_offset;
                    int end_offset = id_entry->datatype->arrtype->end_offset;

                    if(node->node_marker == ID)
                    {
                        ID_TABLE_ENTRY* index = st_lookup(node->tree_node->lexeme, id_st);
                        int offset = index->offset;

                        // load start index value from offset
                        fprintf(fp, "\txor rax, rax\n");
                        fprintf(fp, "\tmov eax, [rbp - %d]\n", offset * 8);
                        fprintf(fp, "\tmov [rbp - %d], rax\n", start_offset * 8);
                    }

                    else
                    {
                        int start = atoi(node->tree_node->lexeme);
                        printf("%d\n", start);
                        fprintf(fp, "mov r13, %d\n", start);
                        fprintf(fp, "mov [rbp - %d], r13\n", start_offset * 8);
                    }
                    if(rchild->node_marker == ID)
                    {
                        ID_TABLE_ENTRY* index = st_lookup(rchild->tree_node->lexeme, id_st);
                        int offset = index->offset;

                        // load end index value from offset
                        fprintf(fp, "\txor rax, rax\n");
                        fprintf(fp, "\tmov eax, [rbp - %d]\n", offset * 8);
                        fprintf(fp, "\tmov [rbp - %d], rax\n", end_offset * 8);
                    }

                    else
                    {
                        int end = atoi(rchild->tree_node->lexeme);
                        fprintf(fp, "mov r13, %d\n", end);
                        fprintf(fp, "mov [rbp - %d], r13\n", end_offset * 8);
                    }

                    char* error_lablel = generate_label();
                    char* exit_label = generate_label();
                    fprintf(fp, "; incrementing array_available address by array size\n\n"); 
                    fprintf(fp, "\txor r14, r14\n");
                    fprintf(fp, "\tmov r14d, [array_available_addr]\n");
                    fprintf(fp, "\txor rax, rax\n");
                    fprintf(fp, "\txor rcx, rcx\n");
                    fprintf(fp, "\tmov eax, [rbp - %d]\n", start_offset * 8);
                    fprintf(fp, "\tmov ecx, [rbp - %d]\n", end_offset * 8);
                    fprintf(fp, "\tcmp eax, ecx\n");
                    fprintf(fp, "\tjg %s\n", error_lablel);
                    fprintf(fp, "\tsub ecx, eax\n");
                    fprintf(fp, "\tinc ecx\n");
                    //fprintf(fp, "\timul rcx, 8\n");
                    fprintf(fp, "\tadd r14d, ecx\n");
                    fprintf(fp, "\tmov [array_available_addr], r14\n\n");
                    fprintf(fp, "\tjmp %s\n", exit_label);

                    fprintf(fp, "\t%s:\n", error_lablel);
                    fprintf(fp, "\tlea rdi, [errorMsg1]\n");
                    // "errorMsg1    db        \"RUN TIME ERROR: End index %%d of Array less
                    // than start index %%d at line %%d. Aborting\", 10, 0\n");
                    fprintf(fp, "\tmov rsi, rcx\n");
                    fprintf(fp, "\tmov rdx,  rax\n");
                    fprintf(fp, "\txor rcx, rcx\n");
                    fprintf(fp, "\tmov rcx, %d\n", node->tree_node->line);
                    fprintf(fp, "\txor rax, rax\n");
                    fprintf(fp, "\tcall printf\n");
                    fprintf(fp, "\tjmp main_end\n");
                    fprintf(fp, "%s:\n", exit_label);
                }

            }

            temp = temp->sibling;
        }
        
    }
    if (is(n, "assignmentStmt"))
    {
        generate_the_universe(n->child, id_st, fp);
    }
    if (is(n, "ASSIGNOP"))
    {
        printf("jdnn\n");
        evaluate_expr(n->child->sibling, id_st, fp); // evaluate the rhs
       
        printf("evaluated\n");
       
        astNode *lhs = n->child;
        astNode *rhs = n->child->sibling;
       if (lhs->node_marker == ARRAY || (lhs->node_marker == var && lhs->child->sibling != NULL))
        {
            // first do a non-recursive lookup
            ID_TABLE_ENTRY *i = st_lookup(lhs->child->tree_node->lexeme, id_st);
            printf("heren\n");
            if (i == NULL) printf("GOTYA\n");
            PARAMS *p = NULL;
            if (i == NULL)      // then check for parameters
            {
                p = param_lookup(id_st->primogenitor->in_params ,lhs->child->tree_node->lexeme);
                if (p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params ,lhs->child->tree_node->lexeme);
                
                int base_offset = p->offset;
                int start_offset = p->datatype->arrtype->begin_offset;
                int end_offset = p->datatype->arrtype->end_offset;
                int index = atoi(lhs->child->sibling->tree_node->lexeme);
                int line = lhs->child->sibling->tree_node->line;
                
                bound_check(fp, start_offset, end_offset, index, line);
                fprintf(fp, "\txor rax, rax\n");
                fprintf(fp, "\txor rdx, rdx\n");
                fprintf(fp, "\tmov eax, [rbp - %d + 208]\n", base_offset * 8);
                fprintf(fp, "\tmov edx, [rbp - %d + 208]\n", start_offset * 8);
                fprintf(fp, "\tmov ebx, %d\n", index);
                fprintf(fp, "\tsub ebx, edx\n");
                fprintf(fp, "\tmov [rax + rbx * 8], rcx \n");
                return;
            }

            int offset = i->offset;
            int start_offset = i->datatype->arrtype->begin_offset;
            int end_offset = i->datatype->arrtype->end_offset;
            int line = lhs->child->tree_node->line;
            fprintf(fp, "\txor rax, rax\n");
            fprintf(fp, "\txor rdx, rdx\n");
            fprintf(fp, "\tmov eax, [rbp - %d]\n", offset * 8);
            fprintf(fp, "\tmov edx, [rbp - %d]\n", start_offset * 8);

            // A[2]
            if(lhs->child->sibling->node_marker != ID)
            {
                int index = atoi(lhs->child->sibling->tree_node->lexeme);
                bound_check(fp, start_offset, end_offset, index, line);
                fprintf(fp, "\tmov ebx, %d\n", index);
            }
            // A[k]
            else
            {
                int index_offset;
                 ID_TABLE_ENTRY* index_entry = st_lookup(lhs->child->sibling->tree_node->lexeme, id_st);
                    
                if(index_entry != NULL)
                {
                    index_offset = index_entry->offset;
                }
                else
                {
                    PARAMS* p = param_lookup(id_st->primogenitor->in_params ,n->child->child->child->tree_node->lexeme);
                    if (p == NULL)
                        p = param_lookup(id_st->primogenitor->out_params ,n->child->child->child->tree_node->lexeme);
                    
                    index_offset = p->offset;
                }
                
                bound_check_dynamic(fp, start_offset, end_offset, index_offset, line);
                fprintf(fp, "\tmov ebx, [rbp - %d]\n", index_offset);
            }
                        
            fprintf(fp, "\tsub ebx, edx\n");
            //fprintf(fp, "\txor rcx, rcx\n");
            fprintf(fp, "\tmov [rax + rbx * 8], rcx\n");
            return;
        }
        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->tree_node->lexeme, id_st);
        if (id_entry != NULL)
        {
            int offset = id_entry->offset;
            fprintf(fp, "\tmov [rbp - %d], rcx\n", offset * 8);
        }
        else
        {
            printf("hetre\n");
            
            PARAMS* p = param_lookup(id_st->primogenitor->in_params ,lhs->tree_node->lexeme);
            printf("gerevgbhf\n");
            if (p == NULL)
                p = param_lookup(id_st->primogenitor->out_params ,lhs->tree_node->lexeme);
            if (p == NULL) printf("7vik's fault\n");
            int offset = p->offset;
            printf("here123\n");
            fprintf(fp, "\tmov [rbp - %d + 208], rcx\n", offset * 8);
        }
        
        
    }
    if (is(n, "iterativeStmt") && is(n->child, "ID"))   // for lup
    {
        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->tree_node->lexeme, id_st);
        
        int offset = id_entry->offset;
        astNode* range = n->child->sibling;
        int start = atoi(range->child->tree_node->value_if_number);
        int end = atoi(range->child->sibling->tree_node->value_if_number);

        // @satvik should handle this
        if (end < start)
        {
            printf("ERROR: end index %d less than start index %d in for loop at line %d\n", end, start, n->tree_node->line);
            exit(1);
        }

        char* for_label = generate_label();
        fprintf(fp, "; for loop\n\n");
        fprintf(fp, "\tmov qword [rbp - %d], %d\n", offset * 8, start);
        fprintf(fp, "\tmov rcx, %d\n", start);
        fprintf(fp, "\tmov rax, %d\n", end);
        fprintf(fp, "%s:\n", for_label);
        fprintf(fp, "\tpush rcx\n\tpush rax\n");
        printf("id_st visited: %d, kid tables: %d\n", id_st->visited, id_st->kid_table_count);
        generate_the_universe(range->sibling->sibling, id_st->kid_st[0], fp);
        //id_st->visited++;

 
        fprintf(fp, "\tpop rax\n\t pop rcx\n");
        fprintf(fp, "\tinc qword [rbp - %d]\n", offset * 8);
        fprintf(fp, "\tinc rcx\n");
        fprintf(fp, "\tcmp rcx, rax\n");
        fprintf(fp, "\tjle %s\n", for_label);

    }
    if (is(n, "iterativeStmt") && (1 - is(n->child, "ID")))   // while lup
    {
       astNode* ex = n->child;
       char* while_label = generate_label();
       char* exit_label = generate_label();
       fprintf(fp, "\t%s:\n", while_label);
       evaluate_expr(ex, id_st, fp);
       fprintf(fp, "\tcmp rcx, 0\n");
       fprintf(fp, "\tje %s", exit_label);
       generate_the_universe(n->child->sibling->sibling, id_st->kid_st[id_st->visited], fp);
       id_st->visited++;
       fprintf(fp, "\tjmp %s\n", while_label);
       fprintf(fp, "\t%s:\n\n", exit_label);

    }
    if (is(n, "ioStmt") && n->child->node_marker == GET_VALUE)
    {

        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->child->tree_node->lexeme, id_st);

        if(id_entry != NULL)
        {
            if (id_entry->datatype->simple != ARRAY)
            {
                fprintf(fp, "\t;Taking id\n\n");
                prompt_user(fp, id_entry->datatype->simple);       
                take_input(fp,  id_entry->datatype->simple, id_entry->offset);
            }

            else 
            {
                fprintf(fp, "\t;Taking array\n\n");
                ask_for_array(fp, id_entry->offset * 8, id_entry->datatype->arrtype->begin_offset * 8, id_entry->datatype->arrtype->end_offset * 8, id_entry->datatype->arrtype->base_type);
            }
        }

        else
        {
            PARAMS* p = param_lookup(id_st->primogenitor->in_params ,n->child->child->tree_node->lexeme);
            if (p == NULL)
                p = param_lookup(id_st->primogenitor->out_params ,n->child->child->tree_node->lexeme);

            if (p->datatype->simple != ARRAY)
            {
                fprintf(fp, "\t;Taking id\n\n");
                prompt_user(fp, p->datatype->simple); 
                int type = id_entry->datatype->simple;
                int offset = p->offset;
                int temp = offset * 8;
                if(type == INTEGER || type == BOOLEAN)
                {
                    fprintf(fp, "\tmov rdi, intFormat_in\n");
                    fprintf(fp, "\tlea rsi, [rbp - %d]\n", temp);
                    fprintf(fp, "\tcall scanf\n");
                }

                else if(type == REAL)
                {
                    fprintf(fp, "\tmov rdi, realFormat_in\n");
                    fprintf(fp, "\tlea rsi, [rbp - %d]\n", temp);
                    fprintf(fp, "\tcall scanf\n");
                }      
            }

            else 
            {
                fprintf(fp, "\t;Taking array\n\n");
                int base_offset = p->offset * 8;
                int lower_offset = p->datatype->arrtype->begin_offset * 8;
                int upper_offset = p->datatype->arrtype->end_offset * 8;
                int type = p->datatype->arrtype->base_type;
                fprintf(fp, "; prompts user for input\n");
                fprintf(fp, "\tmov ecx, [rbp - %d]\n", lower_offset);
                fprintf(fp, "\tmov r8d, [rbp - %d]\n", upper_offset);
                fprintf(fp, "\tmov esi, r8d\n");
                fprintf(fp, "\tsub esi, ecx\n");
                fprintf(fp, "\tinc esi\n");
                fprintf(fp, "\tmov rdi, arr_inMsg\n");

                if (type == INTEGER)
                    fprintf(fp, "mov rdx, type_int\n");
                else if (type == REAL)
                    fprintf(fp, "mov rdx, type_real\n");
                else if (type == BOOLEAN)
                    fprintf(fp, "mov rdx, type_bool\n");
                else
                {
                    printf("Error in ask for array function\n");
                    exit(1);
                }
                fprintf(fp, "\txor rcx, rcx\n");
                fprintf(fp, "\txor r8, r8\n");
                fprintf(fp, "\tmov ecx, [rbp - %d]\n", lower_offset);
                fprintf(fp, "\tmov r8d, [rbp - %d]\n", upper_offset);
                fprintf(fp, "\tcall printf\n\n");

                char* array_input_label  = generate_label();
                fprintf(fp, "\t; stores the count\n\n");
                fprintf(fp, "\txor r12, r12\n");
                fprintf(fp, "\txor r13, r13\n");
                fprintf(fp, "\tmov r12d, [rbp - %d]\n", upper_offset);
                fprintf(fp, "\tmov r13d, [rbp - %d]\n", lower_offset);
                fprintf(fp, "\tsub r12d, r13d\n");
                fprintf(fp, "\tinc r12d\n");
                fprintf(fp, "\txor r13, r13\n\n");  
                fprintf(fp, "\t%s:\n", array_input_label);

                if(type == INTEGER)
                {
                    fprintf(fp, "lea rdi, [intFormat_in]\n");
                
                }

                else if(type == REAL)
                {
                    fprintf(fp, "lea rdi, [realFormat_in]\n");
                }

                else if(type == BOOLEAN)
                {
                    fprintf(fp, "lea rdi, [intFormat_in]\n");
                }

                else
                {
                    printf("ERROR in ask for array\n");
                    exit(1);
                }
                fprintf(fp, "\txor r14, r14\n");
                fprintf(fp, "\tmov r14d, [rbp - %d]\n", base_offset);
                fprintf(fp, "\tlea rsi, [r14 + r13 * 8]\n");
                fprintf(fp, "\tcall scanf\n\n");

                fprintf(fp, "\tinc r13d\n");
                fprintf(fp, "\tcmp r13d, r12d\n");
                fprintf(fp, "\tjne %s\n", array_input_label);
                // fprintf(fp, "pop rbp\n");
                fprintf(fp, "\n\n");
            }
            
        }
        

    }
    if (is(n, "ioStmt") && n->child->node_marker == printOpt)
    {
        printf("here io1\n");
        
        // print constant
        if(n->child->child->child == NULL)
        {
            if(n->child->child->node_marker == NUM)
            {
                int num = atoi(n->child->child->tree_node->lexeme);
                fprintf(fp, "\tlea rdi, [intFormat_out]\n");
                fprintf(fp, "xor rsi, rsi\n");
                fprintf(fp, "\tmov esi, %d\n", num);
                fprintf(fp, "\tcall printf\n");

                fprintf(fp, "\tlea rdi, [new_line]\n");
                fprintf(fp, "\tcall printf\n\n");
            }
            else
            {
                if(n->child->child->node_marker == TRUE)
                {
                    fprintf(fp, "lea rsi, [true_label]\n");
                }
                else
                {
                    fprintf(fp, "lea rsi, [false_label]\n");
                }
                fprintf(fp, "\tlea rdi, [strFormat_out]\n");
                fprintf(fp, "\tcall printf\n");
                
            }
            
            return;
        }
        printf("%s\n", n->child->child->child->tree_node->lexeme);
        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->child->child->tree_node->lexeme, id_st);
        
        if(id_entry != NULL)
        {
            if (id_entry->datatype->simple != ARRAY)
            {
                printf("here io\n");
                fprintf(fp, "\t;Printing ID\n\n");
                print_id(fp,  id_entry->datatype->simple, id_entry->offset);
            }
            else if(n->child->child->child->sibling == NULL)
            {
                fprintf(fp, "\t;Printing array\n\n");
                print_array(fp, id_entry->offset * 8, id_entry->datatype->arrtype->begin_offset * 8, id_entry->datatype->arrtype->end_offset * 8, id_entry->datatype->arrtype->base_type);
            }
            else
            {
                astNode* index = n->child->child->child->sibling;
                astNode* array_node = n->child->child->child;
                int index_offset;
                int base_offset = id_entry->offset;
                int start_offset = id_entry->datatype->arrtype->begin_offset;
                int end_offset = id_entry->datatype->arrtype->end_offset;
                int line = array_node->tree_node->line; 
                int type = id_entry->datatype->arrtype->base_type;
                if(index->node_marker == ID) // A[k]
                {
                    ID_TABLE_ENTRY* index_entry = st_lookup(index->tree_node->lexeme, id_st);
                    
                    if(index_entry != NULL)
                    {
                        index_offset = index_entry->offset;
                        bound_check_dynamic(fp, start_offset, end_offset, index_offset, line);
                        print_array_id_dynamic(fp, type, base_offset, start_offset, index_offset);
                        return;
                    }
                    else
                    {
                        PARAMS* p = param_lookup(id_st->primogenitor->in_params ,n->child->child->child->tree_node->lexeme);
                        if (p == NULL)
                            p = param_lookup(id_st->primogenitor->out_params ,n->child->child->child->tree_node->lexeme);
                        
                        index_offset = p->offset;
                        bound_check_dynamic(fp, start_offset, end_offset, index_offset, line);
                        print_array_id_dynamic(fp, type, base_offset, start_offset, index_offset);
                    }
                    
                    
                }
                else  // A[2]
                {
                    int index_value = atoi(index->tree_node->lexeme);
                    bound_check(fp, start_offset, end_offset, index_value, line);
                    print_array_id(fp, type, base_offset, start_offset, index_value);
                }
                
            }
            
        }

        else
        {
            PARAMS* p = param_lookup(id_st->primogenitor->in_params ,n->child->child->child->tree_node->lexeme);
            if (p == NULL)
                p = param_lookup(id_st->primogenitor->out_params ,n->child->child->child->tree_node->lexeme);
            if (p->datatype->simple != ARRAY)
            {
                fprintf(fp, "\t;Printing ID\n\n");
                int type = p->datatype->simple;
                int offset = p->offset;
                int temp = offset * 8;
                if(type == INTEGER)
                {
                    fprintf(fp, "\tmov rdi, intFormat_out\n");
                    fprintf(fp, "\txor rsi, rsi\n");
                    fprintf(fp, "\tmov esi, [rbp - %d + 208]\n", temp);
                    fprintf(fp, "\tcall printf\n\n");
                    fprintf(fp, "\tlea rdi, [new_line]\n");
                    fprintf(fp, "\tcall printf\n\n");
                }

                else if(type == REAL)
                {
                    fprintf(fp, "\tmov rdi, realFormat_out\n");
                    fprintf(fp, "\txor rsi, rsi\n");
                    fprintf(fp, "\tmov esi, [rbp - %d + 208]\n", temp);
                    fprintf(fp, "\tcall printf\n\n");
                    fprintf(fp, "\tlea rdi, [new_line]\n");
                    fprintf(fp, "\tcall printf\n\n");
                }

                else if(type == BOOLEAN)
                {
                    char* f_label = generate_label();
                    char* p_label = generate_label();
                    fprintf(fp, "\tlea rdi, [strFormat_in]\n");
                    fprintf(fp, "\tmov sil, [rbp - %d + 208]\n\n", temp);
                    fprintf(fp, "\tcmp sil, 0\n");
                    fprintf(fp, "\tjz %s\n", f_label);
                    fprintf(fp, "\tlea rsi, [true_label]\n");
                    fprintf(fp, "\tjmp %s\n\n", p_label);
                    fprintf(fp, "%s: \n", f_label);
                    fprintf(fp, "\tlea rsi, [false_label]\n\n");
                    fprintf(fp, "%s: \n", p_label);
                    fprintf(fp, "\tcall printf\n\n");
                    fprintf(fp, "\tlea rdi, [new_line]\n");
                    fprintf(fp, "\tcall printf\n");
                    fprintf(fp, "\n\n");
                }
            }
            else
            {
                printf("here\n");
                fprintf(fp, "\t;Printing array\n\n");
                int base_offset = p->offset * 8;
                int lower_offset = p->datatype->arrtype->begin_offset * 8;
                int upper_offset = p->datatype->arrtype->end_offset * 8;
                int type = p->datatype->arrtype->base_type;

                fprintf(fp, "; printing array\n");
                fprintf(fp, "lea rdi, [arr_outMsg]\n");
                fprintf(fp, "call printf\n");

                char* array_output_label = generate_label();
                fprintf(fp, "; stores the count\n\n");
                fprintf(fp, "xor r12, r12\n");
                fprintf(fp, "xor r13, r13\n");
                fprintf(fp, "mov r12d, [rbp - %d + 208]\n", upper_offset);
                fprintf(fp, "mov r13d, [rbp - %d + 208]\n", lower_offset);
                fprintf(fp, "sub r12d, r13d\n");
                fprintf(fp, "inc r12d\n");
                fprintf(fp, "xor r13, r13\n\n");  
                fprintf(fp, "%s:\n", array_output_label);

                if(type == INTEGER)
                {
                    fprintf(fp, "\tlea rdi, [intFormat_out]\n");
                    fprintf(fp, "\txor r14, r14\n");
                    fprintf(fp, "\tmov r14d, [rbp - %d + 208]\n", base_offset);
                    fprintf(fp, "\tmov rsi, [r14 + r13 * 8]\n");
                }

                else if(type == REAL)
                {
                    fprintf(fp, "lea rdi, [realFormat_out]\n");
                    fprintf(fp, "\txor r14, r14\n");
                    fprintf(fp, "\tmov r14d, [rbp - %d + 208]\n", base_offset);
                    fprintf(fp, "\tlea rsi, [r14 + r13 * 8]\n");
                    
                }

                else if(type == BOOLEAN)
                {
                    char* f_label = generate_label();
                    char* p_label = generate_label();
                    fprintf(fp, "\tlea rdi, [strFormat_in]\n");
                    fprintf(fp, "\txor r14, r14\n");
                    fprintf(fp, "\tmov r14d, [rbp - %d + 208]\n", base_offset);
                    fprintf(fp, "\tmov rsi, [r14 + r13 * 8]\n");

                    fprintf(fp, "\tcmp sil, 0\n");
                    fprintf(fp, "\tjz %s\n", f_label);
                    fprintf(fp, "\tlea rsi, [true_label]\n");
                    fprintf(fp, "\tjmp %s\n\n", p_label);
                    fprintf(fp, "%s: \n", f_label);
                    fprintf(fp, "\tlea rsi, [false_label]\n\n");

                    fprintf(fp, "%s: \n", p_label);

                }

                else
                {
                    printf("ERROR in ask for array\n");
                    exit(1);
                }
                
                fprintf(fp, "\tcall printf\n\n");
                fprintf(fp, "\tinc r13d\n");
                fprintf(fp, "\tcmp r13d, r12d\n");
                fprintf(fp, "\tjne %s\n", array_output_label);
                fprintf(fp, "\tlea rdi, [new_line]\n");
                fprintf(fp, "\tcall printf\n");

                // fprintf(fp, "pop rbp\n");
                fprintf(fp, "\n\n");
            }
        }
        
    }
    if (is(n, "conditionalStmt"))
    {
        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->tree_node->lexeme, id_st);
        
        int offset = id_entry->offset;
        
        fprintf(fp, "\txor rax, rax\n");
        fprintf(fp, "\tmov eax, [rbp - %d]\n", offset * 8);
        
        if(id_entry->datatype->simple != BOOLEAN)
        {
            generate_the_universe(n->child->sibling->sibling, id_st->kid_st[id_st->visited], fp);
            id_st->visited++;
        }
        else
        {
            astNode* case_node = n->child->sibling->sibling->child;
            char* cases_exit = generate_label();
            char* case_exit = generate_label();
            fprintf(fp, "\tcmp rax, %d\n", 1);
            fprintf(fp, "\tjne %s\n", case_exit);
            fprintf(fp, "\tpush rax\n\tpush rax\n");
            generate_the_universe(case_node->child->sibling, id_st->kid_st[id_st->visited], fp);
            fprintf(fp, "\tpop rax\n\tpop rax\n");
            fprintf(fp, "\tjmp %s\n", cases_exit);
            fprintf(fp, "\t%s:\n", case_exit);

            fprintf(fp, "\tpush rax\n\tpush rax\n");
            generate_the_universe(case_node->sibling->child->sibling, id_st->kid_st[id_st->visited], fp);
            id_st->visited++;
            fprintf(fp, "\tpop rax\n\tpop rax\n");
            fprintf(fp, "\t%s:\n", cases_exit);   
        }
        


    }
    if (is(n, "caseStmts"))
    {
        char* cases_exit = generate_label();
        for (astNode *temp = n->child; temp; temp = temp->sibling)
        {
            int num = atoi(temp->child->tree_node->lexeme);
            char* case_exit = generate_label();
            fprintf(fp, "\tcmp rax, %d\n", num);
            fprintf(fp, "\tjne %s\n", case_exit);
            fprintf(fp, "\tpush rax\n\tpush rax\n");
            generate_the_universe(temp->child->sibling, id_st, fp);
            fprintf(fp, "\tpop rax\n\tpop rax\n");
            fprintf(fp, "\tjmp %s\n", cases_exit);
            fprintf(fp, "\t%s:\n", case_exit);
        }

        astNode* default_nt_node = n->sibling;
        generate_the_universe(default_nt_node->child, id_st, fp);
        fprintf(fp, "%s:\n", cases_exit);

    }
  
    if (is(n, "moduleReuseStmt") && n->child->node_marker == EPS)
    {
        char* func_name = n->child->sibling->tree_node->lexeme;

        astNode* id_list_node = n->child->sibling->sibling->child;
        int count = 0;
        while(id_list_node->node_marker != EPS)
        {
            ID_TABLE_ENTRY* id_entry = st_lookup(id_list_node->tree_node->lexeme, id_st);
            int offset = id_entry->offset;
            if(id_entry->datatype->simple != ARRAY)
            {
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp,"mov r15d, [rbp - %d]\n", offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                id_list_node = id_list_node->sibling;
                count++;
            }

            else if(id_entry->datatype->simple == ARRAY)
            {
                int start_offset = id_entry->datatype->arrtype->begin_offset;
                int end_offset = id_entry->datatype->arrtype->end_offset;
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                count++;
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", start_offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                count++;
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", end_offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                id_list_node = id_list_node->sibling;
                count++;
            }
        }
        fprintf(fp, "\tcall %s\n", func_name);
    }
    if (is(n, "moduleReuseStmt") && n->child->node_marker != EPS)
    {
        printf("satvik\n");
       char* func_name = n->child->sibling->tree_node->lexeme;

        astNode* id_list_node = n->child->sibling->sibling->child;
        int count = 0;
        while(id_list_node->node_marker != EPS)
        {
            printf("here3\n");
            ID_TABLE_ENTRY* id_entry = st_lookup(id_list_node->tree_node->lexeme, id_st);
            int offset = id_entry->offset;
            if(id_entry->datatype->simple != ARRAY)
            {
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                id_list_node = id_list_node->sibling;
                count++;
            }

            else if(id_entry->datatype->simple == ARRAY)
            {
                int start_offset = id_entry->datatype->arrtype->begin_offset;
                int end_offset = id_entry->datatype->arrtype->end_offset;
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                count++;
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", start_offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                count++;
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", end_offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                id_list_node = id_list_node->sibling;
                count++;
            }
        }
        fprintf(fp, "\tcall %s\n", func_name);

        printf("here1\n");
        id_list_node = n->child->child;
        count = 0;
        printf("here2\n");
        while(id_list_node->node_marker != EPS)
        {
            ID_TABLE_ENTRY* id_entry = st_lookup(id_list_node->tree_node->lexeme, id_st);
            int offset = id_entry->offset;
            fprintf(fp, "mov [rbp - %d], %s\n", offset * 8, registers_array[count]);
            id_list_node = id_list_node->sibling;
            count++;
        }
        printf("here3\n");

    }
    return;
}


// trav the ast and create ASM code 
void generate_the_multiverse(astNode *n, GST *st, FILE* fp)
{
    printf("BIG\t%s\n", variables_array[n->node_marker]);
    if (is(n,"program"))
    {
        for(astNode *temp = n->child; temp; temp = temp->sibling)
        {
            generate_the_multiverse(temp,st, fp);
        }
    }

    if (is(n, "moduleDeclarations"))
        ;
    if (is(n, "otherModules"))
    {
        astNode* module_node = n->child;

        while(module_node != NULL)
        {
            FUNC_TABLE_ENTRY* func_entry = global_st_lookup(module_node->child->tree_node->lexeme, st);
            char* func_label = generate_func_label(module_node->child->tree_node->lexeme);
            printf("Generating code for module %s\n", module_node->child->tree_node->lexeme);
            fprintf(fp, "%s\n\n", func_label);
            fprintf(fp, "\tpush rbp\n");
            fprintf(fp, "\tmov rbp, rsp\n");
            fprintf(fp, "\tpush rdi\n");
            fprintf(fp, "\tpush rsi\n");
            fprintf(fp, "\tpush rdx\n");
            fprintf(fp, "\tpush rcx\n");
            fprintf(fp, "\tpush r8\n");
            fprintf(fp, "\tpush r9\n");
            fprintf(fp, "\tpush r10\n");
            fprintf(fp, "\tpush r11\n");
            fprintf(fp, "\tpush r12\n");
            fprintf(fp, "\tpush r13\n");
            fprintf(fp, "\tpush r14\n");
            fprintf(fp, "\tpush r15\n");
            fprintf(fp, "\tsub rsp, 96\n");
            fprintf(fp, "\tpush rbp\n");
            fprintf(fp, "\tpush rbp\n");
            fprintf(fp, "\tmov rbp, rsp\n");
            fprintf(fp, "\tsub rsp, %d\n", (func_entry->activation_record_size) * 16);
            generate_the_universe(module_node->child->sibling->sibling->sibling, func_entry->local_id_table ,fp); 
            fprintf(fp, "\tmov rsp, rbp\n");
            fprintf(fp, "\tpop rbp\n");
            fprintf(fp, "\tpop rbp\n");
            fprintf(fp, "\tpop r15\n");
            fprintf(fp, "\tpop r14\n");
            fprintf(fp, "\tpop r13\n");
            fprintf(fp, "\tpop r12\n");
            fprintf(fp, "\tpop r11\n");
            fprintf(fp, "\tpop r10\n");
            fprintf(fp, "\tpop r9\n");
            fprintf(fp, "\tpop r8\n");
            fprintf(fp, "\tpop rcx\n");
            fprintf(fp, "\tpop rdx\n");
            fprintf(fp, "\tpop rsi\n");
            fprintf(fp, "\tpop rdi\n");
            fprintf(fp, "\tmov rsp, rbp\n");
            fprintf(fp, "\tpop rbp\n");
            fprintf(fp, "\tret\n"); 
            printf("Generating code for module %s completed\n", module_node->child->tree_node->lexeme);  
            module_node = module_node->sibling; 
        }

    }

    if (is(n, "driverModule"))
    {
        FUNC_TABLE_ENTRY *f = global_st_lookup("driverModule", st);
        printf("pointer inside drver: %p", &(*(f->local_id_table)));
        printf("visted inside driver: %d, %p\n", (f->local_id_table)->visited, &((f->local_id_table)->visited));
        id_st_print(f->local_id_table);
        printf("visted inside driver: %d\n", f->local_id_table->visited);
        printf("driver module started\n");
        fprintf(fp, "main:\n\n");
        fprintf(fp, "push rbp\n");
        fprintf(fp, "mov rbp, rsp\n");
        fprintf(fp, "\tsub rsp, %d\n", (f->activation_record_size) * 16);
        printf("visted inside driver: %d\n", f->local_id_table->visited);
        id_st_print(f->local_id_table);
        //stack_count = 0;
        printf("visted inside driver: %d\n", f->local_id_table->visited);
        generate_the_universe(n->child, f->local_id_table, fp);
        printf("driver module ended\n");
    }
    if (is(n, "EPS"))
        return;         // bliss

    return;
}

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        printf("Invalid argument count. Expected 4 arguments as in './executable testcase parse_outfile code.asm'.");
        printf("\nAborting Execution!!\n");
        exit(2);
    }
    FILE* test_fp = fopen(argv[1], "r");
    FILE* test_parse_fp = fopen(argv[2], "w");
    if (test_fp == NULL || test_parse_fp == NULL)
    {
        printf("Error in opening files. Exitting.\n");
        exit(1);
    }
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
    astNode* ast_root = buildAST(tree);
    print_ast_json(ast_root, "output_ast_tree.json");
    // Test Symbol table
    GST *st = create_global_st();
    traverse_the_multiverse(ast_root, st);
    gst_print(st);                                                   // instead of cool, beautiful print,
    //v_gst_print(st);                                                    // do boring print
    printf("Performing further semantic analysis\n\n");
    //semantic_analyser(ast_root, st);
    printf("No semantic errors found\n\n");

    if (hasSemanticError == true)
    {
        printf("Semantic errors detected. Code generation aborted. Exitting\n");
        exit(3);
    }
    // test code generation
    printf("Starting code generation\n");
    FILE* code_fp = fopen(argv[3], "w");
    initialise_file(code_fp);
    generate_the_multiverse(ast_root, st, code_fp);
    print_return(code_fp);
    fclose(test_fp);
    fclose(test_parse_fp);
    free(twin_buff);
    free(parse_table);
    return 0;
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

    fclose(test_fp);
    fclose(test_parse_fp);
    free(twin_buff);
    free(parse_table);
    return 0;
}
*/