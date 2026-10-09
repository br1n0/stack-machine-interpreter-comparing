mi domandavo quale fosse l'implementazione piu performante per un interprete tipo una stack machine.
Percui questo benchmark misurare le differenze, e compilando con gcc ad ottimizzazioni differenti.
native_function_init serve a misurare l'inizzializzazione dei dati,
mentre native_function_call serve a misurare l'esecuzione del codice nativo tramite funzioni 

Ho cercato assegnare nomi parlanti alle implementazioni, indicano se nativo o interprete, il loro threading model (TTC o DCT), ed il relativo dispatch model (goto,switch,if,function table,function call).
Utilizzo i nomi del threading model del forth che ne ha sperimentato differenti implementazioni.
TTC sta per Token Threaded Code, ovvero i comandi nel bytecode sono codificato con numeri corrispondenti a comandi dell'interpete. 
Il vantaggio é che é indipendente da locazione memoria e questa rappresentazione occupa poco spazio.

DCT sta per Direct Call Threading, nella viene chiamato anche Direct Threading,
in questo modo i comandi nel bytecode sono espressi come puntatori alle funzioni. il Vantaggio é che l'interprete non ha necessitá della di una tavola conversioni funzioni, si limita ad eseguire quello che gli é indicato.
la versione tramite DCT é la piu lenta, le altre hanno velocitá simili, i tempi migliori (in secondi) sul mio portatilaccio sono:
2.56 i_TTC_dispatch_computed_goto
2.58 i_TTC_dispatch_switch
2.57 i_TTC_dispatch_if
2.49 i_TTC_dispatch_function_table
2.65 i_DCT_dispatch_function_call
2.05 native_function_call
0.00 native_function_init

I tempi completi sono in results.txt


commenti implementazioni
l'implementazione di interpreti tramite TTC risulta semplice specie la versione con switch, ma necessita adattamenti all'interpete aggiungendo o togliendo un comando dal linguaggio. 
il TTC non utilizzando direttamente un simbolo per identificare i comandi, consente di ridefinirli senza modificare il bytecode, percui é facile implementare funzionalitá avanzate come l'hotswap di una funzione, ovvero modificare l'implementazione di un programma a runtime o caricare l'implementazione dei comandi/funzioni da una libreria dinamica!
Le implementazioni i_TTC_dispatch_function_table e i_DCT_dispatch_function_call eseguono le funzioni, le potrebbero condividere in un file esterno.
l'implementazione con i_DCT_dispatch_function_call non necessita di un elenco funzioni, ma risulta la piu lenta, mentre quando ottimizzata dal compilatore la i_TTC_dispatch_function_table é la piú veloce.
Percui i_TTC_dispatch_function_table é il modo migliore per scrivere un interprete basato su stack.



Struttura Dati
VM é la struttura dati principale dell'interprete. 
Permette di variare le implementazioni senza modificare l'eseguibile:
il dispatch varia a seconda dell'implementazione della funzione exec.

struct VM {
    uint16_t sp;              // stack pointer
    uint16_t pc;              // program counter
    uint16_t code_size;       // program size
    double stack[ STACK_MAX ];// data stack
    Opcode code[ OPCODE_MAX ];// program
};


Opcode invece nelle implementazioni TTC é definito come enum:

Opcode_enum.c lo definisce come un enumerazione:
typedef enum{
    OP_NOP,
    OP_RETURN,    
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_SIN,
    OP_COS,
    OPCODE_COUNT
} Opcode;

mentre nella implementazione i_DCT_dispatch_function_call
contiene il puntatore della funzione da eseguire
typedef void (*Opcode)(VM *vm);

