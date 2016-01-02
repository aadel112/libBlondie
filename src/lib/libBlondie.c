#include "blondie.h"
simple_value_hash __h;
simple_function_hash __f;

int is_value_stored( int crc ) {
    return __h.is_stored[crc] == DEF;
}

const int CRC7_POLY = 0x91;
/*https://www.pololu.com/docs/0J44/6.7.6*/
long getCRC(char message[], int length) {
    long i, j, crc = 0;

    for (i = 0; i < length; i++) {
        crc ^= message[i];
        for (j = 0; j < CRCLEN; j++) {
            if (crc & 1)
                crc ^= CRC7_POLY;
            crc >>= 1;
        }
    }
    return crc;
}

void setfvar(int fcrc) {
    switch(__f.type[fcrc]) {

        case(t_BOOL):
#undef fvar 
#define fvar fun_t_BOOL_BLONDIE 
            break;
        case(t_UNSIGNED_CHAR):
#undef fvar
#define fvar fun_t_UNSIGNED_CHAR_BLONDIE 
            break;
        case(t_CHAR):
#undef fvar 
#define fvar fun_t_CHAR_BLONDIE 
            break;
        case(t_SIGNED_CHAR):
#undef fvar 
#define fvar fun_t_SIGNED_CHAR_BLONDIE 
            break;
        case(t_SHORT_INT): 
#undef fvar
#define fvar fun_t_SHORT_INT_BLONDIE 
            break;
        case(t_UNSIGNED_SHORT_INT): 
#undef fvar
#define fvar fun_t_UNSIGNED_SHORT_INT_BLONDIE 
            break;
        case(t_INT):
#undef fvar
#define fvar fun_t_INT_BLONDIE 
            break;
        case(t_UNSIGNED_INT):
#undef fvar 
#define fvar fun_t_UNSIGNED_INT_BLONDIE 
            break;
        case(t_LONG_INT): 
#undef fvar
#define fvar fun_t_LONG_INT_BLONDIE 
            break;	
        case(t_UNSIGNED_LONG_INT): 
#undef fvar
#define fvar fun_t_UNSIGNED_LONG_INT_BLONDIE 
            break;
        case(t_LONG_LONG_INT): 
#undef fvar
#define fvar fun_t_LONG_LONG_INT_BLONDIE 
            break;
        case(t_UNSIGNED_LONG_LONG_INT): 
#undef fvar
#define fvar fun_t_UNSIGNED_LONG_LONG_INT_BLONDIE 
            break;
        case(t_FLOAT): 
#undef fvar
#define fvar fun_t_FLOAT_BLONDIE 
            break;
        case(t_DOUBLE): 
#undef fvar
#define fvar fun_t_DOUBLE_BLONDIE 
            break;  
        case(t_LONG_DOUBLE): 
#undef fvar
#define fvar fun_t_LONG_DOUBLE_BLONDIE 
            break;   
        case(t_POINTER_TO_CHAR):
#undef fvar 
#define fvar fun_t_POINTER_TO_CHAR_BLONDIE 
            break;
        case(t_POINTER_TO_VOID):
#undef fvar
#define fvar fun_t_POINTER_TO_VOID_BLONDIE 
            break;
        case(t_POINTER_TO_INT):
#undef fvar
#define fvar fun_t_POINTER_TO_INT_BLONDIE 
            break;
        default:
            break;
    }

}
void setvar(int fcrc) {
    switch(__f.type[fcrc]) {

        case(t_BOOL):
#undef tvar 
#define tvar v_t_BOOL_BLONDIE 
            break;
        case(t_UNSIGNED_CHAR):
#undef tvar
#define tvar v_t_UNSIGNED_CHAR_BLONDIE 
            break;
        case(t_CHAR):
#undef tvar 
#define tvar v_t_CHAR_BLONDIE 
            break;
        case(t_SIGNED_CHAR):
#undef tvar 
#define tvar v_t_SIGNED_CHAR_BLONDIE 
            break;
        case(t_SHORT_INT): 
#undef tvar
#define tvar v_t_SHORT_INT_BLONDIE 
            break;
        case(t_UNSIGNED_SHORT_INT): 
#undef tvar
#define tvar v_t_UNSIGNED_SHORT_INT_BLONDIE 
            break;
        case(t_INT):
#undef tvar
#define tvar v_t_INT_BLONDIE 
            break;
        case(t_UNSIGNED_INT):
#undef tvar 
#define tvar v_t_UNSIGNED_INT_BLONDIE 
            break;
        case(t_LONG_INT): 
#undef tvar
#define tvar v_t_LONG_INT_BLONDIE 
            break;	
        case(t_UNSIGNED_LONG_INT): 
#undef tvar
#define tvar v_t_UNSIGNED_LONG_INT_BLONDIE 
            break;
        case(t_LONG_LONG_INT): 
#undef tvar
#define tvar v_t_LONG_LONG_INT_BLONDIE 
            break;
        case(t_UNSIGNED_LONG_LONG_INT): 
#undef tvar
#define tvar v_t_UNSIGNED_LONG_LONG_INT_BLONDIE 
            break;
        case(t_FLOAT): 
#undef tvar
#define tvar v_t_FLOAT_BLONDIE 
            break;
        case(t_DOUBLE): 
#undef tvar
#define tvar v_t_DOUBLE_BLONDIE 
            break;  
        case(t_LONG_DOUBLE): 
#undef tvar
#define tvar v_t_LONG_DOUBLE_BLONDIE 
            break;   
        case(t_POINTER_TO_CHAR):
#undef tvar 
#define tvar v_t_POINTER_TO_CHAR_BLONDIE 
            break;
        case(t_POINTER_TO_VOID):
#undef tvar
#define tvar v_t_POINTER_TO_VOID_BLONDIE 
            break;
        case(t_POINTER_TO_INT):
#undef tvar
#define tvar v_t_POINTER_TO_INT_BLONDIE 
            break;
        default:
            break;
    }

}


char* getMod(enum t_typename t) {
   switch(t) {
        case(t_BOOL):
            return "%d";
            break;
        case(t_UNSIGNED_CHAR):
            return "%c";
            break;
        case(t_CHAR):
            return "%c";
            break;
        case(t_SIGNED_CHAR):
            return "%c";
            break;
        case(t_SHORT_INT): 
            return "%d";
            break;
        case(t_UNSIGNED_SHORT_INT): 
            return "%d";
            break;
        case(t_INT):
            return "%d";
            break;
        case(t_UNSIGNED_INT):
            return "%d";
            break;
        case(t_LONG_INT): 
            return "%ld";
            break;	
        case(t_UNSIGNED_LONG_INT): 
            return "%ld";
            break;
        case(t_LONG_LONG_INT): 
            return "%ld";
            break;
        case(t_UNSIGNED_LONG_LONG_INT): 
            return "%ld";
            break;
        case(t_FLOAT): 
            return "%f";
            break;
        case(t_DOUBLE): 
            return "%f";
            break;  
        case(t_LONG_DOUBLE): 
            return "%lf";
            break;   
        case(t_POINTER_TO_CHAR):
            return "%s";
            break;
        case(t_POINTER_TO_VOID):
            return "%x";
            break;
        case(t_POINTER_TO_INT):
            return "%x";
            break;
        default:
            return "";
            break;
    }
    return "";
}
