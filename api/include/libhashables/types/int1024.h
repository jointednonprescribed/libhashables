
#ifndef _LIBHASHABLES__types_INT1024_H_
#define _LIBHASHABLES__types_INT1024_H_ 1

#ifndef _LIBHASHABLES__INCLUDES_H_
#   include "../includes.h"
#endif



LHASH_EXTERN_C


/*
 * 128-bit integer type
 */
typedef struct _lhashint1024_t
{
    unsigned long long v[16];
} lhashint1024_t, lhashuint1024_t;

#define lhashint1024_0 (lhashint1024_t){.v={0}}

typedef struct _lhashint1024_pair_t
{
    lhashuint1024_t v[2];
} lhashint1024_pair_t, lhashuint1024_pair_t;

LHASH_API lhashint1024_t  lhashint1024(long long int);
LHASH_API lhashuint1024_t lhashuint1024(unsigned long long int);
LHASH_API lhashint1024_t  lhashint1024l(long int);
LHASH_API lhashuint1024_t lhashuint1024l(unsigned long int);

LHASH_API lhashint1024_t  lhashint1024_pair(lhashint1024_t a, lhashint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_pair(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_pairll(long long a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_pairll(unsigned long long a, unsigned long long b);
LHASH_API lhashint1024_t  lhashint1024_pairl(long a, long b);
LHASH_API lhashuint1024_t lhashuint1024_pairl(unsigned long a, unsigned long b);

LHASH_API lhashint1024_t  lhashint1024_add(lhashint1024_t a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_addll(lhashint1024_t a, long long b);
LHASH_API lhashint1024_t  lhashint1024_addl(lhashint1024_t a, long b);
LHASH_API lhashuint1024_t lhashuint1024_add(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_addll(lhashuint1024_t a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_addl(lhashuint1024_t a, long b);
LHASH_API lhashint1024_t  lhashint1024_addeq(lhashint1024_t *a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_addlleq(lhashint1024_t *a, long long b);
LHASH_API lhashint1024_t  lhashint1024_addleq(lhashint1024_t *a, long b);
LHASH_API lhashuint1024_t lhashuint1024_addeq(lhashuint1024_t *a, lhashint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_addlleq(lhashuint1024_t *a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_addleq(lhashuint1024_t *a, long b);

LHASH_API lhashint1024_t  lhashint1024_sub(lhashint1024_t a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_subll(lhashint1024_t a, long long b);
LHASH_API lhashint1024_t  lhashint1024_subl(lhashint1024_t a, long b);
LHASH_API lhashuint1024_t lhashuint1024_sub(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_subll(lhashuint1024_t a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_subl(lhashuint1024_t a, long b);
LHASH_API lhashint1024_t  lhashint1024_subeq(lhashint1024_t *a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_sublleq(lhashint1024_t *a, long long b);
LHASH_API lhashint1024_t  lhashint1024_subleq(lhashint1024_t *a, long b);
LHASH_API lhashuint1024_t lhashuint1024_subeq(lhashuint1024_t *a, lhashint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_sublleq(lhashuint1024_t *a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_subleq(lhashuint1024_t *a, long b);

LHASH_API lhashint1024_t  lhashint1024_mult(lhashint1024_t a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_multll(lhashint1024_t a, long long b);
LHASH_API lhashint1024_t  lhashint1024_multl(lhashint1024_t a, long b);
LHASH_API lhashuint1024_t lhashuint1024_mult(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_multll(lhashuint1024_t a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_multl(lhashuint1024_t a, long b);
LHASH_API lhashint1024_t  lhashint1024_multeq(lhashint1024_t *a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_multlleq(lhashint1024_t *a, long long b);
LHASH_API lhashint1024_t  lhashint1024_multleq(lhashint1024_t *a, long b);
LHASH_API lhashuint1024_t lhashuint1024_multeq(lhashuint1024_t *a, lhashint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_multlleq(lhashuint1024_t *a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_multleq(lhashuint1024_t *a, long b);

LHASH_API lhashint1024_t  lhashint1024_div(lhashint1024_t a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_divll(lhashint1024_t a, long long b);
LHASH_API lhashint1024_t  lhashint1024_divl(lhashint1024_t a, long b);
LHASH_API lhashuint1024_t lhashuint1024_div(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_divll(lhashuint1024_t a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_divl(lhashuint1024_t a, long b);
LHASH_API lhashint1024_t  lhashint1024_diveq(lhashint1024_t *a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_divlleq(lhashint1024_t *a, long long b);
LHASH_API lhashint1024_t  lhashint1024_divleq(lhashint1024_t *a, long b);
LHASH_API lhashuint1024_t lhashuint1024_diveq(lhashuint1024_t *a, lhashint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_divlleq(lhashuint1024_t *a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_divleq(lhashuint1024_t *a, long b);

LHASH_API lhashint1024_t  lhashint1024_mod(lhashint1024_t a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_modll(lhashint1024_t a, long long b);
LHASH_API lhashint1024_t  lhashint1024_modl(lhashint1024_t a, long b);
LHASH_API lhashuint1024_t lhashuint1024_mod(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_modll(lhashuint1024_t a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_modl(lhashuint1024_t a, long b);
LHASH_API lhashint1024_t  lhashint1024_modeq(lhashint1024_t *a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_modlleq(lhashint1024_t *a, long long b);
LHASH_API lhashint1024_t  lhashint1024_modleq(lhashint1024_t *a, long b);
LHASH_API lhashuint1024_t lhashuint1024_modeq(lhashuint1024_t *a, lhashint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_modlleq(lhashuint1024_t *a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_modleq(lhashuint1024_t *a, long b);

LHASH_API lhashint1024_pair_t  lhashint1024_syndiv(lhashint1024_t a, lhashint1024_t b);
LHASH_API lhashint1024_pair_t  lhashint1024_syndivll(lhashint1024_t a, long long b);
LHASH_API lhashint1024_pair_t  lhashint1024_syndivl(lhashint1024_t a, long b);
LHASH_API lhashuint1024_pair_t lhashuint1024_syndiv(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API lhashuint1024_pair_t lhashuint1024_syndivll(lhashuint1024_t a, long long b);
LHASH_API lhashuint1024_pair_t lhashuint1024_syndivl(lhashuint1024_t a, long b);
LHASH_API lhashint1024_pair_t  lhashint1024_syndiveq(lhashint1024_t *a, lhashint1024_t b);
LHASH_API lhashint1024_pair_t  lhashint1024_syndivlleq(lhashint1024_t *a, long long b);
LHASH_API lhashint1024_pair_t  lhashint1024_syndivleq(lhashint1024_t *a, long b);
LHASH_API lhashuint1024_pair_t lhashuint1024_syndiveq(lhashuint1024_t *a, lhashint1024_t b);
LHASH_API lhashuint1024_pair_t lhashuint1024_syndivlleq(lhashuint1024_t *a, long long b);
LHASH_API lhashuint1024_pair_t lhashuint1024_syndivleq(lhashuint1024_t *a, long b);

LHASH_API lhashint1024_t  lhashint1024_shr(lhashint1024_t a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_shrll(lhashint1024_t a, long long b);
LHASH_API lhashint1024_t  lhashint1024_shrl(lhashint1024_t a, long b);
LHASH_API lhashuint1024_t lhashuint1024_shr(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_shrll(lhashuint1024_t a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_shrl(lhashuint1024_t a, long b);
LHASH_API lhashint1024_t  lhashint1024_shreq(lhashint1024_t *a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_shrlleq(lhashint1024_t *a, long long b);
LHASH_API lhashint1024_t  lhashint1024_shrleq(lhashint1024_t *a, long b);
LHASH_API lhashuint1024_t lhashuint1024_shreq(lhashuint1024_t *a, lhashint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_shrlleq(lhashuint1024_t *a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_shrleq(lhashuint1024_t *a, long b);

LHASH_API lhashint1024_t  lhashint1024_shl(lhashint1024_t a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_shlll(lhashint1024_t a, long long b);
LHASH_API lhashint1024_t  lhashint1024_shll(lhashint1024_t a, long b);
LHASH_API lhashuint1024_t lhashuint1024_shl(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_shlll(lhashuint1024_t a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_shll(lhashuint1024_t a, long b);
LHASH_API lhashint1024_t  lhashint1024_shleq(lhashint1024_t *a, lhashint1024_t b);
LHASH_API lhashint1024_t  lhashint1024_shllleq(lhashint1024_t *a, long long b);
LHASH_API lhashint1024_t  lhashint1024_shlleq(lhashint1024_t *a, long b);
LHASH_API lhashuint1024_t lhashuint1024_shleq(lhashuint1024_t *a, lhashint1024_t b);
LHASH_API lhashuint1024_t lhashuint1024_shllleq(lhashuint1024_t *a, long long b);
LHASH_API lhashuint1024_t lhashuint1024_shlleq(lhashuint1024_t *a, long b);

LHASH_API int            lhashint1024_cmp(lhashint1024_t a, lhashint1024_t b);
LHASH_API int            lhashint1024_cmpll(lhashint1024_t a, long long b);
LHASH_API int            lhashint1024_cmpl(lhashint1024_t a, long b);
LHASH_API int            lhashuint1024_cmp(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API int            lhashuint1024_cmpll(lhashuint1024_t a, long long b);
LHASH_API int            lhashuint1024_cmpl(lhashuint1024_t a, long b);

LHASH_API bool           lhashint1024_cmple(lhashint1024_t a, lhashint1024_t b);
LHASH_API bool           lhashint1024_cmplell(lhashint1024_t a, long long b);
LHASH_API bool           lhashint1024_cmplel(lhashint1024_t a, long b);
LHASH_API bool           lhashuint1024_cmple(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API bool           lhashuint1024_cmplell(lhashuint1024_t a, long long b);
LHASH_API bool           lhashuint1024_cmplel(lhashuint1024_t a, long b);

LHASH_API bool           lhashint1024_cmplt(lhashint1024_t a, lhashint1024_t b);
LHASH_API bool           lhashint1024_cmpltll(lhashint1024_t a, long long b);
LHASH_API bool           lhashint1024_cmpltl(lhashint1024_t a, long b);
LHASH_API bool           lhashuint1024_cmplt(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API bool           lhashuint1024_cmpltll(lhashuint1024_t a, long long b);
LHASH_API bool           lhashuint1024_cmpltl(lhashuint1024_t a, long b);

LHASH_API bool           lhashint1024_cmpge(lhashint1024_t a, lhashint1024_t b);
LHASH_API bool           lhashint1024_cmpgell(lhashint1024_t a, long long b);
LHASH_API bool           lhashint1024_cmpgel(lhashint1024_t a, long b);
LHASH_API bool           lhashuint1024_cmpge(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API bool           lhashuint1024_cmpgell(lhashuint1024_t a, long long b);
LHASH_API bool           lhashuint1024_cmpgel(lhashuint1024_t a, long b);

LHASH_API bool           lhashint1024_cmpgt(lhashint1024_t a, lhashint1024_t b);
LHASH_API bool           lhashint1024_cmpgtll(lhashint1024_t a, long long b);
LHASH_API bool           lhashint1024_cmpgtl(lhashint1024_t a, long b);
LHASH_API bool           lhashuint1024_cmpgt(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API bool           lhashuint1024_cmpgtll(lhashuint1024_t a, long long b);
LHASH_API bool           lhashuint1024_cmpgtl(lhashuint1024_t a, long b);

LHASH_API bool           lhashint1024_cmpeq(lhashint1024_t a, lhashint1024_t b);
LHASH_API bool           lhashint1024_cmpeqll(lhashint1024_t a, long long b);
LHASH_API bool           lhashint1024_cmpeql(lhashint1024_t a, long b);
LHASH_API bool           lhashuint1024_cmpeq(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API bool           lhashuint1024_cmpeqll(lhashuint1024_t a, long long b);
LHASH_API bool           lhashuint1024_cmpeql(lhashuint1024_t a, long b);

LHASH_API bool           lhashint1024_cmpne(lhashint1024_t a, lhashint1024_t b);
LHASH_API bool           lhashint1024_cmpnell(lhashint1024_t a, long long b);
LHASH_API bool           lhashint1024_cmpnel(lhashint1024_t a, long b);
LHASH_API bool           lhashuint1024_cmpne(lhashuint1024_t a, lhashuint1024_t b);
LHASH_API bool           lhashuint1024_cmpnell(lhashuint1024_t a, long long b);
LHASH_API bool           lhashuint1024_cmpnel(lhashuint1024_t a, long b);


LHASH_END_EXTERN_C



#endif // _LIBHASHABLES__types_INT128_H_
