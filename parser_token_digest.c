static void parser_token_digest(Token t,FILE *out){
    switch (t.tipo) {

        case TOK_NUMERO:            
            fprintf( out, "PUSH(%f);\n", t.valore.numero);
            //fprintf( out, "stack_push( v, %f );\n", t.valore.numero);
            break;

        case TOK_COMANDO:
            fprintf( out,  "%s(v);\n", words[ t.valore.cmd ] );
            break;
  
/*
        case TOK_STRINGA:
            printf("STRINGA  : \"");
            string_print(t.valore.stringa);
            printf("\" (len=%zu)\n",
                   string_len(t.valore.stringa));
            break;

        case TOK_COMMENTO:
            printf("COMMENTO : ");
            string_print(t.valore.stringa);
            putchar('\n');
            break;

        case TOK_FINE:
            puts("FINE");
            break;

        case TOK_ERRORE:
            puts("ERRORE DI PARSING");
            break;
*/        
    }
}