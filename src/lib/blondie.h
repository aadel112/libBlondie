#include "blondie_magic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>

#define INIT 1
#define NOT_INIT 0
#define ARRMAX 32768
// #define ARRMAX 1048576
#define MSTR 100000
#define SHORTSTR 1024
#define CRCLEN 15
#define MARGSTR 5
#define DELIM @
#define DEF 1

#define die(); exit(1);
#define blondie __f.fvar[fcrc]
#define tvar v_t_INT_BLONDIE
#define fvar fun_t_INT_BLONDIE
#define str(a) #a

#define EMPTYSTR ""
#define STR(s) str(s)
#define SEXPAND(a) str(TEXPAND(a))
#define TEXPAND(a) CAT( __, a )
#define __$P(...)  __VA_ARGS__
#define EVAL(...) __VA_ARGS__
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
#define STRMOD(x) STR(%s)
#define PCTX(x) %x
#define COMMA() ,
#define EMPTY() 
#define DEFER(x) x EMPTY()
#define COMMAFY(x) CAT(x, COMMA)
#define EVAL_MOD(x) PCTX( MOD(x) )
#define TYPE_OF_COMMA(t) type_of(t) 

#define MOD( v ) _Generic((v), \
_Bool: STR(d),  unsigned char: STR(c),  \
char: STR(c),   signed char: STR(c),  \
short int: STR(d),  unsigned short int: STR(d),  \
int: STR(d),  unsigned int: STR(d),  \
long int: STR(ld),  unsigned long int: STR(ld),  \
long long int: STR(ld),  unsigned long long int: STR(ld),  \
float: STR(f),  double: STR(f),  \
long double: STR(lf),  char *: STR(s),  \
void *: STR(x),  int *: STR(d),  \
default: STR(x))

/* http://stackoverflow.com/questions/6280055/how-do-i-check-if-a-variable-is-of-a-certain-type-compare-two-types-in-c */
#define type_of(x) _Generic((x),                                                 \
_Bool: t_BOOL,                  unsigned char: t_UNSIGNED_CHAR,          \
        char: t_CHAR,                   signed char: t_SIGNED_CHAR,            \
        short int: t_SHORT_INT,         unsigned short int: t_UNSIGNED_SHORT_INT,     \
        int: t_INT,                     unsigned int: t_UNSIGNED_INT,      \
        long int: t_LONG_INT,           unsigned long int: t_UNSIGNED_LONG_INT,    \
        long long int: t_LONG_LONG_INT, unsigned long long int: t_UNSIGNED_LONG_LONG_INT, \
        float: t_FLOAT,                 double: t_DOUBLE,                 \
        long double: t_LONG_DOUBLE,     char *: t_POINTER_TO_CHAR,        \
        void *: t_POINTER_TO_VOID,      int *: t_POINTER_TO_INT,         \
        default: t_OTHER)

enum t_typename {
    t_BOOL,
    t_UNSIGNED_CHAR,
    t_CHAR,
    t_SIGNED_CHAR,
    t_SHORT_INT,
    t_UNSIGNED_SHORT_INT,
    t_INT,
    t_UNSIGNED_INT,
    t_LONG_INT,	
    t_UNSIGNED_LONG_INT,
    t_LONG_LONG_INT,
    t_UNSIGNED_LONG_LONG_INT,
    t_FLOAT,
    t_DOUBLE,  
    t_LONG_DOUBLE,   
    t_POINTER_TO_CHAR,
    t_POINTER_TO_VOID,
    t_POINTER_TO_INT,
    t_OTHER
} generic;


#define BlondieMemoize(r, n, b, tps, args...) \
    r CAT( __, n )( CAT( __, tps) ); \
    r CAT( __, n )( CAT( __, tps) ) b \
