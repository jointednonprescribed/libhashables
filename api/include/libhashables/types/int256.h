
#ifndef _LIBHASHABLES__types_INT256_H_
#define _LIBHASHABLES__types_INT256_H_ 1

#ifndef _LIBHASHABLES__INCLUDES_H_
#   include "../includes.h"
#endif



LHASH_EXTERN_C


/*
 * 128-bit integer type
 */
typedef struct _lhashint256_t
{
    unsigned long long v[4];
} lhashint256_t, lhashuint256_t;

#define lhashint256_0 (lhashint256_t){.v={0}}

typedef struct _lhashint256_pair_t
{
    lhashuint256_t v[2];
} lhashint256_pair_t, lhashuint256_pair_t;

LHASH_API lhashint256_t  lhashint256(long long int);
LHASH_API lhashuint256_t lhashuint256(unsigned long long int);
LHASH_API lhashint256_t  lhashint256l(long int);
LHASH_API lhashuint256_t lhashuint256l(unsigned long int);

LHASH_API lhashint256_t  lhashint256_pair(lhashint256_t a, lhashint256_t b);
LHASH_API lhashuint256_t lhashuint256_pair(lhashuint256_t a, lhashuint256_t b);
LHASH_API lhashint256_t  lhashint256_pairll(long long a, long long b);
LHASH_API lhashuint256_t lhashuint256_pairll(unsigned long long a, unsigned long long b);
LHASH_API lhashint256_t  lhashint256_pairl(long a, long b);
LHASH_API lhashuint256_t lhashuint256_pairl(unsigned long a, unsigned long b);

