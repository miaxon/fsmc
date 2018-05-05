
#include <stdlib.h>
#include <stdio.h>
#include "fsm.h"
void print_nodes(fsm *o)
{
    fsm_node *tmp = o->base;
    while(tmp)
    {
        strstate(tmp->state);
        tmp = tmp->next;
    }
}
void strstate(fsm_state state)
{
    switch(state)
    {
        case INIT:
            printf("INIT\n");
        break;
        case BEGIN:
            printf("BEGIN\n");
        break;
        case DATA:
            printf("DATA\n");
        break;
        case END:
            printf("END\n");
        break;
    }
}

int fsm_new(fsm *o, fsm_state state, void (*fun)(fsm *, int, void **), int argc, void** argv)
{
    o->base = calloc(1, sizeof *(o->node));
    o->base->state = state;
    o->base->function = fun;
    o->base->next = NULL;
    o->node = o->base;
    o->arg_num = argc;
    o->arg_value = argv;
    return 0;
}

int fsm_node_next(fsm *o)
{
    o->node->function(o, o->arg_num, o->arg_value);
    if (o->node->next != NULL)
        o->node = o->node->next;
    else
        return -1;
    return 0;
}

int fsm_run(fsm *o)
{
    while (!fsm_node_next(o));
    return 0;
}

int fsm_node_exists(fsm *o, fsm_state state)
{
    fsm_node *tmp = o->base;  
    while(tmp)
    {
        if(tmp->state == state)
            return -1;
        tmp = tmp->next;    
    }
    return 0;
}

int fsm_node_add(fsm *o, fsm_state state, void (*fun)(fsm *, int, void **) )
{
    if(fsm_node_exists(o, state) != 0)
        return -1;
    
    fsm_node *tmp = o->base;
    while(tmp->next)
        tmp = tmp->next;  
    
    fsm_node *new_node = calloc(1, sizeof *new_node);
    new_node->state = state;
    new_node->function = fun;
    new_node->next = NULL;
    tmp->next = new_node;
    return 0;
}

int fsm_node_remove(fsm *o, fsm_state state)
{
    if (state == INIT)
        return -1;
    fsm_node *prev;
    fsm_node *tmp = o->base;
    while(tmp)
    {
        if(tmp->state == state)
        {
            prev->next = tmp->next;
            free(tmp);
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return 0;
}

int fsm_transition(fsm *o, fsm_state state, int num, void** arg)
{
    fsm_node *tmp = o->base;
    while((tmp->state != state))
        tmp=tmp->next;
    if (tmp == NULL)
        return -1;
    o->node = tmp;
    o->arg_num = num;
    o->arg_value = arg;
    o->node->function(o, num, arg);
    return 0;
}

int fsm_default(fsm *o, void (*fun)(fsm *, int, void **) )
{
    o->base = calloc(1, sizeof *(o->node));
    o->base->state = INIT;
    o->base->function = fun;
    o->base->next = NULL;
    o->node = o->base;
    return 0;
}

void fsm_exit(fsm *obj)
{
    // delete all states to prevent memory leek
    fsm_node *tmp = obj->base;
    fsm_node *to_del = tmp;
    while(tmp)
    {
        to_del = tmp;
        tmp = tmp->next;
        free(to_del);
    }
    obj->node = NULL;
    obj->node = NULL;
}