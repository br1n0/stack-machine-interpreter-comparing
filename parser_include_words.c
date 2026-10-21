//genera l'include words
// #include "Opcode_enum.c"
void parser_include_words(){
    printf("%s\n","parser_include_words RUNNING" );
    FILE *out = fopen( "transpiled_words_used.c", "w+");
    fprintf( out ,"\n//-----\n" );
    for( size_t i= 0; i<nwords; i++ ){
        if( used[i] )
                //fprintf(out, "    word_%s();\n", cname);
                fprintf( out ,"#include \"words/%s.c\"\n" , words[i] );
    }
    fprintf( out ,"\n//-----\n" );
    fclose(out);
}