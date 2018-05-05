#include<stdio.h>
#include "fsm.h"

void init(fsm *o, int val, void **arg)
{
    printf("%d ",val);
    strstate(o->node->state);
    //fsm_transition(o, DATA, 10, NULL);
}

void begin(fsm *o, int val,void **arg)
{
    printf("%d ",val);
    strstate(o->node->state);
    o->arg_num = 1;
    //fsm_transition(o, DATA, 2, NULL);
}


void data(fsm *o, int val,void **arg)
{
    // state -> hello
    printf("%d ",val);
    strstate(o->node->state);
    //fsm_transition(o, END, 3, NULL);
}

void end(fsm *o, int val, void **arg)
{
    printf("%d ",val);
    strstate(o->node->state);
    //fsm_transition(o, INIT, 0, NULL);
}


int main()
{
    struct fsm o;
    fsm_new(&o, INIT, init, 0, NULL); 
    fsm_node_add(&o, BEGIN, begin);
    fsm_node_add(&o, DATA, data);
    fsm_node_add(&o, DATA, data);    
    fsm_node_add(&o, END, end);
    print_nodes(&o);
    fsm_node_remove(&o, DATA);
    print_nodes(&o);
    fsm_run(&o);
    return 0;
}