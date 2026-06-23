
#ifndef _LIBHASHABLES__types_INT128_H_
#define _LIBHASHABLES__types_INT128_H_ 1

#ifndef _LIBHASHABLES__INCLUDES_H_
#   include "../includes.h"
#endif



LHASH_EXTERN_C


/*
 * 128-bit integer type
 */
typedef struct _lhashint128_t
{
    unsigned long long v[2];
} lhashint128_t, lhashuint128_t;

#define lhashint128_0 (lhashint128_t){.v={0}}

typedef struct _lhashint128_pair_t
{
    lhashuint128_t v[2];
} lhashint128_pair_t, lhashuint128_pair_t;

LHASH_API lhashint128_t  lhashint128(long long int);
LHASH_API lhashuint128_t lhashuint128(unsigned long long int);
LHASH_API lhashint128_t  lhashint128l(long int);
LHASH_API lhashuint128_t lhashuint128l(unsigned long int);

LHASH_API lhashint128_t  lhashint128_pair(lhashint128_t a, lhashint128_t b);
LHASH_API lhashuint128_t lhashuint128_pair(lhashuint128_t a, lhashuint128_t b);
LHASH_API lhashint128_t  lhashint128_pairll(long long a, long long b);
LHASH_API lhashuint128_t lhashuint128_pairll(unsigned long long a, unsigned long long b);
LHASH_API lhashint128_t  lhashint128_pairl(long a, long b);
LHASH_API lhashuint128_t lhashuint128_pairl(unsigned long a, unsigned long b);

