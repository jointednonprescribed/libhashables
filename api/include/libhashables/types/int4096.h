
#ifndef _LIBHASHABLES__types_INT4096_H_
#define _LIBHASHABLES__types_INT4096_H_ 1

#ifndef _LIBHASHABLES__INCLUDES_H_
#   include "../includes.h"
#endif



LHASH_EXTERN_C


/*
 * 128-bit integer type
 */
typedef struct _lhashint4096_t
{
    unsigned long long v[64];
} lhashint4096_t, lhashuint4096_t;

#define lhashint4096_0 (lhashint4096_t){.v={0}}

typedef struct _lhashint4096_pair_t
{
    lhashuint4096_t v[2];
} lhashint4096_pair_t, lhashuint4096_pair_t;

LHASH_API lhashint4096_t  lhashint4096(long long int);
LHASH_API lhashuint4096_t lhashuint4096(unsigned long long int);
LHASH_API lhashint4096_t  lhashint4096l(long int);
LHASH_API lhashuint4096_t lhashuint4096l(unsigned long int);

LHASH_API lhashint4096_t  lhashint4096_pair(lhashint4096_t a, lhashint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_pair(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_pairll(long long a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_pairll(unsigned long long a, unsigned long long b);
LHASH_API lhashint4096_t  lhashint4096_pairl(long a, long b);
LHASH_API lhashuint4096_t lhashuint4096_pairl(unsigned long a, unsigned long b);

LHASH_API lhashint4096_t  lhashint4096_add(lhashint4096_t a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_addll(lhashint4096_t a, long long b);
LHASH_API lhashint4096_t  lhashint4096_addl(lhashint4096_t a, long b);
LHASH_API lhashuint4096_t lhashuint4096_add(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_addll(lhashuint4096_t a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_addl(lhashuint4096_t a, long b);
LHASH_API lhashint4096_t  lhashint4096_addeq(lhashint4096_t *a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_addlleq(lhashint4096_t *a, long long b);
LHASH_API lhashint4096_t  lhashint4096_addleq(lhashint4096_t *a, long b);
LHASH_API lhashuint4096_t lhashuint4096_addeq(lhashuint4096_t *a, lhashint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_addlleq(lhashuint4096_t *a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_addleq(lhashuint4096_t *a, long b);

LHASH_API lhashint4096_t  lhashint4096_sub(lhashint4096_t a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_subll(lhashint4096_t a, long long b);
LHASH_API lhashint4096_t  lhashint4096_subl(lhashint4096_t a, long b);
LHASH_API lhashuint4096_t lhashuint4096_sub(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_subll(lhashuint4096_t a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_subl(lhashuint4096_t a, long b);
LHASH_API lhashint4096_t  lhashint4096_subeq(lhashint4096_t *a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_sublleq(lhashint4096_t *a, long long b);
LHASH_API lhashint4096_t  lhashint4096_subleq(lhashint4096_t *a, long b);
LHASH_API lhashuint4096_t lhashuint4096_subeq(lhashuint4096_t *a, lhashint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_sublleq(lhashuint4096_t *a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_subleq(lhashuint4096_t *a, long b);

LHASH_API lhashint4096_t  lhashint4096_mult(lhashint4096_t a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_multll(lhashint4096_t a, long long b);
LHASH_API lhashint4096_t  lhashint4096_multl(lhashint4096_t a, long b);
LHASH_API lhashuint4096_t lhashuint4096_mult(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_multll(lhashuint4096_t a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_multl(lhashuint4096_t a, long b);
LHASH_API lhashint4096_t  lhashint4096_multeq(lhashint4096_t *a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_multlleq(lhashint4096_t *a, long long b);
LHASH_API lhashint4096_t  lhashint4096_multleq(lhashint4096_t *a, long b);
LHASH_API lhashuint4096_t lhashuint4096_multeq(lhashuint4096_t *a, lhashint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_multlleq(lhashuint4096_t *a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_multleq(lhashuint4096_t *a, long b);

LHASH_API lhashint4096_t  lhashint4096_div(lhashint4096_t a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_divll(lhashint4096_t a, long long b);
LHASH_API lhashint4096_t  lhashint4096_divl(lhashint4096_t a, long b);
LHASH_API lhashuint4096_t lhashuint4096_div(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_divll(lhashuint4096_t a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_divl(lhashuint4096_t a, long b);
LHASH_API lhashint4096_t  lhashint4096_diveq(lhashint4096_t *a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_divlleq(lhashint4096_t *a, long long b);
LHASH_API lhashint4096_t  lhashint4096_divleq(lhashint4096_t *a, long b);
LHASH_API lhashuint4096_t lhashuint4096_diveq(lhashuint4096_t *a, lhashint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_divlleq(lhashuint4096_t *a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_divleq(lhashuint4096_t *a, long b);

LHASH_API lhashint4096_t  lhashint4096_mod(lhashint4096_t a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_modll(lhashint4096_t a, long long b);
LHASH_API lhashint4096_t  lhashint4096_modl(lhashint4096_t a, long b);
LHASH_API lhashuint4096_t lhashuint4096_mod(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_modll(lhashuint4096_t a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_modl(lhashuint4096_t a, long b);
LHASH_API lhashint4096_t  lhashint4096_modeq(lhashint4096_t *a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_modlleq(lhashint4096_t *a, long long b);
LHASH_API lhashint4096_t  lhashint4096_modleq(lhashint4096_t *a, long b);
LHASH_API lhashuint4096_t lhashuint4096_modeq(lhashuint4096_t *a, lhashint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_modlleq(lhashuint4096_t *a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_modleq(lhashuint4096_t *a, long b);

LHASH_API lhashint4096_pair_t  lhashint4096_syndiv(lhashint4096_t a, lhashint4096_t b);
LHASH_API lhashint4096_pair_t  lhashint4096_syndivll(lhashint4096_t a, long long b);
LHASH_API lhashint4096_pair_t  lhashint4096_syndivl(lhashint4096_t a, long b);
LHASH_API lhashuint4096_pair_t lhashuint4096_syndiv(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API lhashuint4096_pair_t lhashuint4096_syndivll(lhashuint4096_t a, long long b);
LHASH_API lhashuint4096_pair_t lhashuint4096_syndivl(lhashuint4096_t a, long b);
LHASH_API lhashint4096_pair_t  lhashint4096_syndiveq(lhashint4096_t *a, lhashint4096_t b);
LHASH_API lhashint4096_pair_t  lhashint4096_syndivlleq(lhashint4096_t *a, long long b);
LHASH_API lhashint4096_pair_t  lhashint4096_syndivleq(lhashint4096_t *a, long b);
LHASH_API lhashuint4096_pair_t lhashuint4096_syndiveq(lhashuint4096_t *a, lhashint4096_t b);
LHASH_API lhashuint4096_pair_t lhashuint4096_syndivlleq(lhashuint4096_t *a, long long b);
LHASH_API lhashuint4096_pair_t lhashuint4096_syndivleq(lhashuint4096_t *a, long b);

LHASH_API lhashint4096_t  lhashint4096_shr(lhashint4096_t a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_shrll(lhashint4096_t a, long long b);
LHASH_API lhashint4096_t  lhashint4096_shrl(lhashint4096_t a, long b);
LHASH_API lhashuint4096_t lhashuint4096_shr(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_shrll(lhashuint4096_t a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_shrl(lhashuint4096_t a, long b);
LHASH_API lhashint4096_t  lhashint4096_shreq(lhashint4096_t *a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_shrlleq(lhashint4096_t *a, long long b);
LHASH_API lhashint4096_t  lhashint4096_shrleq(lhashint4096_t *a, long b);
LHASH_API lhashuint4096_t lhashuint4096_shreq(lhashuint4096_t *a, lhashint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_shrlleq(lhashuint4096_t *a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_shrleq(lhashuint4096_t *a, long b);

LHASH_API lhashint4096_t  lhashint4096_shl(lhashint4096_t a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_shlll(lhashint4096_t a, long long b);
LHASH_API lhashint4096_t  lhashint4096_shll(lhashint4096_t a, long b);
LHASH_API lhashuint4096_t lhashuint4096_shl(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_shlll(lhashuint4096_t a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_shll(lhashuint4096_t a, long b);
LHASH_API lhashint4096_t  lhashint4096_shleq(lhashint4096_t *a, lhashint4096_t b);
LHASH_API lhashint4096_t  lhashint4096_shllleq(lhashint4096_t *a, long long b);
LHASH_API lhashint4096_t  lhashint4096_shlleq(lhashint4096_t *a, long b);
LHASH_API lhashuint4096_t lhashuint4096_shleq(lhashuint4096_t *a, lhashint4096_t b);
LHASH_API lhashuint4096_t lhashuint4096_shllleq(lhashuint4096_t *a, long long b);
LHASH_API lhashuint4096_t lhashuint4096_shlleq(lhashuint4096_t *a, long b);

LHASH_API int            lhashint4096_cmp(lhashint4096_t a, lhashint4096_t b);
LHASH_API int            lhashint4096_cmpll(lhashint4096_t a, long long b);
LHASH_API int            lhashint4096_cmpl(lhashint4096_t a, long b);
LHASH_API int            lhashuint4096_cmp(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API int            lhashuint4096_cmpll(lhashuint4096_t a, long long b);
LHASH_API int            lhashuint4096_cmpl(lhashuint4096_t a, long b);

LHASH_API bool           lhashint4096_cmple(lhashint4096_t a, lhashint4096_t b);
LHASH_API bool           lhashint4096_cmplell(lhashint4096_t a, long long b);
LHASH_API bool           lhashint4096_cmplel(lhashint4096_t a, long b);
LHASH_API bool           lhashuint4096_cmple(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API bool           lhashuint4096_cmplell(lhashuint4096_t a, long long b);
LHASH_API bool           lhashuint4096_cmplel(lhashuint4096_t a, long b);

LHASH_API bool           lhashint4096_cmplt(lhashint4096_t a, lhashint4096_t b);
LHASH_API bool           lhashint4096_cmpltll(lhashint4096_t a, long long b);
LHASH_API bool           lhashint4096_cmpltl(lhashint4096_t a, long b);
LHASH_API bool           lhashuint4096_cmplt(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API bool           lhashuint4096_cmpltll(lhashuint4096_t a, long long b);
LHASH_API bool           lhashuint4096_cmpltl(lhashuint4096_t a, long b);

LHASH_API bool           lhashint4096_cmpge(lhashint4096_t a, lhashint4096_t b);
LHASH_API bool           lhashint4096_cmpgell(lhashint4096_t a, long long b);
LHASH_API bool           lhashint4096_cmpgel(lhashint4096_t a, long b);
LHASH_API bool           lhashuint4096_cmpge(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API bool           lhashuint4096_cmpgell(lhashuint4096_t a, long long b);
LHASH_API bool           lhashuint4096_cmpgel(lhashuint4096_t a, long b);

LHASH_API bool           lhashint4096_cmpgt(lhashint4096_t a, lhashint4096_t b);
LHASH_API bool           lhashint4096_cmpgtll(lhashint4096_t a, long long b);
LHASH_API bool           lhashint4096_cmpgtl(lhashint4096_t a, long b);
LHASH_API bool           lhashuint4096_cmpgt(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API bool           lhashuint4096_cmpgtll(lhashuint4096_t a, long long b);
LHASH_API bool           lhashuint4096_cmpgtl(lhashuint4096_t a, long b);

LHASH_API bool           lhashint4096_cmpeq(lhashint4096_t a, lhashint4096_t b);
LHASH_API bool           lhashint4096_cmpeqll(lhashint4096_t a, long long b);
LHASH_API bool           lhashint4096_cmpeql(lhashint4096_t a, long b);
LHASH_API bool           lhashuint4096_cmpeq(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API bool           lhashuint4096_cmpeqll(lhashuint4096_t a, long long b);
LHASH_API bool           lhashuint4096_cmpeql(lhashuint4096_t a, long b);

LHASH_API bool           lhashint4096_cmpne(lhashint4096_t a, lhashint4096_t b);
LHASH_API bool           lhashint4096_cmpnell(lhashint4096_t a, long long b);
LHASH_API bool           lhashint4096_cmpnel(lhashint4096_t a, long b);
LHASH_API bool           lhashuint4096_cmpne(lhashuint4096_t a, lhashuint4096_t b);
LHASH_API bool           lhashuint4096_cmpnell(lhashuint4096_t a, long long b);
LHASH_API bool           lhashuint4096_cmpnel(lhashuint4096_t a, long b);


LHASH_END_EXTERN_C



#endif // _LIBHASHABLES__types_INT4096_H_
