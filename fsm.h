
typedef struct fsm fsm;
typedef struct fsm_node fsm_node;

typedef enum fsm_state {
    INIT, BEGIN, DATA, END
}fsm_state;

typedef struct fsm_node{
    fsm_state state;
    
    void (*function)(fsm* o, int c, void** v);
    
    fsm_node *next;
    
}fsm_node; 


typedef struct fsm{

    fsm_node *base;

    fsm_node *node;
    
    int arg_num;
    
    void **arg_value;
} fsm;

int fsm_new(fsm *obj, fsm_state state, void (*fun)(fsm *, int, void **), int argc, void** argv);

int fsm_run(fsm *obj);

int fsm_node_exists(fsm *obj, fsm_state state);

int fsm_node_next(fsm *obj);

int fsm_node_add(fsm *obj, fsm_state st, void (*fun)(fsm *o, int c, void ** v) );

int fsm_node_remove(fsm *obj, fsm_state st);

int fsm_transition(fsm *o, fsm_state st, int num, void** arg);

void fsm_exit(fsm *obj);

void strstate(fsm_state state);

void print_nodes(fsm *obj);