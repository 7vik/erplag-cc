// gcc symbol_table.c ast.c parser.c lexer.c hash.c bool.c

#include "symbol_table.h"
#include "type.h"
#include<stdlib.h>                                      // int atoi(), char *strcat()
#include<string.h>                                      // char *strcpy()
#define ST_ABS(N) ((N<0)?(-N):(N))                      // because of my awesome hashing function
#define malloc_error { printf("Malloc error. Terminating.\n\n"); exit(5); }

bool hasSemanticError = false;
unsigned int current_offset = 100;
unsigned int error_line = 0;

// hash function: implementing vunDina's hash, patent pending ;)
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
        char* str1 = malloc( l1 + 1 );
        char* str2 = malloc( l2 + 1 );
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
        return st_lookup(name, (ID_SYMBOL_TABLE *)st->id_st_parent);         // assuming scope only broadens with nesting, uncomment as per the requirement
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
    new->offset = current_offset++;     
    new->next = NULL;
    new->is_declared = false;
    if (new->datatype->simple == ARRAY)
    {
        // new->datatype->arrtype->end_offset = current_offset++;
        // new->datatype->arrtype->begin_offset = current_offset++;
    }
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
        if (get_type_expr(ex->child, id_st) != get_type_expr(ex->child->sibling, id_st))
        {
            if (ex->tree_node->line > error_line)
                printf("Semantic Error on line %d. Expected type '%s' for comparison, gotten type '%s'.\n",ex->tree_node->line, variables_array[get_type_expr(ex->child, id_st)], variables_array[get_type_expr(ex->child->sibling, id_st)]);
            error_line = ex->tree_node->line;
            hasSemanticError = true;
        }
        else
            return BOOLEAN;
    }
    if (ex->node_marker == AND ||ex->node_marker == OR||0)
    {
        if (get_type_expr(ex->child, id_st) != get_type_expr(ex->child->sibling, id_st))
        {
            if (ex->tree_node->line > error_line)
                printf("Semantic Error on line %d. Expnected type '%s' for comparison, gotten type '%s'.\n",ex->tree_node->line, variables_array[get_type_expr(ex->child, id_st)], variables_array[get_type_expr(ex->child->sibling, id_st)]);
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
        if (t1 != t2)
        {
            // printf("ENTERIF\n");
            if (ex->tree_node->line > error_line)
                printf("Semantic Error on line %d. Exprected type '%s' for arithmetic operation, gotten type '%s'.\n",ex->tree_node->line, variables_array[get_type_expr(ex->child, id_st)], variables_array[get_type_expr(ex->child->sibling, id_st)]);
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
        if (ex->child->sibling == NULL)     // not an array
            return get_type_expr(ex->child, id_st);
        else                                // array
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
                    if (ex->tree_node->line > error_line)
                        printf("Semantic Error on line %d. Variable '%s' not declared.\n", ex->tree_node->line, ex->child->tree_node->lexeme);
                    error_line = ex->tree_node->line;
                    hasSemanticError = true;
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
    return 42;      // hopefully never
}

void traverse_the_universe(astNode *n, ID_SYMBOL_TABLE *id_st)
{
    // printf("->\t%s\n", n->tree_node->node_symbol);
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
                if (error_line < temp->tree_node->line)
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
                t->arrtype->begin_offset = current_offset++;            // in any case, 
                t->arrtype->end_offset   = current_offset++;            // fill the offsets
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
        // printf("WOW %s\n", rhs->tree_node->node_symbol);
        // if (lhs->tree_node->lexeme == NULL) printf("MILLA\n");
        if (lhs->node_marker == ARRAY || (lhs->node_marker == var && lhs->child->sibling != NULL))
        {
            // first do a non-recursive lookup
            ID_TABLE_ENTRY *i = st_lookup_nr(lhs->child->tree_node->lexeme, id_st);
            // if (i == NULL) printf("GOTYA\n");
            PARAMS *p;
            if (i == NULL)      // then check for parameters
            {
                p = param_lookup(id_st->primogenitor->in_params ,lhs->child->tree_node->lexeme);
                if (p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params ,lhs->child->tree_node->lexeme);
            }
            if (i == NULL && p == NULL) // finally do a recursive lookup
                i = st_lookup(lhs->child->tree_node->lexeme, id_st);

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
                    printf("Semantic Error on line %d. Expected type '%s' for variable, gotten type '%s'.\n",lhs->child->tree_node->line, variables_array[i->datatype->arrtype->base_type], variables_array[get_type_expr(rhs, id_st)]);
                error_line = n->child->tree_node->line;
                hasSemanticError = true;
            }
            if (p != NULL && (p->datatype->arrtype->base_type != get_type_expr(rhs, id_st)))
            {
                if (error_line < lhs->child->tree_node->line)
                    printf("Semantic Error on line %d. Expected type '%s' for variable, gotten type '%s'.\n",lhs->child->tree_node->line, variables_array[p->datatype->arrtype->base_type], variables_array[get_type_expr(rhs, id_st)]);
                error_line = n->child->tree_node->line;
                hasSemanticError = true;
            }
        }
        else    // not an array
        {
            PARAMS *p; ID_TABLE_ENTRY *i;
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
                // printf("DOD4\n");
            }
            if (p == NULL && i == NULL)
            {
                if (error_line < lhs->tree_node->line)
                    printf("Semantic Error on line %d. Variable '%s' not declared.\n", lhs->tree_node->line, lhs->tree_node->lexeme);
                error_line = lhs->tree_node->line;
                hasSemanticError = true;
            }

            if (p == NULL || i != NULL)
            {
                // types must match before assignment
                if (i->datatype->simple != get_type_expr(rhs, id_st))
                {
                    if (error_line < lhs->tree_node->line)
                        printf("Semantic Error on line %d. Expected type '%s' for variable, gotten type '%s'.\n",lhs->tree_node->line, variables_array[i->datatype->simple], variables_array[get_type_expr(rhs, id_st)]);
                    error_line = lhs->tree_node->line;
                    hasSemanticError = true;
                }
                else;
                    //printf("");
            }
            if (p != NULL || i == NULL)
            {
                // types must match before assignment
                if (p->datatype->simple != get_type_expr(rhs, id_st))
                {
                    if (error_line < lhs->tree_node->line)
                        printf("Semantic Error on line %d. Expected type '%s' for variable, gotten type '%s'.\n",lhs->tree_node->line, variables_array[p->datatype->simple], variables_array[get_type_expr(rhs, id_st)]);
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
        if (is(n->child, "LE"))
        {
            ID_TABLE_ENTRY *i1 = st_lookup(n->child->child->child->tree_node->lexeme, id_st);
            ID_TABLE_ENTRY *i2 = st_lookup(n->child->child->sibling->child->tree_node->lexeme, id_st);
            if (i1 == NULL && i2 == NULL)
            {
                if (error_line < n->child->tree_node->line)
                    printf("Semantic Error on line %d. While loop variables not declared.\n", n->child->tree_node->line);
                error_line = n->child->tree_node->line;
                hasSemanticError = true;
            }
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
        else
        {
            // it's not a get value, hence a printop, same shit
            ID_TABLE_ENTRY *i1 = st_lookup(n->child->child->child->tree_node->lexeme, id_st);
            PARAMS *p1 = param_lookup(id_st->primogenitor->in_params ,n->child->child->child->tree_node->lexeme);
            PARAMS *p2 = param_lookup(id_st->primogenitor->out_params ,n->child->child->child->tree_node->lexeme);
            if (i1 == NULL && p1 == NULL && p2 == NULL)
            {
                printf("Semantic Error on line %d. Variable '%s' not declared.\n", n->child->child->child->tree_node->line, n->child->child->child->tree_node->lexeme);
                hasSemanticError = true;
            }
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
                printf("Semantic Error at line %d. Function %s not defined before use.\n", n->child->sibling->tree_node->line, n->child->sibling->tree_node->lexeme);
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
        astNode *d;
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

    if (is(n, "otherModules") && n->sibling != NULL)
    {
        for (astNode *m = n->child; m; m = m->sibling)
        {
            PARAMS *p1 = create_param(m->child->sibling->child);
            PARAMS *p2 = create_param(m->child->sibling->sibling->child);
            // printf("aaya2\n");
            ID_SYMBOL_TABLE *id_st = create_id_st(NULL);
            st_insert_func_entry(create_function(m->child, p1, p2, id_st), st);
            traverse_the_universe(m->child->sibling->sibling->sibling, id_st);
        }
    }

    if (is(n, "driverModule"))
    {
        ID_SYMBOL_TABLE *id_st = create_id_st(NULL);
        FUNC_TABLE_ENTRY *fnew = create_function(NULL, NULL, NULL, id_st);
        st_insert_func_entry(fnew, st);
        // printf("mil\n");
        traverse_the_universe(n->child, id_st);
        // printf("gaya\n");
    }
    if (is(n, "otherModules") && n->sibling == NULL)
    {
        for (astNode *m = n->child; m; m = m->sibling)
        {
            PARAMS *p1 = create_param(m->child->sibling->child);
            // printf("aaya2\n");
            PARAMS *p2;
            if (m->child->sibling->sibling->child->node_marker == EPS)  // no output
                p2 = NULL;
            else
                p2 = create_param(m->child->sibling->sibling->child);
            ID_SYMBOL_TABLE *id_st = create_id_st(NULL);
            st_insert_func_entry(create_function(m->child, p1, p2, id_st), st);
            traverse_the_universe(m->child->sibling->sibling->sibling, id_st);
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
    TYPE *t = new->datatype;
    astNode *temp = plist->child->sibling->child;       // rangeArr
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
        t->arrtype->begin_offset = current_offset++;            // in any case, 
        t->arrtype->end_offset   = current_offset++;            // fill the offsets
    }
    new->is_assigned = false;
    if (plist->sibling)
        new->next = create_param(plist->sibling);
    else
        new->next = NULL;
    return new;
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
        printf("%s : %s, ",pn, ty);
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
    ID_TABLE_ENTRY *temp;
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