LHASH_API lhashint128_t  lhashint128_add(lhashint128_t a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_addll(lhashint128_t a, long long b);
LHASH_API lhashint128_t  lhashint128_addl(lhashint128_t a, long b);
LHASH_API lhashuint128_t lhashuint128_add(lhashuint128_t a, lhashuint128_t b);
LHASH_API lhashuint128_t lhashuint128_addll(lhashuint128_t a, long long b);
LHASH_API lhashuint128_t lhashuint128_addl(lhashuint128_t a, long b);
LHASH_API lhashint128_t  lhashint128_addeq(lhashint128_t *a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_addlleq(lhashint128_t *a, long long b);
LHASH_API lhashint128_t  lhashint128_addleq(lhashint128_t *a, long b);
LHASH_API lhashuint128_t lhashuint128_addeq(lhashuint128_t *a, lhashint128_t b);
LHASH_API lhashuint128_t lhashuint128_addlleq(lhashuint128_t *a, long long b);
LHASH_API lhashuint128_t lhashuint128_addleq(lhashuint128_t *a, long b);

LHASH_API lhashint128_t  lhashint128_sub(lhashint128_t a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_subll(lhashint128_t a, long long b);
LHASH_API lhashint128_t  lhashint128_subl(lhashint128_t a, long b);
LHASH_API lhashuint128_t lhashuint128_sub(lhashuint128_t a, lhashuint128_t b);
LHASH_API lhashuint128_t lhashuint128_subll(lhashuint128_t a, long long b);
LHASH_API lhashuint128_t lhashuint128_subl(lhashuint128_t a, long b);
LHASH_API lhashint128_t  lhashint128_subeq(lhashint128_t *a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_sublleq(lhashint128_t *a, long long b);
LHASH_API lhashint128_t  lhashint128_subleq(lhashint128_t *a, long b);
LHASH_API lhashuint128_t lhashuint128_subeq(lhashuint128_t *a, lhashint128_t b);
LHASH_API lhashuint128_t lhashuint128_sublleq(lhashuint128_t *a, long long b);
LHASH_API lhashuint128_t lhashuint128_subleq(lhashuint128_t *a, long b);

LHASH_API lhashint128_t  lhashint128_mult(lhashint128_t a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_multll(lhashint128_t a, long long b);
LHASH_API lhashint128_t  lhashint128_multl(lhashint128_t a, long b);
LHASH_API lhashuint128_t lhashuint128_mult(lhashuint128_t a, lhashuint128_t b);
LHASH_API lhashuint128_t lhashuint128_multll(lhashuint128_t a, long long b);
LHASH_API lhashuint128_t lhashuint128_multl(lhashuint128_t a, long b);
LHASH_API lhashint128_t  lhashint128_multeq(lhashint128_t *a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_multlleq(lhashint128_t *a, long long b);
LHASH_API lhashint128_t  lhashint128_multleq(lhashint128_t *a, long b);
LHASH_API lhashuint128_t lhashuint128_multeq(lhashuint128_t *a, lhashint128_t b);
LHASH_API lhashuint128_t lhashuint128_multlleq(lhashuint128_t *a, long long b);
LHASH_API lhashuint128_t lhashuint128_multleq(lhashuint128_t *a, long b);

LHASH_API lhashint128_t  lhashint128_div(lhashint128_t a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_divll(lhashint128_t a, long long b);
LHASH_API lhashint128_t  lhashint128_divl(lhashint128_t a, long b);
LHASH_API lhashuint128_t lhashuint128_div(lhashuint128_t a, lhashuint128_t b);
LHASH_API lhashuint128_t lhashuint128_divll(lhashuint128_t a, long long b);
LHASH_API lhashuint128_t lhashuint128_divl(lhashuint128_t a, long b);
LHASH_API lhashint128_t  lhashint128_diveq(lhashint128_t *a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_divlleq(lhashint128_t *a, long long b);
LHASH_API lhashint128_t  lhashint128_divleq(lhashint128_t *a, long b);
LHASH_API lhashuint128_t lhashuint128_diveq(lhashuint128_t *a, lhashint128_t b);
LHASH_API lhashuint128_t lhashuint128_divlleq(lhashuint128_t *a, long long b);
LHASH_API lhashuint128_t lhashuint128_divleq(lhashuint128_t *a, long b);

LHASH_API lhashint128_t  lhashint128_mod(lhashint128_t a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_modll(lhashint128_t a, long long b);
LHASH_API lhashint128_t  lhashint128_modl(lhashint128_t a, long b);
LHASH_API lhashuint128_t lhashuint128_mod(lhashuint128_t a, lhashuint128_t b);
LHASH_API lhashuint128_t lhashuint128_modll(lhashuint128_t a, long long b);
LHASH_API lhashuint128_t lhashuint128_modl(lhashuint128_t a, long b);
LHASH_API lhashint128_t  lhashint128_modeq(lhashint128_t *a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_modlleq(lhashint128_t *a, long long b);
LHASH_API lhashint128_t  lhashint128_modleq(lhashint128_t *a, long b);
LHASH_API lhashuint128_t lhashuint128_modeq(lhashuint128_t *a, lhashint128_t b);
LHASH_API lhashuint128_t lhashuint128_modlleq(lhashuint128_t *a, long long b);
LHASH_API lhashuint128_t lhashuint128_modleq(lhashuint128_t *a, long b);

LHASH_API lhashint128_pair_t  lhashint128_syndiv(lhashint128_t a, lhashint128_t b);
LHASH_API lhashint128_pair_t  lhashint128_syndivll(lhashint128_t a, long long b);
LHASH_API lhashint128_pair_t  lhashint128_syndivl(lhashint128_t a, long b);
LHASH_API lhashuint128_pair_t lhashuint128_syndiv(lhashuint128_t a, lhashuint128_t b);
LHASH_API lhashuint128_pair_t lhashuint128_syndivll(lhashuint128_t a, long long b);
LHASH_API lhashuint128_pair_t lhashuint128_syndivl(lhashuint128_t a, long b);
LHASH_API lhashint128_pair_t  lhashint128_syndiveq(lhashint128_t *a, lhashint128_t b);
LHASH_API lhashint128_pair_t  lhashint128_syndivlleq(lhashint128_t *a, long long b);
LHASH_API lhashint128_pair_t  lhashint128_syndivleq(lhashint128_t *a, long b);
LHASH_API lhashuint128_pair_t lhashuint128_syndiveq(lhashuint128_t *a, lhashint128_t b);
LHASH_API lhashuint128_pair_t lhashuint128_syndivlleq(lhashuint128_t *a, long long b);
LHASH_API lhashuint128_pair_t lhashuint128_syndivleq(lhashuint128_t *a, long b);

LHASH_API lhashint128_t  lhashint128_shr(lhashint128_t a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_shrll(lhashint128_t a, long long b);
LHASH_API lhashint128_t  lhashint128_shrl(lhashint128_t a, long b);
LHASH_API lhashuint128_t lhashuint128_shr(lhashuint128_t a, lhashuint128_t b);
LHASH_API lhashuint128_t lhashuint128_shrll(lhashuint128_t a, long long b);
LHASH_API lhashuint128_t lhashuint128_shrl(lhashuint128_t a, long b);
LHASH_API lhashint128_t  lhashint128_shreq(lhashint128_t *a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_shrlleq(lhashint128_t *a, long long b);
LHASH_API lhashint128_t  lhashint128_shrleq(lhashint128_t *a, long b);
LHASH_API lhashuint128_t lhashuint128_shreq(lhashuint128_t *a, lhashint128_t b);
LHASH_API lhashuint128_t lhashuint128_shrlleq(lhashuint128_t *a, long long b);
LHASH_API lhashuint128_t lhashuint128_shrleq(lhashuint128_t *a, long b);

LHASH_API lhashint128_t  lhashint128_shl(lhashint128_t a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_shlll(lhashint128_t a, long long b);
LHASH_API lhashint128_t  lhashint128_shll(lhashint128_t a, long b);
LHASH_API lhashuint128_t lhashuint128_shl(lhashuint128_t a, lhashuint128_t b);
LHASH_API lhashuint128_t lhashuint128_shlll(lhashuint128_t a, long long b);
LHASH_API lhashuint128_t lhashuint128_shll(lhashuint128_t a, long b);
LHASH_API lhashint128_t  lhashint128_shleq(lhashint128_t *a, lhashint128_t b);
LHASH_API lhashint128_t  lhashint128_shllleq(lhashint128_t *a, long long b);
LHASH_API lhashint128_t  lhashint128_shlleq(lhashint128_t *a, long b);
LHASH_API lhashuint128_t lhashuint128_shleq(lhashuint128_t *a, lhashint128_t b);
LHASH_API lhashuint128_t lhashuint128_shllleq(lhashuint128_t *a, long long b);
LHASH_API lhashuint128_t lhashuint128_shlleq(lhashuint128_t *a, long b);

LHASH_API int            lhashint128_cmp(lhashint128_t a, lhashint128_t b);
LHASH_API int            lhashint128_cmpll(lhashint128_t a, long long b);
LHASH_API int            lhashint128_cmpl(lhashint128_t a, long b);
LHASH_API int            lhashuint128_cmp(lhashuint128_t a, lhashuint128_t b);
LHASH_API int            lhashuint128_cmpll(lhashuint128_t a, long long b);
LHASH_API int            lhashuint128_cmpl(lhashuint128_t a, long b);

LHASH_API bool           lhashint128_cmple(lhashint128_t a, lhashint128_t b);
LHASH_API bool           lhashint128_cmplell(lhashint128_t a, long long b);
LHASH_API bool           lhashint128_cmplel(lhashint128_t a, long b);
LHASH_API bool           lhashuint128_cmple(lhashuint128_t a, lhashuint128_t b);
LHASH_API bool           lhashuint128_cmplell(lhashuint128_t a, long long b);
LHASH_API bool           lhashuint128_cmplel(lhashuint128_t a, long b);

LHASH_API bool           lhashint128_cmplt(lhashint128_t a, lhashint128_t b);
LHASH_API bool           lhashint128_cmpltll(lhashint128_t a, long long b);
LHASH_API bool           lhashint128_cmpltl(lhashint128_t a, long b);
LHASH_API bool           lhashuint128_cmplt(lhashuint128_t a, lhashuint128_t b);
LHASH_API bool           lhashuint128_cmpltll(lhashuint128_t a, long long b);
LHASH_API bool           lhashuint128_cmpltl(lhashuint128_t a, long b);

LHASH_API bool           lhashint128_cmpge(lhashint128_t a, lhashint128_t b);
LHASH_API bool           lhashint128_cmpgell(lhashint128_t a, long long b);
LHASH_API bool           lhashint128_cmpgel(lhashint128_t a, long b);
LHASH_API bool           lhashuint128_cmpge(lhashuint128_t a, lhashuint128_t b);
LHASH_API bool           lhashuint128_cmpgell(lhashuint128_t a, long long b);
LHASH_API bool           lhashuint128_cmpgel(lhashuint128_t a, long b);

LHASH_API bool           lhashint128_cmpgt(lhashint128_t a, lhashint128_t b);
LHASH_API bool           lhashint128_cmpgtll(lhashint128_t a, long long b);
LHASH_API bool           lhashint128_cmpgtl(lhashint128_t a, long b);
LHASH_API bool           lhashuint128_cmpgt(lhashuint128_t a, lhashuint128_t b);
LHASH_API bool           lhashuint128_cmpgtll(lhashuint128_t a, long long b);
LHASH_API bool           lhashuint128_cmpgtl(lhashuint128_t a, long b);

LHASH_API bool           lhashint128_cmpeq(lhashint128_t a, lhashint128_t b);
LHASH_API bool           lhashint128_cmpeqll(lhashint128_t a, long long b);
LHASH_API bool           lhashint128_cmpeql(lhashint128_t a, long b);
LHASH_API bool           lhashuint128_cmpeq(lhashuint128_t a, lhashuint128_t b);
LHASH_API bool           lhashuint128_cmpeqll(lhashuint128_t a, long long b);
LHASH_API bool           lhashuint128_cmpeql(lhashuint128_t a, long b);

LHASH_API bool           lhashint128_cmpne(lhashint128_t a, lhashint128_t b);
LHASH_API bool           lhashint128_cmpnell(lhashint128_t a, long long b);
LHASH_API bool           lhashint128_cmpnel(lhashint128_t a, long b);
LHASH_API bool           lhashuint128_cmpne(lhashuint128_t a, lhashuint128_t b);
LHASH_API bool           lhashuint128_cmpnell(lhashuint128_t a, long long b);
LHASH_API bool           lhashuint128_cmpnel(lhashuint128_t a, long b);


LHASH_END_EXTERN_C



#endif // _LIBHASHABLES__types_INT128_H_
