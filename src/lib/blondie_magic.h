//from - http://stackoverflow.com/questions/1872220/is-it-possible-to-iterate-over-arguments-in-variadic-macros
// Make a FOREACH macro
#define FE_1(WHAT, X) WHAT( X ) 
#define FE_2(WHAT, X, ...) WHAT( X ) FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT( X ) FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT( X ) FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT( X ) FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT( X ) FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT( X ) FE_6(WHAT, __VA_ARGS__)
#define FE_8(WHAT, X, ...) WHAT( X ) FE_7(WHAT, __VA_ARGS__)
#define FE_9(WHAT, X, ...) WHAT( X ) FE_8(WHAT, __VA_ARGS__)
#define FE_10(WHAT, X, ...) WHAT( X ) FE_9(WHAT, __VA_ARGS__)
#define FE_11(WHAT, X, ...) WHAT( X ) FE_10(WHAT, __VA_ARGS__)
#define FE_12(WHAT, X, ...) WHAT( X ) FE_11(WHAT, __VA_ARGS__)
#define FE_13(WHAT, X, ...) WHAT( X ) FE_12(WHAT, __VA_ARGS__)
#define FE_14(WHAT, X, ...) WHAT( X ) FE_13(WHAT, __VA_ARGS__)
#define FE_15(WHAT, X, ...) WHAT( X ) FE_14(WHAT, __VA_ARGS__)
#define FE_16(WHAT, X, ...) WHAT( X ) FE_15(WHAT, __VA_ARGS__)
#define FE_17(WHAT, X, ...) WHAT( X ) FE_16(WHAT, __VA_ARGS__)
#define FE_18(WHAT, X, ...) WHAT( X ) FE_17(WHAT, __VA_ARGS__)
#define FE_19(WHAT, X, ...) WHAT( X ) FE_18(WHAT, __VA_ARGS__)
#define FE_20(WHAT, X, ...) WHAT( X ) FE_19(WHAT, __VA_ARGS__)
#define FE_21(WHAT, X, ...) WHAT( X ) FE_20(WHAT, __VA_ARGS__)
#define FE_22(WHAT, X, ...) WHAT( X ) FE_21(WHAT, __VA_ARGS__)
#define FE_23(WHAT, X, ...) WHAT( X ) FE_22(WHAT, __VA_ARGS__)
#define FE_24(WHAT, X, ...) WHAT( X ) FE_23(WHAT, __VA_ARGS__)
#define FE_25(WHAT, X, ...) WHAT( X ) FE_24(WHAT, __VA_ARGS__)
#define FE_26(WHAT, X, ...) WHAT( X ) FE_25(WHAT, __VA_ARGS__)
#define FE_27(WHAT, X, ...) WHAT( X ) FE_26(WHAT, __VA_ARGS__)
#define FE_28(WHAT, X, ...) WHAT( X ) FE_27(WHAT, __VA_ARGS__)
#define FE_29(WHAT, X, ...) WHAT( X ) FE_28(WHAT, __VA_ARGS__)
#define FE_30(WHAT, X, ...) WHAT( X ) FE_29(WHAT, __VA_ARGS__)
#define FE_31(WHAT, X, ...) WHAT( X ) FE_30(WHAT, __VA_ARGS__)
#define FE_32(WHAT, X, ...) WHAT( X ) FE_31(WHAT, __VA_ARGS__)
#define FE_33(WHAT, X, ...) WHAT( X ) FE_32(WHAT, __VA_ARGS__)
#define FE_34(WHAT, X, ...) WHAT( X ) FE_33(WHAT, __VA_ARGS__)
#define FE_35(WHAT, X, ...) WHAT( X ) FE_34(WHAT, __VA_ARGS__)
#define FE_36(WHAT, X, ...) WHAT( X ) FE_35(WHAT, __VA_ARGS__)
#define FE_37(WHAT, X, ...) WHAT( X ) FE_36(WHAT, __VA_ARGS__)
#define FE_38(WHAT, X, ...) WHAT( X ) FE_37(WHAT, __VA_ARGS__)
#define FE_39(WHAT, X, ...) WHAT( X ) FE_38(WHAT, __VA_ARGS__)
#define FE_40(WHAT, X, ...) WHAT( X ) FE_39(WHAT, __VA_ARGS__)
#define FE_41(WHAT, X, ...) WHAT( X ) FE_40(WHAT, __VA_ARGS__)
#define FE_42(WHAT, X, ...) WHAT( X ) FE_41(WHAT, __VA_ARGS__)
#define FE_43(WHAT, X, ...) WHAT( X ) FE_42(WHAT, __VA_ARGS__)
#define FE_44(WHAT, X, ...) WHAT( X ) FE_43(WHAT, __VA_ARGS__)
#define FE_45(WHAT, X, ...) WHAT( X ) FE_44(WHAT, __VA_ARGS__)
#define FE_46(WHAT, X, ...) WHAT( X ) FE_45(WHAT, __VA_ARGS__)
#define FE_47(WHAT, X, ...) WHAT( X ) FE_46(WHAT, __VA_ARGS__)
#define FE_48(WHAT, X, ...) WHAT( X ) FE_47(WHAT, __VA_ARGS__)
#define FE_49(WHAT, X, ...) WHAT( X ) FE_48(WHAT, __VA_ARGS__)
#define FE_50(WHAT, X, ...) WHAT( X ) FE_49(WHAT, __VA_ARGS__)

//... repeat as needed

#define GET_MACRO(_1,_2,_3,_4,_5,NAME,...) NAME 
#define FOR_EACH(action,...) \
  GET_MACRO(__VA_ARGS__,FE_5,FE_4,FE_3,FE_2,FE_1)(action,__VA_ARGS__)
