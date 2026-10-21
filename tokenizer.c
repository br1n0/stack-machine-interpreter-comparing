
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MAX_NUMBER_LEN 128
char tmp[64]="";


// String: intervallo [pos, end)
typedef struct {
    const char *pos;
    const char *end;
} String;

typedef String Parser;

static size_t string_len(String s){
    return (size_t)(s.end - s.pos);
}


static bool string_empty(String s){
    return s.pos == s.end;
}


static bool string_equal(String s, const char *str){
    size_t len = strlen(str);

    return string_len(s) == len &&
           memcmp(s.pos, str, len) == 0;
}


static void string_print(String s){
    fwrite(s.pos, 1, string_len(s), stdout);
}


void String_to_cstring(String s){
    int len= s.end-s.pos;
    memcpy( tmp, s.pos, len ) == 0;
    tmp[len]= 0;
}

typedef int command_id;
#define CMD_NONE -1


command_id command_find(String s){
    String_to_cstring(s);
    for( size_t i = 0; i < nwords; i++ )
        if( string_equal( s, words[i] ) ){
            used[i]= 1;
            return i;
        }
    return CMD_NONE;
}


// Token: tagged union
typedef enum {
    TOK_FINE,
    TOK_NUMERO,
    TOK_COMANDO,
    TOK_STRINGA,
    TOK_COMMENTO,
    TOK_ERRORE
} TipoToken;

typedef struct {
    TipoToken tipo;

    union {
        double numero;
        command_id cmd;
        String stringa;
    } valore;

} Token;



// Parser
static void tokenizer_init( Parser *p, const void *data, size_t size ){
    p->pos = (const char *)data;
    p->end = p->pos + size;
}


static void tokenizer_skip_spaces(Parser *p){
    while (!string_empty(*p) &&
           isspace((unsigned char)*p->pos)) {
        p->pos++;
    }
}


// Convert a String into double.
// strtod richiede una stringa NUL terminata, usa un buffer temporaneo.
static bool tokenizer_number(String s, double *result){
    size_t len = string_len(s);

    if (len == 0 || len > MAX_NUMBER_LEN)
        return false;

    char buf[MAX_NUMBER_LEN + 1];

    memcpy(buf, s.pos, len);
    buf[len] = '\0';

    char *fine;

    errno = 0;
    double n = strtod(buf, &fine);

    if (fine == buf || *fine != '\0')
        return false;

    if (errno == ERANGE || !isfinite(n))
        return false;

    *result = n;
    return true;
}


static Token tokenizer_next(Parser *p){
    Token t = {0};

    tokenizer_skip_spaces(p);

    if (string_empty(*p)) {
        t.tipo = TOK_FINE;
        return t;
    }


    // to handle  Comment // till newline
    if (p->end - p->pos >= 2 &&
        p->pos[0] == '/' &&
        p->pos[1] == '/') {

        const char *inizio = p->pos;

        p->pos += 2;

        while (p->pos < p->end &&
               *p->pos != '\n') {
            p->pos++;
        }

        t.tipo = TOK_COMMENTO;
        t.valore.stringa = (String) {
            .pos = inizio,
            .end = p->pos
        };

        return t;
    }


    // to handle Strings between "
    if (*p->pos == '"') {

        p->pos++;  // salta " iniziale

        const char *inizio = p->pos;

        while (p->pos < p->end &&
               *p->pos != '"') {
            p->pos++;
        }

        if (p->pos == p->end) {
            t.tipo = TOK_ERRORE;
            return t;
        }

        String s = {
            .pos = inizio,
            .end = p->pos
        };

        p->pos++;  // salta " finale

        if (p->pos < p->end &&
            !isspace((unsigned char)*p->pos)) {
            t.tipo = TOK_ERRORE;
            return t;
        }

        t.tipo = TOK_STRINGA;
        t.valore.stringa = s;

        return t;
    }


    // to handle  Token ordinary
    const char *inizio = p->pos;

    while (p->pos < p->end && !isspace((unsigned char)*p->pos)) {
        p->pos++;
    }

    String s = {
        .pos = inizio,
        .end = p->pos
    };

    // Command
    command_id cmd = command_find(s);

    if (cmd != CMD_NONE) {
        t.tipo = TOK_COMANDO;
        t.valore.cmd = cmd;
        return t;
    }


    // to handle  Number 
    double numero;

    if (tokenizer_number(s, &numero)) {
        t.tipo = TOK_NUMERO;
        t.valore.numero = numero;
        return t;
    }


    // to handle  String free
    t.tipo = TOK_STRINGA;
    t.valore.stringa = s;

    return t;
}
