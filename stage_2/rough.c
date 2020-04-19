astNode *lhs = n->child;
        astNode *rhs = n->child->sibling;
       if (lhs->node_marker == ARRAY || (lhs->node_marker == var && lhs->child->sibling != NULL))
        {
            // first do a non-recursive lookup
            ID_TABLE_ENTRY *i = st_lookup(ex->child->tree_node->lexeme, id_st);
            int line = ex->child->sibling->tree_node->line;
            int base_offset, start_offset, end_offset, index, index_offset;

            if (i == NULL) printf("GOTYA\n");
            PARAMS *p = NULL;

            // calculating offsets of arrays
            if (i == NULL)      // then check for parameters
            {
                p = param_lookup(id_st->primogenitor->in_params ,ex->child->tree_node->lexeme);
                if (p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params ,ex->child->tree_node->lexeme);
                
                base_offset = p->offset - 26;
                start_offset = p->datatype->arrtype->begin_offset - 26;
                end_offset = p->datatype->arrtype->end_offset - 26;
            }

            else
            {
                printf("inside not function index\n");
                base_offset = i->offset;
                start_offset = i->datatype->arrtype->begin_offset;
                end_offset = i->datatype->arrtype->end_offset;
            }

            // A[2]
            if(ex->child->sibling->node_marker != ID)
            {
                index = atoi(ex->child->sibling->tree_node->lexeme);
                printf("index xxxxxxxxxx %d\n", index);
                fprintf(fp, "\tpush rcx\n\tpush rcx\n");
                bound_check(fp, start_offset, end_offset, index, line);
                fprintf(fp, "\tpop rcx\n\tpop rcx\n");
                fprintf(fp, "\txor rax, rax\n");
                fprintf(fp, "\txor rdx, rdx\n");
                fprintf(fp, "\tmov rax, [rbp - %d]\n", base_offset * 8);
                fprintf(fp, "\tmov rdx, [rbp - %d]\n", start_offset * 8);
                fprintf(fp, "\txor rbx, rbx\n");
                fprintf(fp, "\tmov ebx, %d\n", index);
                fprintf(fp, "\tsub ebx, edx\n");
                fprintf(fp, "\tmov [rax + rbx * 8], rcx \n");

                return;
            }
            
             // A[k]

            else
            {
                ID_TABLE_ENTRY* index_entry = st_lookup(ex->child->sibling->tree_node->lexeme, id_st);
                    
                if(index_entry != NULL)
                {
                    index_offset = index_entry->offset;
                }
                else
                {
                    PARAMS* p = param_lookup(id_st->primogenitor->in_params ,ex->child->sibling->tree_node->lexeme);
                    if (p == NULL)
                        p = param_lookup(id_st->primogenitor->out_params ,ex->child->sibling->tree_node->lexeme);
                    
                    index_offset = p->offset - 26;
                }
                
                bound_check_dynamic(fp, start_offset, end_offset, index_offset, line);
                fprintf(fp, "\txor rax, rax\n");
                fprintf(fp, "\txor rdx, rdx\n");
                fprintf(fp, "\tmov eax, [rbp - %d]\n", base_offset * 8);
                fprintf(fp, "\tmov edx, [rbp - %d]\n", start_offset * 8);
                fprintf(fp, "\tmov ebx, [rbp - %d]\n", index_offset * 8);
                fprintf(fp, "\tsub ebx, edx\n");
                fprintf(fp, "\tmov [rax + rbx * 8], rcx\n");
                return;
            }   
                
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
        