
#ifndef _LIBHASHABLES__types_INT2048_H_
#define _LIBHASHABLES__types_INT2048_H_ 1

#ifndef _LIBHASHABLES__INCLUDES_H_
#   include "../includes.h"
#endif



LHASH_EXTERN_C


/*
 * 128-bit integer type
 */
typedef struct _lhashint2048_t
{
    unsigned long long v[32];
} lhashint2048_t, lhashuint2048_t;

#define lhashint2048_0 (lhashint2048_t){.v={0}}

typedef struct _lhashint2048_pair_t
{
    lhashuint2048_t v[2];
} lhashint2048_pair_t, lhashuint2048_pair_t;

LHASH_API lhashint2048_t  lhashint2048(long long int);
LHASH_API lhashuint2048_t lhashuint2048(unsigned long long int);
LHASH_API lhashint2048_t  lhashint2048l(long int);
LHASH_API lhashuint2048_t lhashuint2048l(unsigned long int);

LHASH_API lhashint2048_t  lhashint2048_pair(lhashint2048_t a, lhashint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_pair(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_pairll(long long a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_pairll(unsigned long long a, unsigned long long b);
LHASH_API lhashint2048_t  lhashint2048_pairl(long a, long b);
LHASH_API lhashuint2048_t lhashuint2048_pairl(unsigned long a, unsigned long b);

LHASH_API lhashint2048_t  lhashint2048_add(lhashint2048_t a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_addll(lhashint2048_t a, long long b);
LHASH_API lhashint2048_t  lhashint2048_addl(lhashint2048_t a, long b);
LHASH_API lhashuint2048_t lhashuint2048_add(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_addll(lhashuint2048_t a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_addl(lhashuint2048_t a, long b);
LHASH_API lhashint2048_t  lhashint2048_addeq(lhashint2048_t *a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_addlleq(lhashint2048_t *a, long long b);
LHASH_API lhashint2048_t  lhashint2048_addleq(lhashint2048_t *a, long b);
LHASH_API lhashuint2048_t lhashuint2048_addeq(lhashuint2048_t *a, lhashint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_addlleq(lhashuint2048_t *a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_addleq(lhashuint2048_t *a, long b);

LHASH_API lhashint2048_t  lhashint2048_sub(lhashint2048_t a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_subll(lhashint2048_t a, long long b);
LHASH_API lhashint2048_t  lhashint2048_subl(lhashint2048_t a, long b);
LHASH_API lhashuint2048_t lhashuint2048_sub(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_subll(lhashuint2048_t a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_subl(lhashuint2048_t a, long b);
LHASH_API lhashint2048_t  lhashint2048_subeq(lhashint2048_t *a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_sublleq(lhashint2048_t *a, long long b);
LHASH_API lhashint2048_t  lhashint2048_subleq(lhashint2048_t *a, long b);
LHASH_API lhashuint2048_t lhashuint2048_subeq(lhashuint2048_t *a, lhashint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_sublleq(lhashuint2048_t *a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_subleq(lhashuint2048_t *a, long b);

LHASH_API lhashint2048_t  lhashint2048_mult(lhashint2048_t a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_multll(lhashint2048_t a, long long b);
LHASH_API lhashint2048_t  lhashint2048_multl(lhashint2048_t a, long b);
LHASH_API lhashuint2048_t lhashuint2048_mult(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_multll(lhashuint2048_t a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_multl(lhashuint2048_t a, long b);
LHASH_API lhashint2048_t  lhashint2048_multeq(lhashint2048_t *a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_multlleq(lhashint2048_t *a, long long b);
LHASH_API lhashint2048_t  lhashint2048_multleq(lhashint2048_t *a, long b);
LHASH_API lhashuint2048_t lhashuint2048_multeq(lhashuint2048_t *a, lhashint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_multlleq(lhashuint2048_t *a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_multleq(lhashuint2048_t *a, long b);

LHASH_API lhashint2048_t  lhashint2048_div(lhashint2048_t a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_divll(lhashint2048_t a, long long b);
LHASH_API lhashint2048_t  lhashint2048_divl(lhashint2048_t a, long b);
LHASH_API lhashuint2048_t lhashuint2048_div(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_divll(lhashuint2048_t a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_divl(lhashuint2048_t a, long b);
LHASH_API lhashint2048_t  lhashint2048_diveq(lhashint2048_t *a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_divlleq(lhashint2048_t *a, long long b);
LHASH_API lhashint2048_t  lhashint2048_divleq(lhashint2048_t *a, long b);
LHASH_API lhashuint2048_t lhashuint2048_diveq(lhashuint2048_t *a, lhashint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_divlleq(lhashuint2048_t *a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_divleq(lhashuint2048_t *a, long b);

LHASH_API lhashint2048_t  lhashint2048_mod(lhashint2048_t a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_modll(lhashint2048_t a, long long b);
LHASH_API lhashint2048_t  lhashint2048_modl(lhashint2048_t a, long b);
LHASH_API lhashuint2048_t lhashuint2048_mod(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_modll(lhashuint2048_t a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_modl(lhashuint2048_t a, long b);
LHASH_API lhashint2048_t  lhashint2048_modeq(lhashint2048_t *a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_modlleq(lhashint2048_t *a, long long b);
LHASH_API lhashint2048_t  lhashint2048_modleq(lhashint2048_t *a, long b);
LHASH_API lhashuint2048_t lhashuint2048_modeq(lhashuint2048_t *a, lhashint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_modlleq(lhashuint2048_t *a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_modleq(lhashuint2048_t *a, long b);

LHASH_API lhashint2048_pair_t  lhashint2048_syndiv(lhashint2048_t a, lhashint2048_t b);
LHASH_API lhashint2048_pair_t  lhashint2048_syndivll(lhashint2048_t a, long long b);
LHASH_API lhashint2048_pair_t  lhashint2048_syndivl(lhashint2048_t a, long b);
LHASH_API lhashuint2048_pair_t lhashuint2048_syndiv(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API lhashuint2048_pair_t lhashuint2048_syndivll(lhashuint2048_t a, long long b);
LHASH_API lhashuint2048_pair_t lhashuint2048_syndivl(lhashuint2048_t a, long b);
LHASH_API lhashint2048_pair_t  lhashint2048_syndiveq(lhashint2048_t *a, lhashint2048_t b);
LHASH_API lhashint2048_pair_t  lhashint2048_syndivlleq(lhashint2048_t *a, long long b);
LHASH_API lhashint2048_pair_t  lhashint2048_syndivleq(lhashint2048_t *a, long b);
LHASH_API lhashuint2048_pair_t lhashuint2048_syndiveq(lhashuint2048_t *a, lhashint2048_t b);
LHASH_API lhashuint2048_pair_t lhashuint2048_syndivlleq(lhashuint2048_t *a, long long b);
LHASH_API lhashuint2048_pair_t lhashuint2048_syndivleq(lhashuint2048_t *a, long b);

LHASH_API lhashint2048_t  lhashint2048_shr(lhashint2048_t a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_shrll(lhashint2048_t a, long long b);
LHASH_API lhashint2048_t  lhashint2048_shrl(lhashint2048_t a, long b);
LHASH_API lhashuint2048_t lhashuint2048_shr(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_shrll(lhashuint2048_t a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_shrl(lhashuint2048_t a, long b);
LHASH_API lhashint2048_t  lhashint2048_shreq(lhashint2048_t *a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_shrlleq(lhashint2048_t *a, long long b);
LHASH_API lhashint2048_t  lhashint2048_shrleq(lhashint2048_t *a, long b);
LHASH_API lhashuint2048_t lhashuint2048_shreq(lhashuint2048_t *a, lhashint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_shrlleq(lhashuint2048_t *a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_shrleq(lhashuint2048_t *a, long b);

LHASH_API lhashint2048_t  lhashint2048_shl(lhashint2048_t a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_shlll(lhashint2048_t a, long long b);
LHASH_API lhashint2048_t  lhashint2048_shll(lhashint2048_t a, long b);
LHASH_API lhashuint2048_t lhashuint2048_shl(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_shlll(lhashuint2048_t a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_shll(lhashuint2048_t a, long b);
LHASH_API lhashint2048_t  lhashint2048_shleq(lhashint2048_t *a, lhashint2048_t b);
LHASH_API lhashint2048_t  lhashint2048_shllleq(lhashint2048_t *a, long long b);
LHASH_API lhashint2048_t  lhashint2048_shlleq(lhashint2048_t *a, long b);
LHASH_API lhashuint2048_t lhashuint2048_shleq(lhashuint2048_t *a, lhashint2048_t b);
LHASH_API lhashuint2048_t lhashuint2048_shllleq(lhashuint2048_t *a, long long b);
LHASH_API lhashuint2048_t lhashuint2048_shlleq(lhashuint2048_t *a, long b);

LHASH_API int            lhashint2048_cmp(lhashint2048_t a, lhashint2048_t b);
LHASH_API int            lhashint2048_cmpll(lhashint2048_t a, long long b);
LHASH_API int            lhashint2048_cmpl(lhashint2048_t a, long b);
LHASH_API int            lhashuint2048_cmp(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API int            lhashuint2048_cmpll(lhashuint2048_t a, long long b);
LHASH_API int            lhashuint2048_cmpl(lhashuint2048_t a, long b);

LHASH_API bool           lhashint2048_cmple(lhashint2048_t a, lhashint2048_t b);
LHASH_API bool           lhashint2048_cmplell(lhashint2048_t a, long long b);
LHASH_API bool           lhashint2048_cmplel(lhashint2048_t a, long b);
LHASH_API bool           lhashuint2048_cmple(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API bool           lhashuint2048_cmplell(lhashuint2048_t a, long long b);
LHASH_API bool           lhashuint2048_cmplel(lhashuint2048_t a, long b);

LHASH_API bool           lhashint2048_cmplt(lhashint2048_t a, lhashint2048_t b);
LHASH_API bool           lhashint2048_cmpltll(lhashint2048_t a, long long b);
LHASH_API bool           lhashint2048_cmpltl(lhashint2048_t a, long b);
LHASH_API bool           lhashuint2048_cmplt(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API bool           lhashuint2048_cmpltll(lhashuint2048_t a, long long b);
LHASH_API bool           lhashuint2048_cmpltl(lhashuint2048_t a, long b);

LHASH_API bool           lhashint2048_cmpge(lhashint2048_t a, lhashint2048_t b);
LHASH_API bool           lhashint2048_cmpgell(lhashint2048_t a, long long b);
LHASH_API bool           lhashint2048_cmpgel(lhashint2048_t a, long b);
LHASH_API bool           lhashuint2048_cmpge(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API bool           lhashuint2048_cmpgell(lhashuint2048_t a, long long b);
LHASH_API bool           lhashuint2048_cmpgel(lhashuint2048_t a, long b);

LHASH_API bool           lhashint2048_cmpgt(lhashint2048_t a, lhashint2048_t b);
LHASH_API bool           lhashint2048_cmpgtll(lhashint2048_t a, long long b);
LHASH_API bool           lhashint2048_cmpgtl(lhashint2048_t a, long b);
LHASH_API bool           lhashuint2048_cmpgt(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API bool           lhashuint2048_cmpgtll(lhashuint2048_t a, long long b);
LHASH_API bool           lhashuint2048_cmpgtl(lhashuint2048_t a, long b);

LHASH_API bool           lhashint2048_cmpeq(lhashint2048_t a, lhashint2048_t b);
LHASH_API bool           lhashint2048_cmpeqll(lhashint2048_t a, long long b);
LHASH_API bool           lhashint2048_cmpeql(lhashint2048_t a, long b);
LHASH_API bool           lhashuint2048_cmpeq(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API bool           lhashuint2048_cmpeqll(lhashuint2048_t a, long long b);
LHASH_API bool           lhashuint2048_cmpeql(lhashuint2048_t a, long b);

LHASH_API bool           lhashint2048_cmpne(lhashint2048_t a, lhashint2048_t b);
LHASH_API bool           lhashint2048_cmpnell(lhashint2048_t a, long long b);
LHASH_API bool           lhashint2048_cmpnel(lhashint2048_t a, long b);
LHASH_API bool           lhashuint2048_cmpne(lhashuint2048_t a, lhashuint2048_t b);
LHASH_API bool           lhashuint2048_cmpnell(lhashuint2048_t a, long long b);
LHASH_API bool           lhashuint2048_cmpnel(lhashuint2048_t a, long b);


LHASH_END_EXTERN_C



#endif // _LIBHASHABLES__types_INT2048_H_
