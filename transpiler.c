#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

size_t nwords = 0;
char **words = NULL;
unsigned char *used= NULL;

#include "load_primitives.c"
#include "tokenizer.c"
#include "parser_include_words.c"
#include "parser_token_digest.c"


/*

Single pass transpiler, 
to transpile a program in a stack language into native executable.
build the transpiler, then run transpiler against program.

the transpiler expect in argv[1] the filename of program in stack language, it compile into transpiled_main.c 

how transpiler works:
Load the primitives available.
tokenize the code, and  each token is processed on single pass: 
emit a push for number or write a function call for a primitive function, written in transpiled_main.c.

Later the parser_include_words write only the primitives that are used into transpiled_words_used.c", to make gcc happy.

transpiled_main.c contain run that is the function to run the code,
this way it is I included on native_transpiled_run1.c and native_transpiled_run400k.c
to be runned 1times and 400k times.

the program source code is loaded trough mmap.
the only allocated memory are words,used.  Both are not disposed, the os will do.

*/

int main(int argc, char *argv[]){
    int risultato = EXIT_SUCCESS;

    //cerchiamo le words definite in words/*.c
    load_primitives();

    if (argc != 2) {
        fprintf(stderr,
                "Uso: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    struct stat st;

    if (fstat(fd, &st) < 0) {
        perror("fstat");
        close(fd);
        return EXIT_FAILURE;
    }

    if (!S_ISREG(st.st_mode) || st.st_size < 0 ||
        (uintmax_t)st.st_size > SIZE_MAX) {
        fprintf(stderr, "File non supportato\n");
        close(fd);
        return EXIT_FAILURE;
    }

    if (st.st_size == 0) {
        puts("File vuoto");
        close(fd);
        return EXIT_SUCCESS;
    }

    size_t size = (size_t)st.st_size;

    void *data = mmap( NULL, size, PROT_READ, MAP_PRIVATE, fd, 0 );
    if (data == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);

    Parser parser;
    tokenizer_init(&parser, data, size);


    // generate transpiled: HEADER
    FILE *out = fopen( "transpiled_main.c", "w+");
    
    fprintf( out, "#include \"./vm.h\"\n\
#include \"./transpiled_words_used.c\"\n\
\n\
#define PUSH(x) stack_push(v, (x)) \n\
#define POP()   stack_pop(v)       \n\
\n\
int run(void) {\n\
    VM vm = {0};\n\
    VM *v = &vm;\n\
    vm.pc= 0;\
    vm.sp= 0;\
");


    // generate transpiled: BODY
    for (;;) {
        Token t = tokenizer_next(&parser);
        parser_token_digest(t,out);

        if (t.tipo == TOK_FINE)
            break;

        if (t.tipo == TOK_ERRORE) {
            risultato = EXIT_FAILURE;
            break;
        }
    }

    // generate transpiled: FOOTER
    fprintf( out, "\n}" );
    fclose(out);

    if (munmap(data, size) < 0) {
        perror("munmap");
        risultato = EXIT_FAILURE;
    }


    //some stats: primitive used
    printf("\n\nPRIMITIVE STATS:\n");
    for (size_t i = 0; i < nwords; i++){
            printf("used:%d ", used[i]);
            printf("word:%s\n", words[i]);
    }

    //write the transpiled_words_used
    parser_include_words();

    return 0;
}
