# Stack Machine Interpreter Benchmark
mi domandavo quale fosse l'implementazione piu performante per un interprete tipo una stack machine.
Percui questo benchmark misurare le differenze, e compilando con gcc ad ottimizzazioni differenti.
native_function_init serve a misurare l'inizzializzazione dei dati,
mentre native_function_call serve a misurare l'esecuzione del codice nativo tramite funzioni.
native_baseline serve a stimare il tempo di calcolo, per stimare quanto il compilatore riesce a ottimizzare un elaborazione se espressa in maniera idiomatica in c.
al massimo dell'e ottimizzazioni il compilatore gcc riesce a semplificare l'elaborazione di native_baseline, impiega 0 secondi, ma non ci riesce se espresso tramite un elaborazione di funzioni sullo stack! infatti native_function_call utilizza le stesse funzioni di i_TTC_dispatch_function_table o i_DCT_dispatch_function_call ma senza l'interprete ed impiega 2.03s. 

## Modelli di interpretazione
Ho cercato di assegnare alle implementazioni nomi descrittivi, che permettano di identificare:
i_ oppure native_: esecuzione interpretata o nativa.
Il threading model: TTC oppure DCT.
Il dispatch mechanism: computed_goto, switch, if, function_table oppure function_call.
La terminologia prende spunto dai modelli di esecuzione storicamente studiati nell'ambito del linguaggio Forth.

### TTC
TTC sta per Token Threaded Code, ovvero le istruzioni dell'interprete nel bytecode sono codificate mediante numeri. 
questa rappresentazione ha il vantaggio di essere compatta,di essere indipendente da locazione memoria dell'implementazione delle istruzioni.
Consente modificare l'implementazione di un'istruzione senza modificare il programma compilato, 
percui é facile implementare funzionalitá avanzate come l'hotswap di una funzione, ovvero modificare l'implementazione di un programma a runtime, 
puo permettere di caricare dinamicamente l'implementazione dei comandi/funzioni da una libreria dinamica!


### DCT
DCT sta per Direct Call Threading, nella viene chiamato anche Direct Threading,
in questo modo i comandi nel bytecode sono espressi come puntatori alle funzioni. il Vantaggio é che l'interprete non ha necessitá della di una tavola conversioni funzioni, si limita ad eseguire quello che gli é indicato.


## Risultati del benchmark

I migliori tempi misurati sul mio portatilaccio sono i seguenti:

| Implementazione | Tempo (s) |
|---|---:|
| `i_TTC_dispatch_computed_goto` | 2.52 |
| `i_TTC_dispatch_switch` | 2.53 |
| `i_TTC_dispatch_if` | 2.52 |
| **`i_TTC_dispatch_function_table`** | **2.53** |
| `i_DCT_dispatch_function_call` | 2.66 |
| `native_function_init` | 0.00 |
| `native_function_call` | 2.03 |
| `native_baseline` | 0.00 |


I tempi con differenti impostazioni di compilazione sono in results.txt


### Considerazioni su implementazioni e prestazioni
l'implementazione di interpreti tramite TTC risulta semplice specie la versione con switch, ma necessita adattamenti all'interpete aggiungendo o togliendo un comando dal linguaggio. 
il TTC non utilizzando direttamente un simbolo per identificare i comandi, consente di ridefinirli senza modificare il bytecode, percui é facile implementare funzionalitá avanzate come l'hotswap di una funzione, ovvero modificare l'implementazione di un programma a runtime o caricare l'implementazione dei comandi/funzioni da una libreria dinamica!
Le implementazioni i_TTC_dispatch_function_table e i_DCT_dispatch_function_call eseguono le funzioni, le potrebbero condividere in un file esterno.
l'implementazione con i_DCT_dispatch_function_call non necessita di un elenco funzioni, ma risulta la piu lenta, mentre quando ottimizzata dal compilatore la i_TTC_dispatch_function_table é la piú veloce.
Percui i_TTC_dispatch_function_table mi sembra il modo migliore per scrivere un interprete basato su stack.



Struttura Dati
VM é la struttura dati principale dell'interprete. 
Contiene lo stato di esecuzione, lo stack dei dati e il programma.

La struttura è condivisa dalle diverse implementazioni, 
mentre cambiano il tipo `Opcode` e il meccanismo di dispatch adottato dalla funzione `exec()`.
In questo modo il programma da eseguire é espresso allo stesso modo, ma viene codificato dal compilatore c in modi diversi.

```c
struct VM {
    uint16_t sp;              // stack pointer
    uint16_t pc;              // program counter
    uint16_t code_size;       // program size
    double stack[ STACK_MAX ];// data stack
    Opcode code[ OPCODE_MAX ];// program
};
```

Opcode invece nelle implementazioni TTC é definito come enum:

```c
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
```

mentre nella implementazione i_DCT_dispatch_function_call
contiene il puntatore della funzione da eseguire
```c
typedef void (*Opcode)(VM *vm);
```


## Riferimenti

- [Anton Ertl — Threaded Code](https://www.complang.tuwien.ac.at/forth/threaded-code.html)
- [Gforth — Threading](https://gforth.org/manual/Threading.html)
- [GCC — Labels as Values](https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html)