LHASH_API lhashint256_t  lhashint256_add(lhashint256_t a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_addll(lhashint256_t a, long long b);
LHASH_API lhashint256_t  lhashint256_addl(lhashint256_t a, long b);
LHASH_API lhashuint256_t lhashuint256_add(lhashuint256_t a, lhashuint256_t b);
LHASH_API lhashuint256_t lhashuint256_addll(lhashuint256_t a, long long b);
LHASH_API lhashuint256_t lhashuint256_addl(lhashuint256_t a, long b);
LHASH_API lhashint256_t  lhashint256_addeq(lhashint256_t *a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_addlleq(lhashint256_t *a, long long b);
LHASH_API lhashint256_t  lhashint256_addleq(lhashint256_t *a, long b);
LHASH_API lhashuint256_t lhashuint256_addeq(lhashuint256_t *a, lhashint256_t b);
LHASH_API lhashuint256_t lhashuint256_addlleq(lhashuint256_t *a, long long b);
LHASH_API lhashuint256_t lhashuint256_addleq(lhashuint256_t *a, long b);

LHASH_API lhashint256_t  lhashint256_sub(lhashint256_t a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_subll(lhashint256_t a, long long b);
LHASH_API lhashint256_t  lhashint256_subl(lhashint256_t a, long b);
LHASH_API lhashuint256_t lhashuint256_sub(lhashuint256_t a, lhashuint256_t b);
LHASH_API lhashuint256_t lhashuint256_subll(lhashuint256_t a, long long b);
LHASH_API lhashuint256_t lhashuint256_subl(lhashuint256_t a, long b);
LHASH_API lhashint256_t  lhashint256_subeq(lhashint256_t *a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_sublleq(lhashint256_t *a, long long b);
LHASH_API lhashint256_t  lhashint256_subleq(lhashint256_t *a, long b);
LHASH_API lhashuint256_t lhashuint256_subeq(lhashuint256_t *a, lhashint256_t b);
LHASH_API lhashuint256_t lhashuint256_sublleq(lhashuint256_t *a, long long b);
LHASH_API lhashuint256_t lhashuint256_subleq(lhashuint256_t *a, long b);

LHASH_API lhashint256_t  lhashint256_mult(lhashint256_t a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_multll(lhashint256_t a, long long b);
LHASH_API lhashint256_t  lhashint256_multl(lhashint256_t a, long b);
LHASH_API lhashuint256_t lhashuint256_mult(lhashuint256_t a, lhashuint256_t b);
LHASH_API lhashuint256_t lhashuint256_multll(lhashuint256_t a, long long b);
LHASH_API lhashuint256_t lhashuint256_multl(lhashuint256_t a, long b);
LHASH_API lhashint256_t  lhashint256_multeq(lhashint256_t *a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_multlleq(lhashint256_t *a, long long b);
LHASH_API lhashint256_t  lhashint256_multleq(lhashint256_t *a, long b);
LHASH_API lhashuint256_t lhashuint256_multeq(lhashuint256_t *a, lhashint256_t b);
LHASH_API lhashuint256_t lhashuint256_multlleq(lhashuint256_t *a, long long b);
LHASH_API lhashuint256_t lhashuint256_multleq(lhashuint256_t *a, long b);

LHASH_API lhashint256_t  lhashint256_div(lhashint256_t a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_divll(lhashint256_t a, long long b);
LHASH_API lhashint256_t  lhashint256_divl(lhashint256_t a, long b);
LHASH_API lhashuint256_t lhashuint256_div(lhashuint256_t a, lhashuint256_t b);
LHASH_API lhashuint256_t lhashuint256_divll(lhashuint256_t a, long long b);
LHASH_API lhashuint256_t lhashuint256_divl(lhashuint256_t a, long b);
LHASH_API lhashint256_t  lhashint256_diveq(lhashint256_t *a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_divlleq(lhashint256_t *a, long long b);
LHASH_API lhashint256_t  lhashint256_divleq(lhashint256_t *a, long b);
LHASH_API lhashuint256_t lhashuint256_diveq(lhashuint256_t *a, lhashint256_t b);
LHASH_API lhashuint256_t lhashuint256_divlleq(lhashuint256_t *a, long long b);
LHASH_API lhashuint256_t lhashuint256_divleq(lhashuint256_t *a, long b);

LHASH_API lhashint256_t  lhashint256_mod(lhashint256_t a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_modll(lhashint256_t a, long long b);
LHASH_API lhashint256_t  lhashint256_modl(lhashint256_t a, long b);
LHASH_API lhashuint256_t lhashuint256_mod(lhashuint256_t a, lhashuint256_t b);
LHASH_API lhashuint256_t lhashuint256_modll(lhashuint256_t a, long long b);
LHASH_API lhashuint256_t lhashuint256_modl(lhashuint256_t a, long b);
LHASH_API lhashint256_t  lhashint256_modeq(lhashint256_t *a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_modlleq(lhashint256_t *a, long long b);
LHASH_API lhashint256_t  lhashint256_modleq(lhashint256_t *a, long b);
LHASH_API lhashuint256_t lhashuint256_modeq(lhashuint256_t *a, lhashint256_t b);
LHASH_API lhashuint256_t lhashuint256_modlleq(lhashuint256_t *a, long long b);
LHASH_API lhashuint256_t lhashuint256_modleq(lhashuint256_t *a, long b);

LHASH_API lhashint256_pair_t  lhashint256_syndiv(lhashint256_t a, lhashint256_t b);
LHASH_API lhashint256_pair_t  lhashint256_syndivll(lhashint256_t a, long long b);
LHASH_API lhashint256_pair_t  lhashint256_syndivl(lhashint256_t a, long b);
LHASH_API lhashuint256_pair_t lhashuint256_syndiv(lhashuint256_t a, lhashuint256_t b);
LHASH_API lhashuint256_pair_t lhashuint256_syndivll(lhashuint256_t a, long long b);
LHASH_API lhashuint256_pair_t lhashuint256_syndivl(lhashuint256_t a, long b);
LHASH_API lhashint256_pair_t  lhashint256_syndiveq(lhashint256_t *a, lhashint256_t b);
LHASH_API lhashint256_pair_t  lhashint256_syndivlleq(lhashint256_t *a, long long b);
LHASH_API lhashint256_pair_t  lhashint256_syndivleq(lhashint256_t *a, long b);
LHASH_API lhashuint256_pair_t lhashuint256_syndiveq(lhashuint256_t *a, lhashint256_t b);
LHASH_API lhashuint256_pair_t lhashuint256_syndivlleq(lhashuint256_t *a, long long b);
LHASH_API lhashuint256_pair_t lhashuint256_syndivleq(lhashuint256_t *a, long b);

LHASH_API lhashint256_t  lhashint256_shr(lhashint256_t a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_shrll(lhashint256_t a, long long b);
LHASH_API lhashint256_t  lhashint256_shrl(lhashint256_t a, long b);
LHASH_API lhashuint256_t lhashuint256_shr(lhashuint256_t a, lhashuint256_t b);
LHASH_API lhashuint256_t lhashuint256_shrll(lhashuint256_t a, long long b);
LHASH_API lhashuint256_t lhashuint256_shrl(lhashuint256_t a, long b);
LHASH_API lhashint256_t  lhashint256_shreq(lhashint256_t *a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_shrlleq(lhashint256_t *a, long long b);
LHASH_API lhashint256_t  lhashint256_shrleq(lhashint256_t *a, long b);
LHASH_API lhashuint256_t lhashuint256_shreq(lhashuint256_t *a, lhashint256_t b);
LHASH_API lhashuint256_t lhashuint256_shrlleq(lhashuint256_t *a, long long b);
LHASH_API lhashuint256_t lhashuint256_shrleq(lhashuint256_t *a, long b);

LHASH_API lhashint256_t  lhashint256_shl(lhashint256_t a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_shlll(lhashint256_t a, long long b);
LHASH_API lhashint256_t  lhashint256_shll(lhashint256_t a, long b);
LHASH_API lhashuint256_t lhashuint256_shl(lhashuint256_t a, lhashuint256_t b);
LHASH_API lhashuint256_t lhashuint256_shlll(lhashuint256_t a, long long b);
LHASH_API lhashuint256_t lhashuint256_shll(lhashuint256_t a, long b);
LHASH_API lhashint256_t  lhashint256_shleq(lhashint256_t *a, lhashint256_t b);
LHASH_API lhashint256_t  lhashint256_shllleq(lhashint256_t *a, long long b);
LHASH_API lhashint256_t  lhashint256_shlleq(lhashint256_t *a, long b);
LHASH_API lhashuint256_t lhashuint256_shleq(lhashuint256_t *a, lhashint256_t b);
LHASH_API lhashuint256_t lhashuint256_shllleq(lhashuint256_t *a, long long b);
LHASH_API lhashuint256_t lhashuint256_shlleq(lhashuint256_t *a, long b);

LHASH_API int            lhashint256_cmp(lhashint256_t a, lhashint256_t b);
LHASH_API int            lhashint256_cmpll(lhashint256_t a, long long b);
LHASH_API int            lhashint256_cmpl(lhashint256_t a, long b);
LHASH_API int            lhashuint256_cmp(lhashuint256_t a, lhashuint256_t b);
LHASH_API int            lhashuint256_cmpll(lhashuint256_t a, long long b);
LHASH_API int            lhashuint256_cmpl(lhashuint256_t a, long b);

LHASH_API bool           lhashint256_cmple(lhashint256_t a, lhashint256_t b);
LHASH_API bool           lhashint256_cmplell(lhashint256_t a, long long b);
LHASH_API bool           lhashint256_cmplel(lhashint256_t a, long b);
LHASH_API bool           lhashuint256_cmple(lhashuint256_t a, lhashuint256_t b);
LHASH_API bool           lhashuint256_cmplell(lhashuint256_t a, long long b);
LHASH_API bool           lhashuint256_cmplel(lhashuint256_t a, long b);

LHASH_API bool           lhashint256_cmplt(lhashint256_t a, lhashint256_t b);
LHASH_API bool           lhashint256_cmpltll(lhashint256_t a, long long b);
LHASH_API bool           lhashint256_cmpltl(lhashint256_t a, long b);
LHASH_API bool           lhashuint256_cmplt(lhashuint256_t a, lhashuint256_t b);
LHASH_API bool           lhashuint256_cmpltll(lhashuint256_t a, long long b);
LHASH_API bool           lhashuint256_cmpltl(lhashuint256_t a, long b);

LHASH_API bool           lhashint256_cmpge(lhashint256_t a, lhashint256_t b);
LHASH_API bool           lhashint256_cmpgell(lhashint256_t a, long long b);
LHASH_API bool           lhashint256_cmpgel(lhashint256_t a, long b);
LHASH_API bool           lhashuint256_cmpge(lhashuint256_t a, lhashuint256_t b);
LHASH_API bool           lhashuint256_cmpgell(lhashuint256_t a, long long b);
LHASH_API bool           lhashuint256_cmpgel(lhashuint256_t a, long b);

LHASH_API bool           lhashint256_cmpgt(lhashint256_t a, lhashint256_t b);
LHASH_API bool           lhashint256_cmpgtll(lhashint256_t a, long long b);
LHASH_API bool           lhashint256_cmpgtl(lhashint256_t a, long b);
LHASH_API bool           lhashuint256_cmpgt(lhashuint256_t a, lhashuint256_t b);
LHASH_API bool           lhashuint256_cmpgtll(lhashuint256_t a, long long b);
LHASH_API bool           lhashuint256_cmpgtl(lhashuint256_t a, long b);

LHASH_API bool           lhashint256_cmpeq(lhashint256_t a, lhashint256_t b);
LHASH_API bool           lhashint256_cmpeqll(lhashint256_t a, long long b);
LHASH_API bool           lhashint256_cmpeql(lhashint256_t a, long b);
LHASH_API bool           lhashuint256_cmpeq(lhashuint256_t a, lhashuint256_t b);
LHASH_API bool           lhashuint256_cmpeqll(lhashuint256_t a, long long b);
LHASH_API bool           lhashuint256_cmpeql(lhashuint256_t a, long b);

LHASH_API bool           lhashint256_cmpne(lhashint256_t a, lhashint256_t b);
LHASH_API bool           lhashint256_cmpnell(lhashint256_t a, long long b);
LHASH_API bool           lhashint256_cmpnel(lhashint256_t a, long b);
LHASH_API bool           lhashuint256_cmpne(lhashuint256_t a, lhashuint256_t b);
LHASH_API bool           lhashuint256_cmpnell(lhashuint256_t a, long long b);
LHASH_API bool           lhashuint256_cmpnel(lhashuint256_t a, long b);


LHASH_END_EXTERN_C



#endif // _LIBHASHABLES__types_INT256_H_
