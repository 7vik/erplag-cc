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
        //printf("%s\n",variables_array[temp->node_marker]);
        if(temp->node_marker == moduleDeclarations)
        {
            check_moduleDeclarations_semantic(temp, global_st);
            temp = temp->sibling;
        }
        if(temp->node_marker == otherModules)
        {
            check_otherModules_semantic(temp, global_st);
            temp = temp->sibling;
        }
        if(temp->node_marker == driverModule)
        {
            check_driverModule_semantic(temp, global_st);
            temp = temp->sibling;
        }
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

    if (func_entry == NULL)
    {
        hasSemanticError = true;
        return;
        //printf("ERROR in check module, function entry should have been there in symbol table\n");
    }
    else // the function is defined
    {
        func_entry->is_declared += 1;
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

    if(id_entry->datatype->simple == ARRAY) // How can the switch variable be an array variable?
    {
        printf("SEMANTIC ERROR at line %d: %s is an array variable.\n", temp->tree_node->line, temp->tree_node->lexeme);
        hasSemanticError = true;
	    return;
    }

    else if(id_entry->datatype->simple == REAL) // Nah, still not over; this cannot be of type "real" as well.
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
            printf("SEMANTIC ERROR at line %d: boolean conditional statement cannot have a single case.\n", temp->tree_node->line);
            hasSemanticError = true;
        }
        else if(temp->sibling->sibling != NULL) // we're having >=3 cases! Binary system: 0, 1, and ?? => Error
        {
            printf("SEMANTIC ERROR at line %d: boolean conditional statement cannot have more than two cases.\n", temp->sibling->sibling->tree_node->line);
            hasSemanticError = true;
        }
        // if we haven't entered any aforementioned condition, we now have 2 case statements in the construct

        else if(temp->child->node_marker == TRUE && temp->sibling->child->node_marker == TRUE)
        {
            printf("SEMANTIC ERROR at line %d: The two boolean conditions cannot have the same case variable TRUE.\n", temp->sibling->tree_node->line);
            hasSemanticError = true;
        }        

        else if(temp->child->node_marker == FALSE && temp->sibling->child->node_marker == FALSE)
        {
            printf("SEMANTIC ERROR at line %d: The two boolean conditions cannot have the same case variable FALSE.\n", temp->sibling->tree_node->line);
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

    // ARRAY!
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

    assert(root->node_marker == default_nt);

    if(id_entry->datatype->simple == BOOLEAN)   // Now, why default?
    {
        printf("SEMANTIC ERROR at line %d: A default statement shouldn't have been present here.\n", root->tree_node->line);
        hasSemanticError = true;
    }

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

    // now, the node marker for temp is either ASSIGNOP or EPS
    if(temp->node_marker == EPS && func_entry->out_params != NULL)  // the function returns some value(s)
    {
        printf("SEMANTIC ERROR at line %d: Function '%s' returns some value(s).\n", temp->tree_node->line, func_entry->func_name);
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
        printf("SEMANTIC ERROR at line %d: Mismatch in the number of return values in definition and usage of function '%s'.\n", temp->tree_node->line, func_entry->func_name);
        hasSemanticError = true;
    }
    else if(count_ret1 != 0 && count_ret2 != 0) /* count_ret1 equals count_ret2, now traverse again and match the types */
    {
        trav1 = temp->child;
        trav2 = func_entry->out_params;
        while(trav2 != NULL)
        {
            lookup_id = st_lookup(trav1->tree_node->lexeme, id_table);

            if (lookup_id == NULL)
                return;
            if(lookup_id->datatype->simple != trav2->datatype->simple)
            {
                printf("SEMANTIC ERROR at line %d: Variable %s should have type %s.\n", trav1->tree_node->line, trav1->tree_node->lexeme, variables_array[trav2->datatype->simple]);
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
        lookup_id = st_lookup(trav1->tree_node->lexeme, id_table);
        if(lookup_id->datatype->simple != trav2->datatype->simple)
        {
            printf("SEMANTIC ERROR at line %d: Variable %s should have type %s.\n", trav1->tree_node->line, trav1->tree_node->lexeme, variables_array[trav2->datatype->simple]);
            hasSemanticError = true;
        }
        count_inp1++;
        count_inp2++;
        trav1 = trav1->sibling;
        trav2 = trav2->next;
    }

    if(count_inp1 != count_inp2)
    {
        printf("SEMANTIC ERROR at line %d: Mismatch in the number of input values in definition and usage of function '%s'.\n", temp->tree_node->line, func_entry->func_name);
        hasSemanticError = true;
    }

    // Rest of the semantics should be dealt with during type checking phase.
    // Comment out any check if already dealt with previously.
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

