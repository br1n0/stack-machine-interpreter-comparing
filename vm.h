#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stddef.h>
#include <dlfcn.h>
#include "Opcode_enum.c"

#define STACK_MAX 2*1024
#define OPCODE_MAX 2*1024
#define EXPORT __attribute__((visibility("default")))

typedef struct VM VM;

typedef void (*OpcodeFn)(VM *);

struct VM {
    uint16_t sp;
    uint16_t pc;
    uint16_t code_size;
    void *handle;

    double stack[STACK_MAX];
    Opcode code[OPCODE_MAX];

    OpcodeFn table[OPCODE_COUNT];
};


typedef struct {
    unsigned int version;
    unsigned int size;
    
    OpcodeFn table[];

} VM_API;


static inline __attribute__((always_inline))
double stack_pop(VM *vm){
    double d= vm->stack[--vm->sp];
    return d;
}

static inline __attribute__((always_inline))
void stack_push(VM *vm, double x){
    vm->stack[vm->sp++] = x;    
}



int hot_reload(VM *vm){
    if( vm->handle != NULL ) dlclose( vm->handle ); //if a lib is used, close

    vm->handle = dlopen( "./vm_shared.so", RTLD_NOW | RTLD_LOCAL );
    if( vm->handle == NULL ) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    dlerror();

    const VM_API *api = (const VM_API *)dlsym( vm->handle, "vm_api" );
    const char *err = dlerror();

    if (err != NULL || api == NULL) {
        fprintf(stderr, "vm_api non disponibile\n");
        dlclose(vm->handle);
        return 1;
    }

    //printf("Version: %d\n", api->version);
    //printf("Size: %d\n", api->size);

    for(int i=0;i<api->size;i++)
        vm->table[ (Opcode)i ] = api->table[i] ;

    return 0;
}


double exec(VM *vm){
    while (vm->pc < vm->code_size) {
        Opcode op = vm->code[vm->pc++];
        ( vm->table[op] )( vm );
    }
    //return vm->stack[0];
    return vm->stack[vm->sp-1];
}