\
    r n( CAT(__, tps) ) { \
        char key[MSTR]; \
        FOR_EACH(SETMOD, args) \
        char fmt[MSTR]; \
        sprintf(fmt, FOR_EACH(STRMOD, args)  FOR_EACH(MODARGNAMECOMMA, args)); \
        sprintf(key, fmt, args); \
        int fcrc = BlondieCrc(#n); \
        int crc = BlondieCrc(key); \
        strncpy(__f.function_name[fcrc], #n, strlen(#n) > SHORTSTR ? SHORTSTR : strlen(#n) ); \
        __f.type[fcrc] = type_of( n ); \
        setfvar(fcrc); \
        setvar(fcrc); \
\
        if( is_value_stored(crc) && !strcmp(__h.key_string[crc], key) ) { \
            return __h.tvar[crc]; \
        } else { \
            strncpy(__h.key_string[crc], key, strlen(key)> SHORTSTR ? SHORTSTR : strlen(key) ); \
            __h.is_stored[crc] = DEF; \
            __h.tvar[crc] = CAT( __, n )( args ); \
            return __h.tvar[crc]; \
        } \
    } 

#define BlondieCrc( a ) getCRC( a, strlen(a) )
#define GETMOD( v ) MOD(v)  

// #define DOUBLE_QUOTE "
#define UNDEF(x) CAT(__undef x)
#define DEF_X_IN_TERMS_OF(x, y) CAT(__define x  y)

#define SWAP(a, b) { \
    (a) ^= (b); \
    (b) ^= (a); \
    (a) ^= (b); \
}

#define MODARGNAME(arg)  CAT(__ARG, arg)  
#define MODARGNAMECOMMA(arg) , CAT(__ARG, arg) 

#define SETMOD(a)  char MODARGNAME(a)[MARGSTR]; sprintf(MODARGNAME(a), "%s", getMod(TYPE_OF_COMMA(a)));

long getCRC(char message[], int length);
int get_crc( char* f, ... );
int get_fcrc( char * f );
int is_value_stored( int crc );
void setfvar(int);
void setvar(int);
char* getMod(enum t_typename t);

typedef struct SimpleFunctionHash {
    enum t_typename type[ARRMAX];
    char function_name[ARRMAX][SHORTSTR];

    _Bool (*fun_t_BOOL_BLONDIE[ARRMAX])();
    unsigned char (*fun_t_UNSIGNED_CHAR_BLONDIE[ARRMAX])();
    char (*fun_t_CHAR_BLONDIE[ARRMAX])();
    signed char (*fun_t_SIGNED_CHAR_BLONDIE[ARRMAX])();
    short int (*fun_t_SHORT_INT_BLONDIE[ARRMAX])();
    unsigned short int (*fun_t_UNSIGNED_SHORT_INT_BLONDIE[ARRMAX])();
    int (*fun_t_INT_BLONDIE[ARRMAX])();
    unsigned int (*fun_t_UNSIGNED_INT_BLONDIE[ARRMAX])();
    long int (*fun_t_LONG_INT_BLONDIE[ARRMAX])();
    unsigned long int (*fun_t_UNSIGNED_LONG_INT_BLONDIE[ARRMAX])();
    long long int (*fun_t_LONG_LONG_INT_BLONDIE[ARRMAX])();
    unsigned long long int (*fun_t_UNSIGNED_LONG_LONG_INT_BLONDIE[ARRMAX])();
    float (*fun_t_FLOAT_BLONDIE[ARRMAX])();
    double (*fun_t_DOUBLE_BLONDIE[ARRMAX])();
    long double (*fun_t_LONG_DOUBLE_BLONDIE[ARRMAX])();
    char* (*fun_t_POINTER_TO_CHAR_BLONDIE[ARRMAX])();
    void* (*fun_t_POINTER_TO_VOID_BLONDIE[ARRMAX])();
    int* (*fun_t_POINTER_TO_INT_BLONDIE[ARRMAX])();
} simple_function_hash;

typedef struct SimpleValueHash {
    int is_stored[ARRMAX];
    char key_string[ARRMAX][SHORTSTR];

    _Bool v_t_BOOL_BLONDIE[ARRMAX];
    unsigned char v_t_UNSIGNED_CHAR_BLONDIE[ARRMAX];
    char v_t_CHAR_BLONDIE[ARRMAX];
    signed char v_t_SIGNED_CHAR_BLONDIE[ARRMAX];
    short int v_t_SHORT_INT_BLONDIE[ARRMAX];
    unsigned short int v_t_UNSIGNED_SHORT_INT_BLONDIE[ARRMAX];
    int v_t_INT_BLONDIE[ARRMAX];
    unsigned int v_t_UNSIGNED_INT_BLONDIE[ARRMAX];
    long int v_t_LONG_INT_BLONDIE[ARRMAX];
    unsigned long int v_t_UNSIGNED_LONG_INT_BLONDIE[ARRMAX];
    long long int v_t_LONG_LONG_INT_BLONDIE[ARRMAX];
    unsigned long long int v_t_UNSIGNED_LONG_LONG_INT_BLONDIE[ARRMAX];
    float v_t_FLOAT_BLONDIE[ARRMAX];
    double v_t_DOUBLE_BLONDIE[ARRMAX];
    long double v_t_LONG_DOUBLE_BLONDIE[ARRMAX];
    char* v_t_POINTER_TO_CHAR_BLONDIE[ARRMAX];
    void* v_t_POINTER_TO_VOID_BLONDIE[ARRMAX];
    int* v_t_POINTER_TO_INT_BLONDIE[ARRMAX];
} simple_value_hash;


extern simple_value_hash __h;
extern simple_function_hash __f;


