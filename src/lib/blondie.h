#include "blondie_magic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>

#define INIT 1
#define NOT_INIT 0
// #define ARRMAX 256
// #define ARRMAX 1024
#define ARRMAX 32768
// #define ARRMAX 1048576
#define MSTR 100000
#define SHORTSTR 1024
#define CRCLEN 9
#define DELIM '\t'
#define DEF 1

#define die(); exit(1);
#define str(a) #a

#define BLONDIE_CAT( dest, src ) \
    if ( strlen(dest)+strlen(src) <= sizeof(dest) / sizeof(char*) ) { \
        strcat( dest, src ); \
    } 
#define STR(s) str(s)
#define __$P(...)  __VA_ARGS__
#define __$V(...)  __VA_ARGS__
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
#define COMMA() ,
#define COMMAFY(x) CAT(x, COMMA)
#define EVAL(...) __VA_ARGS__

#define $HN(fn) CAT(__BLONDIE_HASH_, fn)

#define $HS(fn) struct getHStructName(fn)

#define getHStructName( fn )  CAT(__BLONDIE_HASH_STRUCT_, fn) 

#define DEFINE_HASH_STRUCT( r, fn ) \
    $HS(fn) { \
        int is_stored[ARRMAX]; \
        char* key[ARRMAX]; \
        r rval[ARRMAX]; \
    };

#define SERIALIZE_AND_CAT_KEY( p ) { \
    long sz = (2 * sizeof(p) ) + 1; \
    char ctmpp[sz]; \
    sprintf(ctmpp, "%X", crc32c((unsigned char*)&p)); \
    BLONDIE_CAT( key, ctmpp ); \
}

#define SERIALIZE_PARAMS(args) \
    char key[MSTR] = "0x"; \
    FOR_EACH( SERIALIZE_AND_CAT_KEY, args );

#define BlondieMemoize(r, n, tps, vps, b...) \
    /*define signature of memo function*/ \
    r CAT( __, n )( CAT( __, tps) ); \
    /*write original function with __ prefix*/ \
    r CAT( __, n )( CAT( __, tps) ) b  \
\
    /*define args struct and function hash*/ \
    DEFINE_HASH_STRUCT(r, n); \
    $HS( n ) $HN( n ); \
\
    r n( CAT(__, tps) ) { \
        printf("START\n"); \
        /*declare my struct vars local to the new funcrion*/ \
        /*set params to what's in the arguments to orignial function*/ \
        SERIALIZE_PARAMS( CAT(__, vps) ); \
        /*store params in param struct, serialize, and dump to hash for crc and dirty compare*/ \
        long ikey = abs( strtoll( key, NULL, 0) ); \
        long crc = ikey % ARRMAX; \
\
        if( $HN(n).is_stored[crc] && !strcmp($HN(n).key[crc], key) ) { \
            return $HN(n).rval[crc]; \
        } else { \
            if($HN(n).is_stored[crc]) { \
                free($HN(n).key[crc]); \
            } \
            /*allocate memory to hash key
             * will need to free it each time this is hit 
             * */ \
            $HN(n).key[crc] = malloc( sizeof(key) ); \
            strcpy($HN(n).key[crc], key); \
            $HN(n).is_stored[crc] = 1; \
            $HN(n).rval[crc] = CAT( __, n )( CAT(__,vps) ); \
            return $HN(n).rval[crc]; \
        } \
        return (r)NULL; \
    } 

#define BlondieCrc( a ) getCRC( a, strlen(a) ) % ARRMAX
unsigned int crc32c(unsigned char *message);

/*long getCRC(char message[], int length); */
